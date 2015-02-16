/**
 * @file fbt_translate.c
 * This modules translates one code region and puts the result into the code
 * cache.
 *
 * @author Mathias Payer <mathias.payer@nebelwelt.net>
 *
 * $Date: 2012-01-14 21:34:20 +0100 (Sat, 14 Jan 2012) $
 * $LastChangedDate: 2012-01-14 21:34:20 +0100 (Sat, 14 Jan 2012) $
 * $LastChangedBy: kravinae $
 * $Revision: 1171 $
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
 */

#include <assert.h>
#include <stdint.h>

#include "fbt_translate.h"
#include "fbt_actions.h"
#include "ia32/fbt_asm_macros.h"
#include "fbt_code_cache.h"
#include "fbt_datatypes.h"
#include "fbt_debug.h"
#include "fbt_disassemble.h"
#include "fbt_mem_mgmt.h"
#include "generic/fbt_libc.h"
#include "generic/fbt_llio.h"

#if defined(__i386__)
# include "ia32/fbt_x86_opcode.h"

# define JUMP_RELATIVE32 JMP_REL32
#elif defined(__arm__)
# include "arm/fbt_arm_opcode.h"

// TODO(philix): add relative ARM jump
# define JUMP_RELATIVE32(dst, rel32)
#endif

#if defined(INLINE_CALLS)
#define INLINE_MAX_LENGTH 64
#endif

#if defined(INLINE_CALLS)
/**
 * Checks if the current call is inlineable
 * @param ts translate struct. This translate struct must currently point to a
 * valid call instruction.
 * @return a boolean if this function is inlineable or not
 */
static ulong_t check_inline(struct translate *ts);
#endif
#if defined(SECU_ENFORCE_NX) || defined(INFO_OUTPUT)
/**
 * Checks if the translation of the given address is allowed.
 * If the translation is not allowed then fastBT will fail/quit.
 * @param orig_address instruction pointer that will be checked
 * @param info pointer to all mem_info structures that will be checked.
 */
static void check_transl_allowed(void* orig_address, struct mem_info *info);
#endif

void *fbt_translate_noexecute(struct thread_local_data *tld,
                              void *orig_address) {
  PRINT_DEBUG_FUNCTION_START("translate_noexecute(*tld=%p, *orig_address=%p)",
                             tld, orig_address);

  assert(tld != NULL);

  /* if the target is already translated then we return the cached version  */
  void *already_translated = fbt_ccache_find(tld, orig_address);
  if (already_translated != NULL) {
    PRINT_DEBUG_FUNCTION_END("already translated -> %p",
                             already_translated);
    return already_translated;
  }

  struct mem_info *code_block = tld->chunk;
  /* make sure that we don't translate translated code */
  while (code_block != NULL) {
    if ((orig_address >= code_block->ptr) &&
        (orig_address < (code_block->ptr + code_block->size))) {
      llprintf("Translating translated code: %p (%p len: 0x%x (%p) type: %d (syscall=%d))\n",
               orig_address, code_block->ptr, code_block->size, code_block,
               code_block->type, MT_SYSCALL_TABLE);
      fbt_suicide(255);
    }
    code_block = code_block->next;
  }

#if defined(SECU_ENFORCE_NX)
  /* Check if the memory address to translate lies in an executable
     section of a loaded library or the executable itself. We only allow
     execution if this is the case. */
  struct mem_info curr_section;
  check_transl_allowed(orig_address, &curr_section);
#endif

  /* we need to translate TU, add to ccache index,
     jump to the translated code */
  enum translation_state tu_state = NEUTRAL;

  int bytes_translated = 0;
  struct translate *ts = &(tld->trans);
  ts->next_instr = (unsigned char*)orig_address;

  /* check if more memory needs to be allocated for tcache */
  if ((long)(ts->code_cache_end - ts->transl_instr) < MAX_BLOCK_SIZE) {
    PRINT_DEBUG("Not enough memory for new code block - allocating more!");
    unsigned char *prev_transl_instr = ts->transl_instr;

    fbt_allocate_new_code_cache(tld);

    /* add a jmp connect old and new tcache memory blocks */
    if (prev_transl_instr != NULL) {
      JUMP_RELATIVE32(prev_transl_instr, ts->transl_instr);
    }
  }
  PRINT_DEBUG("tld->ts.transl_instr: %p", ts->transl_instr);

  /* add entry to ccache index */
  fbt_ccache_add_entry(tld, orig_address, ts->transl_instr);

  /* look up address in translation cache index */
  void *transl_address = ts->transl_instr;

  /* we translate as long as we
     - stay in the limit (MAX_BLOCK_SIZE)
     - or if we have an open TU (could happen if we are translating a call or
       so)
     - or we are inlining, then we first need to finish it and spill all the
       frames! we need to check for inlining here because inlining could
       overrun the MAX_BLOCK _SIZE (this can happen if we translate short
       instructions in the inlined code to longer instructions in the
       translated code - but thats what the guard is there for!) */
#ifdef INLINE_CALLS
  while (((bytes_translated < MAX_BLOCK_SIZE) && (tu_state == NEUTRAL)) ||
         (tu_state == OPEN) || (ts->inline_call_RIP!=NULL)) {
#else
  while (((bytes_translated < MAX_BLOCK_SIZE) && (tu_state == NEUTRAL)) ||
         (tu_state == OPEN)) {
#endif  /* INLINE_CALLS */
    /* translate an instruction */
    /* Check if we are still within the boundaries of the current section.
       Otherwise, do a complete check of the address to translate and
       update the current section information. */
#ifdef SECU_ENFORCE_NX
    if (((void*) ts->next_instr < curr_section.node.addr_begin)
        || ((void*) ts->next_instr >= curr_section.node.addr_end)) {
      check_transl_allowed(ts->next_instr, &curr_section);
    }
#endif /* SECU_ENFORCE_NX */

#if defined(FBT_CHECK_TRANSLATED)
    // current instr already translated?
    unsigned char *dst=NULL;
    if (((dst=tcache_find(tld, ts->next_instr))!=NULL) &&
        dst!=ts->transl_instr && ts->inlined_frames==NULL) {
      JUMP_RELATIVE32(ts->transl_instr, (int32_t)dst);
      tu_state = CLOSE;
      break;
    }
#endif

    fbt_disasm_instr(ts);
    PRINT_DEBUG("translating a '%s'", ts->cur_instr_info->mnemonic);

    unsigned char *old_transl_instr = ts->transl_instr;
#ifdef DEBUG
    unsigned char *old_cur_instr = ts->cur_instr;
    unsigned char *old_next_instr = ts->next_instr;
#endif
#ifdef DUMP_GENERATED_CODE
    unsigned char *old_transl_instr_dump = ts->transl_instr;
    unsigned char *old_next_instr_dump = ts->next_instr;
#endif

#if defined(INLINE_CALLS)
    /* if the current instruction is a call, then we check if it is inlinable */
    if (ts->cur_instr_info->opcode.handler == action_call) {
      unsigned int function_length;
      // inlinable ?
      if ((function_length = check_inline(ts)) &&
          ((bytes_translated + function_length) < MAX_BLOCK_SIZE)) {
        // if yes, then we construct the static call frame (with return address)
        ts->inline_call_RIP = ts->next_instr;
      }
    }
#endif

    /* call the action specified for this instruction */
    tu_state = ts->cur_instr_info->opcode.handler(ts);

    bytes_translated += (ts->transl_instr - old_transl_instr);

#if defined(FBT_STATISTIC)
    fbt_nr_translated_instr++;
#endif
    PRINT_DEBUG("orig_ins_addr: %p (%db)", ts->cur_instr, (old_next_instr -
                                                           old_cur_instr));
    PRINT_DEBUG("transl_insn_addr: %p (%db)", old_transl_instr,
                (ts->transl_instr - old_transl_instr));
    PRINT_DEBUG("tu_state: %d\n", tu_state); /* debug */
    DUMP_CODE(ts, (old_next_instr_dump - ts->cur_instr),
              (ts->transl_instr - old_transl_instr_dump));
  }

  /* if the TU was finished because the number of instructions hit the limit, we
     have to add glue code to the TU */
  if (tu_state != CLOSE) {
    if (tu_state != CLOSE_GLUE) {
      PRINT_DEBUG("finishing TU because instruction limit was hit, invoking"
                  "translation function on %p", ts->next_instr);
    } else {
      PRINT_DEBUG("closing TU upon request, invoking translation function on"
                  " %p", ts->next_instr);
    }
    /* takes care of the flag register! */
    /* write: jump to trampoline that does chaining if next block needs to be
       translated or does fallthrough otherwise */
    struct trampoline *trampo = fbt_create_trampoline(tld,
                                                      (void*)ts->next_instr,
                                                      ts->transl_instr+1,
                                                      ORIGIN_RELATIVE);
    JUMP_RELATIVE32(ts->transl_instr, trampo->code);
  }

  /* make sure that we always stay in the limits, even if we overwrite the
     MAX_BLOCK_SIZE due to some optimizations */
  assert(bytes_translated < TRANSL_GUARD);
  assert((void*)(ts->transl_instr) < (void*)(ts->code_cache_end +
                                             TRANSL_GUARD));

  PRINT_DEBUG_FUNCTION_END("-> %p,   next_tu=%p (len: %d)", transl_address,
                           ts->next_instr, bytes_translated);

  return transl_address;
}

#if defined(SECU_ENFORCE_NX)
static void check_transl_allowed(void* orig_address, struct mem_info *info) {
  if (fbt_memprotect_execquery(orig_address)) {
    if (!fbt_memprotect_info(orig_address, info)) {
      fbt_suicide_str("Unknown error in check_transl_allowed"
                      " (check_transl_allowed: fbt_translate.c).\n");
    }
  } else {
    if (fbt_memprotect_info(orig_address, info)) {
      llprintf("Tried to translate code at address %p in %s, section %s, "
               "which is not marked as executable.\n",
               orig_address, info->obj_name, info->sec_name);
    } else {
      llprintf("Tried to translate code at address %p, which was determined"
               " not to be in a section of any loaded shared library or the"
               " executable.\n", orig_address);
    }
    fbt_suicide_str("Exiting Program! If you believe this occurs in error,"
                    " disable the -DSECU_ENFORCE_NX CFLAG in the libdetox "
                    "Makefile (check_transl_allowed: fbt_translate.c).\n");
  }
}
#endif

#if defined(INLINE_CALLS)
static ulong_t check_inline(struct translate *ts) {
  /* static translate struct for internal use */
  struct translate myts;
  fbt_memcpy(&myts, ts, sizeof(struct translate));
  unsigned int function_length = 0;

  /* extract relative call target from call. */
  /* we assume that this call will not have any prefixes */
#if defined(__i386__)
  assert(!HAS_PREFIX(*(myts.cur_instr)));
#elif defined(__arm__)
  // TODO(philix): port check_inline() to ARM
#endif
  myts.next_instr = (unsigned char*)(*((int32_t*)(myts.cur_instr + 1)) +
                                     (int32_t)myts.cur_instr + 5);

  while (function_length < INLINE_MAX_LENGTH) {
    fbt_disasm_instr(&myts);
    function_length += (myts.next_instr - myts.cur_instr);

    if (myts.cur_instr_info->opcode.handler != action_copy) {
      /* if we found a ret, then we are done, let's return the length of this
         function (in bytes) */
      if (myts.cur_instr_info->opcode.handler == action_ret)
        return function_length;

      /* if (myts.action == action_call) ...
         if we have a call, then we might go into recursion and inline this
         call as well. But if we want to support recursion then we need to add
         dynamic inline information structs (e.g., a linked list) and then we
         would also need to implement a free function for unused inline
         structs. As we only inline 64 bytes usually this is not worth it. */

      /* some action we don't know jack about - stop inlining and bail out */
      return 0;
    }
  }
  /* if the function is too long we might hit that */
  return 0;
}
#endif

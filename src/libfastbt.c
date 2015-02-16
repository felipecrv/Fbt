/**
 * @file libfastbt.c
 * Interface to the binary translator which can be used from the outside
 *
 * Copyright (c) 2011 ETH Zurich
 * @author Mathias Payer <mathias.payer@nebelwelt.net>
 *
 * $Date: 2012-01-22 21:05:54 +0100 (Sun, 22 Jan 2012) $
 * $LastChangedDate: 2012-01-22 21:05:54 +0100 (Sun, 22 Jan 2012) $
 * $LastChangedBy: kravinae $
 * $Revision: 1206 $
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

#include "libfastbt.h"
#include "fbt_code_cache.h"
#include "fbt_debug.h"
#include "fbt_mem_mgmt.h"
#include "fbt_syscall.h"
#include "fbt_translate.h"
#include "fbt_trampoline.h"
#include "generic/fbt_libc.h"
#include "generic/fbt_llio.h"
#if defined(__i386__)
# include "ia32/fbt_x86_opcode.h"
#elif defined(__arm__)
# include "arm/fbt_arm_opcode.h"
#endif

/* forward declaration for the default opcode table */
extern ArchOpcode default_opcode_table[];

/* Starting the BT with LD_PRELOAD

   By using `LD_PRELOAD=./src/libarmfbt.so executable` on the terminal we can
   redefine the executable's `_init` and `_fini` symbols. By providing our own
   `_fini` we can take control of the execution.

   _fini(); // called by Linux when starting the process
    |- tld = fbt_init(NULL);
    |         \- initialize thread-local store and trampolines
    |            (fbt_initialize_trampolines())
    |
    \- fbt_start_transaction(tld, fbt_commit_transaction);
        |- fbt_transaction_init(tld, commit_transaction = fbt_commit_transaction);
        |   \- Adds an entry to the code cache to map `fbt_commit_transaction`
        |      to `fbt_end_transaction`. Then when `fbt_commit_transaction`
        |      would execute in `_fini`, the BT jumps to `fbt_end_transaction`
        |      which does nothing instead of printing an error message as
        |      `fbt_commit_transaction` whould do.
        |
        |- finds out the return address of fbt_start_transaction() and tranlates code
        |  from this address.
        |
        \- overwrite the return address in the stack to an address in the
           translated code so that execution continues from the translated code
           once fbt_start_transaction() returns.

*/

#ifdef HIJACKCONTROL
static struct thread_local_data *tld;

void _init() {
# if defined(DEBUG) && !defined(SILENT_STARTUP)
  llprintf("Starting BT\n");
  llprintf("This is a debug build, so do not expect stellar performance!\n");
# endif

  //sleep(5);
  tld = fbt_init(NULL);

  fbt_start_transaction(tld, fbt_commit_transaction);
  // -> return address of fbt_start_transaction()
  //
  // fbt_start_transaction() finds out this address and start translating
  // code from here (i.e. it starts translating the executable's code).
}

void _fini() {
  // If everything goes well, _fini should be executed inside the translator.
# if defined(DEBUG) && !defined(SILENT_STARTUP)
  llprintf("Stopping BT\n");
# endif /* DEBUG */
  fbt_commit_transaction(); // This will be redirected to fbt_end_transaction()
                            // by the translator.
  fbt_exit(tld);
}
#endif // HIJACKCONTROL

/* this function is called in fbt_asm_functions.S, .section .init */
struct thread_local_data* fbt_init(ArchOpcode *opcode_table) {
  DUMP_START();
  DEBUG_START();

  struct thread_local_data *tld = fbt_init_tls();
  #ifdef SHARED_DATA
  fbt_init_shared_data(tld);
  #endif

  fbt_initialize_trampolines(tld);

  /* if the user program specifies a custom opcode table we overwrite the
   * default table overwriting is done because of performance reasons. this way
   * the position of the default_opcode_table does not change in memory and therefore
   * the address can be hardcoded at compile time */
  if (opcode_table != NULL) {
    fbt_memcpy(default_opcode_table, opcode_table, 0x100 * sizeof(ArchOpcode));
  }

#if defined(AUTHORIZE_SYSCALLS)
  /* call init function for the secure system call mechanism */
  fbt_init_syscalls(tld);
#endif

  return tld;
}

void fbt_exit(struct thread_local_data *tld) {
  PRINT_DEBUG_FUNCTION_START("fbt_exit(tld=%p)\n", tld);
  assert(tld != NULL);

  fbt_mem_free(tld);

  PRINT_DEBUG_FUNCTION_END(" ");
  DUMP_END();
  DEBUG_END();
}

void fbt_transaction_init(struct thread_local_data *tld,
                          void (*commit_function)()) {
  /* set memory address of the stub of fbt_commit_transaction in the client
     program */
  fbt_ccache_add_entry(tld, (void*)commit_function, (void*)fbt_end_transaction);

#ifdef SHARED_DATA
  /* Remember the commit function, in case we need to reestablish the cache
   * entry when we flush the cache */
  tld->shared_data->commit_function = commit_function;
#endif

  /* These functions are not transaction safe, therefore we catch them inside of
   * transactions and execute our own cover-functions that take care to return
   * to translated code */
#if defined(HIJACKCONTROL)
  /* if thread fails to exit from the BT then we force-exit it */
  fbt_ccache_add_entry(tld, (void*)fbt_exit, (void*)fbt_exit);
#endif  /* HIJACKCONTROL */
}

void fbt_start_transaction(struct thread_local_data *tld,
                           void (*commit_function)()) {
  PRINT_DEBUG_FUNCTION_START("fbt_start_transaction(commit_function = %p)",
                             (void*)commit_function);

  fbt_transaction_init(tld, commit_function);

  /* find out return instruction pointer (=beginning of first TU)*/
  void *orig_begin = __builtin_return_address(0);
  char *transl_begin = fbt_translate_noexecute(tld, orig_begin);

  PRINT_DEBUG("starting transaction at %p (orig. addr: %p)\n",
              (long)transl_begin, (long)orig_begin);

  /* use a jump-back trampoline to jump to the translated code in the code cache
   */
  tld->ind_target = transl_begin;
  /* overwrite RIP to jump to tramp */
  *((ulong_t*)__builtin_frame_address(0)+1) = (ulong_t)tld->ret2app_trampoline;
  PRINT_DEBUG_FUNCTION_END(" ");
  /* avoid tail-call optimization (-foptimize-sibling-calls) for RIP change */
  __asm__ volatile("" : : : "cc", "memory");
}

void fbt_commit_transaction() {
  llprintf("WARNING: Guest code managed to break out of secuBT"
           " sandbox!\nIf you can read this message, this means that "
           "untranslated code was executed between fbt_start_transaction() and "
           "fbt_commit_transaction().\n");
  DUMP_END();
  DEBUG_END();
}

void fbt_end_transaction() {
#if defined(FBT_STATISTIC)
  fbt_print_statistics();
#endif
  __asm__ volatile("");
}

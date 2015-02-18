/**
 * @file fbt_pc_cache.h
 * This module defines a data structure that maps the PC of translated code to
 * the PC of untranslated code.
 *
 * Copyright (c) 2015 Felipe O. Carvalho
 * @author Felipe O. Carvalho <felipekde@gmail.com>
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

#include "fbt_pc_cache.h"
#include "../generic/fbt_libc.h"  // for NULL
#include "../fbt_datatypes.h"
#include "../fbt_debug.h"

/**
 * Find the original (untranslated PC value) that was previously mapped in
 * tld->pc_mappingtable.
 */
uint32_t *fbt_pccache_find(struct thread_local_data *tld, uint32_t *translated_pc) {
  PRINT_DEBUG_FUNCTION_START("fbt_pccache_find(*tld=%p, *translated_pc=%p)",
                             tld, translated_pc);
  assert(tld != NULL);

  /* calculate offset into hashtable (this instruction is our hash function) */
  uint32_t offset = C_PC_MAPPING_FUNCTION((uint32_t)translated_pc);
  uint32_t pos = 0;
  struct pccache_entry *entry = tld->pc_mappingtable + offset;

  /* check entry if translated_pc address equals translated_pc */
  while (entry->translated_pc != 0) {
    if (translated_pc == entry->translated_pc) {
      /* return corresponding dest address */
      PRINT_DEBUG_FUNCTION_END("-> %p", entry->untranslated_pc);
      assert(entry->untranslated_pc != NULL);
      if (pos != 0) {
        /* not optimal entry! swap suboptimal entry! */
        void *tmp;
        struct pccache_entry *firstentry = tld->pc_mappingtable +
          C_PC_MAPPING_FUNCTION((uint32_t)translated_pc);
        tmp = firstentry->translated_pc;
        firstentry->translated_pc = entry->translated_pc;
        entry->translated_pc = tmp;
        tmp = firstentry->untranslated_pc;
        firstentry->untranslated_pc = entry->untranslated_pc;
        entry->untranslated_pc = tmp;
        entry = firstentry;
      }
      return entry->untranslated_pc;
    }
    /* We mustn't access memory beyond the hashtable!!
     * Bitwise AND with (HASHTABLE_SIZE - 1) is the same as
     * modulo HASHTABLE_SIZE. */
    offset = (offset + sizeof(struct pccache_entry)) & (PC_MAPPINGTABLE_SIZE - 1);
    pos++;
    entry = tld->pc_mappingtable + offset;
  }

  PRINT_DEBUG_FUNCTION_END("-> %p", NULL);
  return NULL;
}

/**
 * Create a translated_pc -> untranslated_pc mapping in the PC cache.
 */
void fbt_pccache_add_entry(struct thread_local_data *tld,
                           void *translated_pc,
                           void *untranslated_pc) {
  PRINT_DEBUG_FUNCTION_START(
      "fbt_pccache_add_entry(*tld=%p, *translated_pc=%p, *untranslated_pc=%p)",
      tld, translated_pc, untranslated_pc);

  /* calculate offset into hashtable that corresponds to this translated_pc*/
  uint32_t offset = C_PC_MAPPING_FUNCTION((uint32_t) translated_pc);
  struct pccache_entry *entry = tld->pc_mappingtable + offset;

  int count = 0;

  /* search the hastable for a free position, beginning at offset */
  while (entry->translated_pc != 0) {
    offset = (offset + sizeof(struct pccache_entry)) & (PC_MAPPINGTABLE_SIZE - 1);
    entry = tld->pc_mappingtable + offset;
    count++;
    if (count >= PC_MAPPINGTABLE_MAXENTRIES / 10) {
      fbt_suicide_str("ERROR: pc_mappingtable out of space (fbt_pc_cache.c)\n");
    }
  }

  /* insert entry into hashtable */
  entry->translated_pc = translated_pc;
  entry->untranslated_pc = untranslated_pc;
  PRINT_DEBUG_FUNCTION_END(" ");
}

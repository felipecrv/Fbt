#ifndef ARM_FBT_PC_CACHE_H
#define ARM_FBT_PC_CACHE_H

#include <stdint.h>

#include "../fbt_datatypes.h"

  /** pc_mappingtable size: we use 20bit out of the 32bit of an address to perform a
   lookup in the hashtable. 2^20 * 8 bytes (space for 2 32bit addresses) =
   8MB. Has to be a power of 2.  */
#define PC_MAPPINGTABLE_NRBITS 23
#define PC_MAPPINGTABLE_SIZE (0x1 << PC_MAPPINGTABLE_NRBITS)
#define PC_MAPPINGTABLE_MAXENTRIES (PC_MAPPINGTABLE_SIZE >> 3)
  /**< (i % MAPPINGTABLE_SIZE) should be the same as (i & (HASHTABLE_SIZE - 1)),
     and the compiler is good at precomputing constant expressions such as
     (HASHTABLE_SIZE - 1) */

/** We take bits with exponents 2 to 21 (inclusive) of the source address to
    determine the position in the hash table. Because an entry in the table is 8
    bytes long, we can only address locations in the table with 8 bytes
    granularity. To achieve that, the address is shifted one bit to the left and
    ANDed with this pattern. This gives us the offset into the table.  WARNING:
    code in fbt_asm_function.S depends on the layout of this definition!
*/
#define PC_MAPPING_PATTERN ((PC_MAPPINGTABLE_SIZE - 1) ^ 0x7)

  /** Implementation of the hash mapping function as C code. The assembly code
      must follow this hash function! */
#define C_PC_MAPPING_FUNCTION(addr)  (((addr) << 3) & PC_MAPPING_PATTERN)

// translated_pc -> untranslated_pc mapping
struct pccache_entry {
  uint32_t *translated_pc;
  uint32_t *untranslated_pc;
};

uint32_t *fbt_pccache_find(struct thread_local_data *tld, uint32_t *translated_pc);

void fbt_pccache_add_entry(struct thread_local_data *tld,
                           void *translated_pc,
                           void *untranslated_pc);

#endif  /* ARM_FBT_PC_CACHE_H */

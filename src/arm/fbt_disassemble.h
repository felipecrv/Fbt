#ifndef FBT_ARM_DISASSEMBLE
#define FBT_ARM_DISASSEMBLE

#include <stdint.h>

#include "../generic/fbt_llio.h"

#define DECODE_REG(lowest_bit, x)    (((x) >> (lowest_bit)) & 0x0F)
#define DECODE_IMM5(lowest_bit, x)   (((x) >> (lowest_bit)) & 0x1F)
#define DECODE_IMM12(lowest_bit, x)  (((x) >> (lowest_bit)) & 0xFFF)

/*
 * @param instr_stream pointer to the 32-bit instruction stream
 * @param size
 * @param start_addr the address of the first instruction in the stream
 * @param out fd where output should be written to
 */
void fbt_disassemble_to_text(uint32_t *instr_stream,
                             uint32_t size,
                             uint32_t start_addr,
                             int out);


#endif  /* FBT_ARM_DISASSEMBLE */

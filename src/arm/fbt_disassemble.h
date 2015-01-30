#ifndef FBT_ARM_DISASSEMBLE
#define FBT_ARM_DISASSEMBLE

#include <stdint.h>

#include "../generic/fbt_llio.h"

#define DECODE_REG(lowest_bit, x)    (((x) >> (lowest_bit)) & 0x0F)
#define DECODE_IMM12(x)              ((x) & 0xFFF)
#define DECODE_IMM5(lowest_bit, x)   (((x) >> (lowest_bit)) & 0x1F)
#define DECODE_SHIFT_TYPE(x)         (((x) >> 5) & 0x3)


static inline uint32_t rotate_right(uint32_t x, uint32_t shift) {
  return (x << (32 - shift)) | (x >> shift);
}

static inline uint32_t fbt_imm12_to_const(uint32_t imm12) {
  return rotate_right(imm12 & 0xFF, (imm12 >> 7) & 0x1E);
}

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

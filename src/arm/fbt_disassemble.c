#include <stdint.h>

#include "../generic/fbt_llio.h"
#include "../fbt_translate.h"
#include "fbt_arm_opcode.h"
#include "fbt_disassemble.h"
#include "fbt_opcode_tables.h"

static char register_names[][4] = {
  "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
  "r8", "r9", "r10", "fp", "ip", "sp", "lr", "pc"
};

static char textual_conds[16][5] = {
         //              (integer)                     (floating) *
  "eq",  //     0b0000 = Equal                         Equal
  "ne",  //     0b0001 = Not equal                     Not equal, or unordered
  "cs",  // **  0b0010 = Carry set                     Greater than, equal, or unordered
  "cc",  // *** 0b0011 = Carry clear                   Less than
  "mi",  //     0b0100 = Minus, negative               Less than
  "pl",  //     0b0101 = Plus, positive or zero        Greater than, equal, or unordered
  "vs",  //     0b0110 = Overflow                      Unordered
  "vc",  //     0b0111 = No overflow                   Not unordered
  "hi",  //     0b1000 = Unsigned higher               Greater than, or unordered
  "ls",  //     0b1001 = Unsigned lower or same        Less than or equal
  "ge",  //     0b1010 = Signed greater than or equal  Greater than or equal
  "lt",  //     0b1011 = Signed less than              Less than, or unordered
  "gt",  //     0b1100 = Signed greater than           Greater than
  "le",  //     0b1101 = Signed less than or equal     Less than, equal or unordered
  "",    //     0b1110 = Always (al)                   Always
  "<?>",
};
//   * unordered means at least one NaN operand
//  ** "hs" (unsigned higher or same) = "cs"
// *** "lo" (unsigned lower) = "cc"

void fbt_disassemble_to_text(uint32_t *instr_stream,
                             uint32_t size,
                             uint32_t start_addr,
                             int out) {
  uint32_t stream_addr = start_addr;

  for (uint32_t instr_idx = 0; instr_idx < size; instr_idx++) {
    uint32_t binary_instr = instr_stream[instr_idx];
    uint32_t opcode_table_key = ((binary_instr >> 16) & 0xFF0) | ((binary_instr >> 4) & 0xF);
    ARMOpcode *opcode = &opcode_table[opcode_table_key];
    uint32_t cond = (binary_instr >> 28) & 0xF;

#define EMIT_TEXT_CODE(fmt, args...) fllprintf(out, fmt, ##args)

#define EMIT_TEXT_INSTR(fmt, args...) \
    fllprintf(out, "0x%x: %s%s\t", stream_addr, opcode->mnemonic, textual_conds[(cond)]); \
    fllprintf(out, fmt, ##args)

    if ((opcode->opcode_flags & DATA) == DATA) {
      int Rn = DECODE_REG(16, binary_instr);
      int Rd = DECODE_REG(12, binary_instr);

      if ((opcode->operand_flags & OPND_REG_SHIFT_BY_IMM) == OPND_REG_SHIFT_BY_IMM) {
        int imm5 = DECODE_IMM5(7, binary_instr);
        int Rm = DECODE_REG(0, binary_instr);

        // <mnemonic>{S}{<c>}{<q>} {<Rd>,} <Rn>, <Rm>{, shift}
        switch (opcode->opcode_flags & 0x1FFF) {
          case TST:
          case TEQ:
          case CMP:
          case CMN:
            // Rd = (0)(0)(0)(0)
            EMIT_TEXT_INSTR("%s, %s", register_names[Rn], register_names[Rm]);
            break;
          case MOV:
          case MVN:
            // Rn = (0)(0)(0)(0)
            EMIT_TEXT_INSTR("%s, %s", register_names[Rd], register_names[Rm]);
            break;
          default:
            EMIT_TEXT_INSTR("%s, %s, %s", register_names[Rd], register_names[Rn], register_names[Rm]);
            break;
        }
        if (imm5 != 0) {
          EMIT_TEXT_CODE(", <type> #%d", imm5);
        }
        EMIT_TEXT_CODE("\n");
      } else if ((opcode->operand_flags & OPND_IMM) == OPND_IMM) {
        int imm12 = binary_instr & 0xFFF;

        // <mnemonic>{S}{<c>}{<q>} {<Rd>,} <Rn>, #<const>
        switch (opcode->opcode_flags & 0x1FFF) {
          case TST:
          case TEQ:
          case CMP:
          case CMN:
            // Rd = (0)(0)(0)(0)
            EMIT_TEXT_INSTR("%s, #%d\n", register_names[Rn], imm12);
            break;
          case MOV:
          case MVN:
            // Rn = (0)(0)(0)(0)
            EMIT_TEXT_INSTR("%s, #%d\n", register_names[Rd], imm12);
            break;
          default:
            EMIT_TEXT_INSTR("%s, %s, #%d\n", register_names[Rd], register_names[Rn], imm12);
            break;
        }
      } else { // OPND_REG_SHIFT_BY_REG
        int Rs = DECODE_REG(8, binary_instr);
        int Rm = DECODE_REG(0, binary_instr);

        // <mnemonic>{S}{<c>}{<q>} {<Rd>,} <Rn>, <Rm>, <type> <Rs>
        EMIT_TEXT_INSTR(
            "%s, %s, %s, <shift_by_reg> %s\n",
            register_names[Rd], register_names[Rn], register_names[Rm], register_names[Rs]);
      }
    } else if ((opcode->opcode_flags & BRANCH) == BRANCH) {
      EMIT_TEXT_INSTR(" ...\n");
    } else if ((opcode->opcode_flags & LOAD_STORE) == LOAD_STORE) {
      EMIT_TEXT_INSTR(" ...\n");
    } else if ((opcode->opcode_flags & MULTI_LOAD_STORE) == MULTI_LOAD_STORE) {
      EMIT_TEXT_INSTR(" ...\n");
    } else if ((opcode->opcode_flags & STATUS) == STATUS) {
      EMIT_TEXT_INSTR(" ...\n");
    } else if ((opcode->opcode_flags & COPROCESSOR) == COPROCESSOR) {
      EMIT_TEXT_INSTR(" ...\n");
    } else if ((opcode->opcode_flags & MISC) == MISC) {
      EMIT_TEXT_INSTR(" ...\n");
    } else {
      fllprintf(out, "0x%x: <UNRECOGNIZED>\n", stream_addr);
    }

    stream_addr += 4;
  }
}

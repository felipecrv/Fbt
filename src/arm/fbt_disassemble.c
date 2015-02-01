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
  "",
};
//   * unordered means at least one NaN operand
//  ** "hs" (unsigned higher or same) = "cs"
// *** "lo" (unsigned lower) = "cc"

static char shift_types[4][4] = {"lsl", "lsr", "asr", "ror"};

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

#define EMIT_TEXT_CODE(fmt, args...) fllprintf(out, (fmt), ##args)

#define EMIT_TEXT_INSTR(fmt, args...) \
    EMIT_TEXT_CODE("0x%x: %.8x    %s%s\t", stream_addr, binary_instr, opcode->mnemonic, textual_conds[(cond)]); \
    EMIT_TEXT_CODE((fmt), ##args)

#define EMIT_TEXT_PSEUDO_INSTR(mnemonic, fmt, args...) \
    if ((opcode->opcode_flags & SET_APSR) == SET_APSR) { \
      EMIT_TEXT_CODE("0x%x: %.8x    %ss%s\t", stream_addr, binary_instr, (mnemonic), textual_conds[(cond)]); \
    } else { \
      EMIT_TEXT_CODE("0x%x: %.8x    %s%s\t", stream_addr, binary_instr, (mnemonic), textual_conds[(cond)]); \
    } \
    EMIT_TEXT_CODE((fmt), ##args)

#define EMIT_TEXT_IMM12() \
    do { \
      if (rotation == 0) { \
        EMIT_TEXT_CODE("#%d", base_value); \
      } else { \
        EMIT_TEXT_CODE("#%d, %d", base_value, rotation); \
      } \
      uint32_t rotated = rotate_right(base_value, rotation); \
      if (rotated) { \
        EMIT_TEXT_CODE("  ; 0x%x\n", rotated); \
      } else { \
        EMIT_TEXT_CODE("\n"); \
      } \
    } while(0)

#define EMIT_TEXT_SHIFT_BY_IMM() \
    do { \
      switch (shift_type) { \
        case 0x0: \
          if (imm5 != 0) { \
            EMIT_TEXT_CODE(", lsl #%d\n", imm5); \
          } else { \
            EMIT_TEXT_CODE("\n"); \
          } \
          break; \
        case 0x1: \
          EMIT_TEXT_CODE(", lsr #%d\n", (imm5 == 0) ? 32 : imm5); \
          break; \
        case 0x2: \
          EMIT_TEXT_CODE(", asr #%d\n", (imm5 == 0) ? 32 : imm5); \
          break; \
        case 0x3: \
          if (imm5 == 0) { \
            EMIT_TEXT_CODE(", rrx\n"); \
          } else { \
            EMIT_TEXT_CODE(", ror #%d\n", imm5); \
          } \
          break; \
      } \
    } while (0)

    switch (opcode->opcode_flags & INSTR_GROUP_MASK) {
      case DATA_OTHER:
      case DATA_ARITH:
      case DATA_LOGIC:
      case DATA_COND: {
        uint8_t Rn = DECODE_REG(16, binary_instr);
        uint8_t Rd = DECODE_REG(12, binary_instr);

        if ((opcode->operand_flags & OPND_REG_SHIFT_BY_IMM) == OPND_REG_SHIFT_BY_IMM) {
          uint8_t Rm = DECODE_REG(0, binary_instr);
          uint8_t imm5 = DECODE_IMM5(7, binary_instr);
          uint8_t shift_type = DECODE_SHIFT_TYPE(binary_instr);

          // <mnemonic>{S}{<c>}{<q>} {<Rd>,} <Rn>, <Rm>{, shift}
          switch (opcode->opcode_flags & 0x1FFF) {
            case TST:
            case TEQ:
            case CMP:
            case CMN:
              // Rd = (0)(0)(0)(0)
              EMIT_TEXT_INSTR("%s, %s", register_names[Rn], register_names[Rm]);
              EMIT_TEXT_SHIFT_BY_IMM();
              break;
            case MOV:
              // Rn = (0)(0)(0)(0)
              if (((uint8_t) ((binary_instr >> 5) & 0x7F)) == 0) { // imm5 . type == 0
                EMIT_TEXT_INSTR("%s, %s\n", register_names[Rd], register_names[Rm]);
              } else {
                switch (shift_type) {
                  case 0x0:
                    EMIT_TEXT_PSEUDO_INSTR(
                        "lsl", "%s, %s, #%d\n",
                        register_names[Rd], register_names[Rm], imm5);
                    break;
                  case 0x1:
                    EMIT_TEXT_PSEUDO_INSTR(
                        "lsr", "%s, %s, #%d\n",
                        register_names[Rd], register_names[Rm], (imm5 == 0) ? 32 : imm5);
                    break;
                  case 0x2:
                    EMIT_TEXT_PSEUDO_INSTR(
                        "asr", "%s, %s, #%d\n",
                        register_names[Rd], register_names[Rm], (imm5 == 0) ? 32 : imm5);
                    break;
                  case 0x3:
                    if (imm5 == 0) {
                      EMIT_TEXT_PSEUDO_INSTR("rrx", "%s, %s\n", register_names[Rd], register_names[Rm]);
                    } else {
                      EMIT_TEXT_PSEUDO_INSTR(
                          "ror", "%s, %s, #%d\n",
                          register_names[Rd], register_names[Rm], imm5);
                    }
                    break;
                }
              }
              break;
            case MVN:
              // Rn = (0)(0)(0)(0)
              EMIT_TEXT_INSTR("%s, %s", register_names[Rd], register_names[Rm]);
              EMIT_TEXT_SHIFT_BY_IMM();
              break;
            default:
              EMIT_TEXT_INSTR("%s, %s, %s", register_names[Rd], register_names[Rn], register_names[Rm]);
              EMIT_TEXT_SHIFT_BY_IMM();
              break;
          }
        } else if ((opcode->operand_flags & OPND_IMM) == OPND_IMM) {
          uint32_t imm12 = DECODE_IMM12(binary_instr);
          uint32_t rotation = (imm12 >> 7) & 0x1E;
          uint32_t base_value = imm12 & 0xFF;

          // <mnemonic>{S}{<c>}{<q>} {<Rd>,} <Rn>, #<const>
          switch (opcode->opcode_flags & 0x1FFF) {
            case TST:
            case TEQ:
            case CMP:
            case CMN:
              // Rd = (0)(0)(0)(0)
              EMIT_TEXT_INSTR("%s, ", register_names[Rn]);
              EMIT_TEXT_IMM12();
              break;
            case MOV:
            case MVN:
              // Rn = (0)(0)(0)(0)
              EMIT_TEXT_INSTR("%s, ", register_names[Rd]);
              EMIT_TEXT_IMM12();
              break;
            default:
              EMIT_TEXT_INSTR("%s, %s, ", register_names[Rd], register_names[Rn]);
              EMIT_TEXT_IMM12();
              break;
          }
        } else { // OPND_REG_SHIFT_BY_REG
          uint8_t Rs = DECODE_REG(8, binary_instr);
          uint8_t Rm = DECODE_REG(0, binary_instr);
          uint8_t shift_type = DECODE_SHIFT_TYPE(binary_instr);

          // <mnemonic>{S}{<c>}{<q>} {<Rd>,} <Rn>, <Rm>, <type> <Rs>
          switch (opcode->opcode_flags & 0x1FFF) {
            case TST:
            case TEQ:
            case CMP:
            case CMN:
              // Rd = (0)(0)(0)(0)
              EMIT_TEXT_INSTR(
                  "%s, %s, %s %s\n",
                  register_names[Rn], register_names[Rm], shift_types[shift_type], register_names[Rs]);
              break;
            case MOV:
              // Rn = (0)(0)(0)(0)
              EMIT_TEXT_PSEUDO_INSTR(
                  shift_types[shift_type], "%s, %s, %s\n",
                  register_names[Rd], register_names[Rm], register_names[Rs]);
              break;
            case MVN:
              // Rn = (0)(0)(0)(0)
              EMIT_TEXT_INSTR(
                  "%s, %s, %s %s\n",
                  register_names[Rd], register_names[Rm], shift_types[shift_type], register_names[Rs]);
              break;
            default:
              EMIT_TEXT_INSTR(
                  "%s, %s, %s, %s %s\n",
                  register_names[Rd], register_names[Rn], register_names[Rm], shift_types[shift_type], register_names[Rs]);
              break;
          }
        }
        break;
      }
      case BRANCH: {
        switch (opcode->opcode_flags & 0x1FFF) {
          case B:
          case BL: {
            uint32_t imm24 = DECODE_IMM24(binary_instr);
            if (cond == 0xF) { // becomes BLX by immediate
              // imm32 = SignExtend(imm24:H:’0’, 32);
              uint32_t H0 = (binary_instr >> 23) & 0x2;
              uint32_t imm32 = (imm24 << 2) | H0;
              SIGN_EXTEND_32(imm32, 26);
              uint32_t branch_address = stream_addr + (int32_t)imm32 + 8;
              EMIT_TEXT_PSEUDO_INSTR("blx", "%x\n", branch_address);
            } else {
              // imm32 = SignExtend(imm24:’00’, 32);
              uint32_t imm32 = imm24 << 2;
              SIGN_EXTEND_32(imm32, 26);
              uint32_t branch_address = stream_addr + (int32_t)imm32 + 8;
              EMIT_TEXT_INSTR("%x\n", branch_address);
            }
            break;
          }
          case BX:
          case BLX: {
            uint8_t Rm = DECODE_REG(0, binary_instr);
            EMIT_TEXT_INSTR("%s\n", register_names[Rm]);
            break;
          }
        }
        break;
      }
      case LOAD_STORE:
        EMIT_TEXT_INSTR(" ...\n");
        break;
      case MULTI_LOAD_STORE:
        EMIT_TEXT_INSTR(" ...\n");
        break;
      case STATUS:
        EMIT_TEXT_INSTR(" ...\n");
        break;
      case COPROCESSOR:
        EMIT_TEXT_INSTR(" ...\n");
        break;
      case MISC:
        EMIT_TEXT_INSTR(" ...\n");
        break;
      default:
        fllprintf(out, "0x%x: <UNRECOGNIZED>\n", stream_addr);
        break;
    }

    stream_addr += 4;
  }
}

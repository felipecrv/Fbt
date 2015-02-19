#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "../generic/fbt_libc.h"
#include "../generic/fbt_llio.h"
#include "../fbt_disassemble.h"
#include "../fbt_datatypes.h"
#include "../fbt_translate.h"
#ifdef ARM_DISASSEMBLER
// Debugging is disabled for the ARM disassembler
# define PRINT_DEBUG_FUNCTION_START(...)
# define PRINT_DEBUG_FUNCTION_END(...)
# define PRINT_DEBUG(...)
#else
# include "../fbt_debug.h"
#endif

// inclusion of the fbt_opcode_tables.h
#include "fbt_arm_opcode.h"  // for struct arm_opcode and definitions
#ifdef ARM_DISASSEMBLER
// The disassembler doesn't call any action, so we simply define empty actions
// to make the compiler happy.
#define DEFINE_EMPTY_ACTION(action_name) \
  static enum translation_state action_##action_name \
  (struct translate *ts __attribute__((unused))) { \
    return NEUTRAL; \
  }
DEFINE_EMPTY_ACTION(copy)
DEFINE_EMPTY_ACTION(warn)
DEFINE_EMPTY_ACTION(branch)
DEFINE_EMPTY_ACTION(branch_and_link)
#else
# include "../fbt_actions.h"  // for the actions
#endif
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

static struct arm_opcode *fbt_opcode_table_lookup(uint32_t binary_instr);

static struct arm_opcode *fbt_opcode_table_lookup(uint32_t binary_instr) {
  uint32_t opcode_table_key =
    ((binary_instr >> 16) & 0xFF0) | ((binary_instr >> 4) & 0xF);
  return &default_opcode_table[opcode_table_key];
}

void fbt_disasm_instr(struct translate *ts) {
  PRINT_DEBUG_FUNCTION_START("fbt_disasm_instr(*ts=%p)", ts);

  Code *cur = (ts->cur_instr = ts->next_instr);

  uint32_t binary_instr = *cur;
  const struct arm_opcode *opcode = fbt_opcode_table_lookup(binary_instr);

  PRINT_DEBUG("Disassembling %p: %p -- a '%s'", cur, binary_instr, opcode->mnemonic);

  /* set the action */
  ts->cur_instr_info = opcode;

  ts->next_instr = cur + 1;
  PRINT_DEBUG_FUNCTION_END("");
}

void fbt_disassemble_to_text(uint32_t *instr_stream,
                             uint32_t size,
                             uint32_t start_addr,
                             int out,
                             bool with_sugar) {
#define EMIT_TEXT_CODE(code) fllwrite(out, (code))
#define EMIT_TEXT_CODEF(fmt, args...) fllprintf(out, (fmt), ##args)

  uint32_t stream_addr = start_addr;

  for (uint32_t instr_idx = 0; instr_idx < size; instr_idx++) {
    uint32_t binary_instr = instr_stream[instr_idx];
    struct arm_opcode *opcode = fbt_opcode_table_lookup(binary_instr);
    uint32_t cond = DECODE_COND(binary_instr);

#define EMIT_TEXT_INSTRF(fmt, args...) \
    EMIT_TEXT_CODEF("%x:  %.8x    %s%s\t" fmt, \
        stream_addr, binary_instr, opcode->mnemonic, textual_conds[(cond)], ##args); \

#define EMIT_TEXT_PSEUDO_INSTRF(mnemonic, fmt, args...) \
    EMIT_TEXT_CODEF("%x:  %.8x    %s%s%s\t" fmt, \
        stream_addr, binary_instr, (mnemonic), \
        (opcode->opcode_flags & SET_APSR) == SET_APSR ? "s" : "", textual_conds[(cond)], \
        ##args)

#define EMIT_TEXT_IMM12_WITH_ROTATION() \
    do { \
      if (rotation == 0) { \
        EMIT_TEXT_CODEF("#%d", base_value); \
      } else { \
        EMIT_TEXT_CODEF("#%d, %d", base_value, rotation); \
      } \
      uint32_t imm32 = rotate_right(base_value, rotation); \
      if (imm32) { \
        EMIT_TEXT_CODEF("  ; 0x%x\n", imm32); \
      } else { \
        EMIT_TEXT_CODE("\n"); \
      } \
    } while(0)

#define EMIT_TEXT_SHIFT_BY_IMM(suffix) \
    do { \
      switch (shift_type) { \
        case 0x0: \
          if (imm5 != 0) { \
            EMIT_TEXT_CODEF(", lsl #%d%s", imm5, (suffix)); \
          } else { \
            EMIT_TEXT_CODE((suffix)); \
          } \
          break; \
        case 0x1: \
          EMIT_TEXT_CODEF(", lsr #%d%s", (imm5 == 0) ? 32 : imm5, (suffix)); \
          break; \
        case 0x2: \
          EMIT_TEXT_CODEF(", asr #%d%s", (imm5 == 0) ? 32 : imm5, (suffix)); \
          break; \
        case 0x3: \
          if (imm5 == 0) { \
            EMIT_TEXT_CODEF(", rrx%s", (suffix)); \
          } else { \
            EMIT_TEXT_CODEF(", ror #%d%s", imm5, (suffix)); \
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
              EMIT_TEXT_INSTRF("%s, %s", register_names[Rn], register_names[Rm]);
              EMIT_TEXT_SHIFT_BY_IMM("\n");
              break;
            case MOV:
              // Rn = (0)(0)(0)(0)
              if (((uint8_t) ((binary_instr >> 5) & 0x7F)) == 0) { // imm5 . type == 0
                EMIT_TEXT_INSTRF("%s, %s\n", register_names[Rd], register_names[Rm]);
              } else {
                switch (shift_type) {
                  case 0x0:
                    EMIT_TEXT_PSEUDO_INSTRF(
                        "lsl", "%s, %s, #%d\n",
                        register_names[Rd], register_names[Rm], imm5);
                    break;
                  case 0x1:
                    EMIT_TEXT_PSEUDO_INSTRF(
                        "lsr", "%s, %s, #%d\n",
                        register_names[Rd], register_names[Rm], (imm5 == 0) ? 32 : imm5);
                    break;
                  case 0x2:
                    EMIT_TEXT_PSEUDO_INSTRF(
                        "asr", "%s, %s, #%d\n",
                        register_names[Rd], register_names[Rm], (imm5 == 0) ? 32 : imm5);
                    break;
                  case 0x3:
                    if (imm5 == 0) {
                      EMIT_TEXT_PSEUDO_INSTRF("rrx", "%s, %s\n", register_names[Rd], register_names[Rm]);
                    } else {
                      EMIT_TEXT_PSEUDO_INSTRF(
                          "ror", "%s, %s, #%d\n",
                          register_names[Rd], register_names[Rm], imm5);
                    }
                    break;
                }
              }
              break;
            case MVN:
              // Rn = (0)(0)(0)(0)
              EMIT_TEXT_INSTRF("%s, %s", register_names[Rd], register_names[Rm]);
              EMIT_TEXT_SHIFT_BY_IMM("\n");
              break;
            default:
              EMIT_TEXT_INSTRF("%s, %s, %s", register_names[Rd], register_names[Rn], register_names[Rm]);
              EMIT_TEXT_SHIFT_BY_IMM("\n");
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
              EMIT_TEXT_INSTRF("%s, ", register_names[Rn]);
              EMIT_TEXT_IMM12_WITH_ROTATION();
              break;
            case MOV:
            case MVN:
              // Rn = (0)(0)(0)(0)
              EMIT_TEXT_INSTRF("%s, ", register_names[Rd]);
              EMIT_TEXT_IMM12_WITH_ROTATION();
              break;
            default:
              EMIT_TEXT_INSTRF("%s, %s, ", register_names[Rd], register_names[Rn]);
              EMIT_TEXT_IMM12_WITH_ROTATION();
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
              EMIT_TEXT_INSTRF(
                  "%s, %s, %s %s\n",
                  register_names[Rn], register_names[Rm], shift_types[shift_type], register_names[Rs]);
              break;
            case MOV:
              // Rn = (0)(0)(0)(0)
              EMIT_TEXT_PSEUDO_INSTRF(
                  shift_types[shift_type], "%s, %s, %s\n",
                  register_names[Rd], register_names[Rm], register_names[Rs]);
              break;
            case MVN:
              // Rn = (0)(0)(0)(0)
              EMIT_TEXT_INSTRF(
                  "%s, %s, %s %s\n",
                  register_names[Rd], register_names[Rm], shift_types[shift_type], register_names[Rs]);
              break;
            default:
              EMIT_TEXT_INSTRF(
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
              EMIT_TEXT_PSEUDO_INSTRF("blx", "%x\n", branch_address);
            } else {
              // imm32 = SignExtend(imm24:’00’, 32);
              uint32_t imm32 = imm24 << 2;
              SIGN_EXTEND_32(imm32, 26);
              uint32_t branch_address = stream_addr + (int32_t)imm32 + 8;
              EMIT_TEXT_INSTRF("%x\n", branch_address);
            }
            break;
          }
          case BX:
          case BLX: {
            uint8_t Rm = DECODE_REG(0, binary_instr);
            EMIT_TEXT_INSTRF("%s\n", register_names[Rm]);
            break;
          }
        }
        break;
      }
      case LOAD_STORE: {
        uint8_t Rn = DECODE_REG(16, binary_instr);
        uint8_t Rt = DECODE_REG(12, binary_instr);

        bool increment = opcode->operand_flags & OPND_INCR_OFFSET;

        if ((opcode->operand_flags & OPND_REG_OFFSET_SHIFT_BY_IMM) == OPND_REG_OFFSET_SHIFT_BY_IMM) {
          uint8_t Rm = DECODE_REG(0, binary_instr);
          uint8_t imm5 = DECODE_IMM5(7, binary_instr);
          uint8_t shift_type = DECODE_SHIFT_TYPE(binary_instr);

          if (opcode->operand_flags & OPND_PRE_INDEX) {
            bool write_back = opcode->operand_flags & OPND_WRITE_BACK;

            if (increment) {
              EMIT_TEXT_INSTRF("%s, [%s, %s", register_names[Rt], register_names[Rn], register_names[Rm]);
            } else {
              EMIT_TEXT_INSTRF("%s, [%s, -%s", register_names[Rt], register_names[Rn], register_names[Rm]);
            }
            static char with_write_back[] = "]!\n";
            static char no_write_back[] = "]\n";
            const char *suffix = write_back ? with_write_back : no_write_back;
            EMIT_TEXT_SHIFT_BY_IMM(suffix);
          } else {
            if (increment) {
              EMIT_TEXT_INSTRF("%s, [%s], %s", register_names[Rt], register_names[Rn], register_names[Rm]);
            } else {
              EMIT_TEXT_INSTRF("%s, [%s], -%s", register_names[Rt], register_names[Rn], register_names[Rm]);
            }
            EMIT_TEXT_SHIFT_BY_IMM("\n");
          }
        } else if ((opcode->operand_flags & OPND_IMM_OFFSET) == OPND_IMM_OFFSET) {
          int32_t imm12 = DECODE_IMM12(binary_instr);
          if (!increment) {
            imm12 = -imm12;
          }

          if (opcode->operand_flags & OPND_PRE_INDEX) {
            bool write_back = opcode->operand_flags & OPND_WRITE_BACK;

            if (write_back) {
              EMIT_TEXT_INSTRF("%s, [%s, #%d]!\n", register_names[Rt], register_names[Rn], imm12);
            } else {
              if (imm12 == 0) {
                EMIT_TEXT_INSTRF("%s, [%s]\n", register_names[Rt], register_names[Rn]);
              } else {
                EMIT_TEXT_INSTRF("%s, [%s, #%d]\n", register_names[Rt], register_names[Rn], imm12);
              }
            }
          } else {
            EMIT_TEXT_INSTRF("%s, [%s], #%d\n", register_names[Rt], register_names[Rn], imm12);
          }
        } else {
          // If this block is reached, there's a bug
          EMIT_TEXT_INSTRF("_____");
        }
        break;
      }
      case LOAD_STORE_EXT: {
        uint8_t Rn = DECODE_REG(16, binary_instr);
        uint8_t Rt = DECODE_REG(12, binary_instr);
        bool increment = opcode->operand_flags & OPND_INCR_OFFSET;

        switch (opcode->opcode_flags & INSTR_LS_DATATYPE_MASK) {
          case INSTR_WORD_LS:
          case INSTR_BYTE_LS:
          case INSTR_HALFWORD_LS:
          case INSTR_SIGNED_BYTE_LS:
          case INSTR_SIGNED_HALFWORD_LS:
            EMIT_TEXT_INSTRF("%s, [%s", register_names[Rt], register_names[Rn]);
            break;
          case INSTR_DUAL_LS: {
            uint8_t Rt2 = DECODE_REG(8, binary_instr);
            EMIT_TEXT_INSTRF("%s, %s, [%s", register_names[Rt], register_names[Rt2], register_names[Rn]);
            break;
          }
          default:
            // If this block is reached, there's a bug
            EMIT_TEXT_INSTRF("_____");
            break;
        }

        if (opcode->operand_flags & OPND_REG_OFFSET) {
          uint8_t Rm = DECODE_REG(0, binary_instr);

          if (opcode->operand_flags & OPND_PRE_INDEX) {
            bool write_back = opcode->operand_flags & OPND_WRITE_BACK;
            if (increment) {
              EMIT_TEXT_CODEF(", %s]%s", register_names[Rm], write_back ? "!\n" : "\n");
            } else {
              EMIT_TEXT_CODEF(", -%s]%s", register_names[Rm], write_back ? "!\n" : "\n");
            }
          } else {
            if (increment) {
              EMIT_TEXT_CODEF("], %s\n", register_names[Rm]);
            } else {
              EMIT_TEXT_CODEF("], -%s\n", register_names[Rm]);
            }
          }
        } else {
          assert(opcode->operand_flags & OPND_IMM_OFFSET);
          int32_t imm = ((binary_instr >> 4) & 0xF0) | (binary_instr & 0xF);
          if (!increment) {
            imm = -imm;
          }

          if (opcode->operand_flags & OPND_PRE_INDEX) {
            if (opcode->operand_flags & OPND_WRITE_BACK) {
              EMIT_TEXT_CODEF(", %d]!\n", imm);
            } else {
              if (imm == 0) {
                EMIT_TEXT_CODEF("]\n");
              } else {
                EMIT_TEXT_CODEF(", %d]\n", imm);
              }
            }
          } else {
            EMIT_TEXT_CODEF("], %d\n", imm);
          }
        }
        break;
      }
      case MULTI_LOAD_STORE: {
        uint8_t Rn = DECODE_REG(16, binary_instr);
        uint32_t register_list = binary_instr & 0xFFFF;

        bool write_back = opcode->operand_flags & OPND_WRITE_BACK;

        if (with_sugar && Rn == SP && write_back) {
          switch (opcode->opcode_flags) {
          case LDMIA:
            EMIT_TEXT_PSEUDO_INSTRF("pop", "");
            break;
          case STMDB:
            EMIT_TEXT_PSEUDO_INSTRF("push", "");
            break;
          default:
            EMIT_TEXT_INSTRF("%s, ", register_names[Rn]);
            break;
          }
        } else {
          EMIT_TEXT_INSTRF("%s%s, ", register_names[Rn], write_back ? "!" : "");
        }

        // Register list
        uint8_t reg_i = 0;
        while ((register_list & 0x1) == 0) {
          register_list = register_list >> 1;
          reg_i++;
        }
        EMIT_TEXT_CODEF("{%s", register_names[reg_i]);
        do {
          register_list = register_list >> 1;
          reg_i++;
          if (register_list & 0x1) {
            EMIT_TEXT_CODEF(", %s", register_names[reg_i]);
          }
        } while (register_list);
        EMIT_TEXT_CODE("}\n");
        break;
      }
      case STATUS:
        EMIT_TEXT_INSTRF(" ...\n");
        break;
      case COPROCESSOR:
        EMIT_TEXT_INSTRF(" ...\n");
        break;
      case MISC:
        EMIT_TEXT_INSTRF(" ...\n");
        break;
      default:
        fllprintf(out, "0x%x: <UNRECOGNIZED>\n", stream_addr);
        break;
    }

    stream_addr += 4;
  }
}

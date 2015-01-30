#ifndef ARM_OPCODE_H
#define ARM_OPCODE_H

#include <string>

#include "arm/fbt_arm_opcode.h"

/*
 * This struct is used to store opcode information for the table generator.
 * Arrays of `instr_description` are the input of the table generator to
 * generate more machine-friendly (aka efficient) lookup tables.
 */
typedef struct instr_description_s {
  /*
   * if the 27-20 bits aren't enough to determine the opcode
   * continue the lookup in this other table
   */
  struct instr_description_s *table;

  /* The mnemonic */
  std::string mnemonic;

  /* opcode_flags: tells the instruction and its group (e.g. DATA_ARITH | ADD,
   * LOAD_STORE | LDR...) */
  unsigned int opcode_flags;

  /* flags for the operands */
  unsigned int operand_flags;

  /* the following is specific to the table generator */
  std::string default_action;
  std::string comment;
} instr_description;

#endif  /* ARM_OPCODE_H */

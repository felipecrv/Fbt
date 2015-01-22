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

  /* the following hold flags for the operands */
  /* the value NONE means the opcode does not make use of this operand */
  //unsigned int dest_flags;
  //unsigned int operand1_flags;
  //unsigned int operand2_flags;

  /* the following hold flags for the implizit operands */
  /* do not reley on the these values if an argument is not implizit */
  //unsigned int implDestFlags;
  //unsigned int implSrcFlags;
  //unsigned int implAuxFlags;*/

  /* the following is specific to the table generator */
  std::string defaultAction;
  std::string comment;

} instr_description;


/* how is the opeand used in this instruction */
#define   RWX             0x00000007
#define   READ            0x00000001    /* operand is read */
#define   WRITE           0x00000002    /* operand is written */
#define   MODIFY          READ | WRITE  /* operand is modified */
#define   EXECUTE         0x00000004    /* operand is executed */

/* These masks define how registers are represented in the translator */
#define   REG_IDX_MASK    0x0000000F
#define   REG_TYPE_MASK   0x000000F0

/* register types */
#define   WORD_REG        0x00000010

/* These masks define how instruction constants are represented in the
 * translator */
#define   INS_TYPE_MASK       0x0000FFFF
#define   INS_GROUP_MASK      0x0000F000
//#define   INS_PREFIX_MASK     0x0FFF0000


#endif  /* ARM_OPCODE_H */

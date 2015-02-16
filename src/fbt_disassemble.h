#ifndef FBT_DISASSEMBLE_H
#define FBT_DISASSEMBLE_H

#include "fbt_datatypes.h"

void fbt_disasm_instr(struct translate *ts);

#if defined(__arm__) || defined(ARM_DISASSEMBLER)
# include "arm/fbt_disassemble.h"
#endif

#endif  /* FBT_DISASSEMBLE_H */

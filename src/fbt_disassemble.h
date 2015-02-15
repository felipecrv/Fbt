#ifndef FBT_DISASSEMBLE_H
#define FBT_DISASSEMBLE_H

#ifdef __arm__
# include "arm/fbt_disassemble.h"
#endif

#include "fbt_datatypes.h"

void fbt_disasm_instr(struct translate *ts);

#endif  /* FBT_DISASSEMBLE_H */

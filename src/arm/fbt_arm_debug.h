#ifndef ARM_FBT_ARM_DEBUG_H
#define ARM_FBT_ARM_DEBUG_H

#ifndef FBT_DEBUG_H
# error "Don't include arm/fbt_arm_debug.h directly, include fbt_debug.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

// TODO(philix): dump ARM generated code
/* do not dump generated code */
#define DUMP_START()
#define DUMP_END()
#define DUMP_CODE(ts, instr_len, transl_len)
#define DUMP_JMP_TABLE_ENTRY(org_addr, transl_addr)

#ifdef __cplusplus
}
#endif

#endif  /* ARM_FBT_ARM_DEBUG_H */

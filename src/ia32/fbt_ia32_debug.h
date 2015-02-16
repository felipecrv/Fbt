#ifndef IA32_FBT_IA32_DEBUG_H
#define IA32_FBT_IA32_DEBUG_H

#ifndef FBT_DEBUG_H
# error "Don't include ia32/fbt_ia32_debug.h directly, include fbt_debug.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DUMP_GENERATED_CODE
/* dump generated code */
void debug_dump_start();
void debug_dump_end();
void debug_dump_code(struct translate *ts, int instr_len, int transl_len);
void debug_dump_jmptable(char *orig_addr, char *transl_addr);
#define DUMP_START() debug_dump_start()
#define DUMP_END() debug_dump_end()
#define DUMP_CODE(ts, instr_len, transl_len) \
  debug_dump_code(ts, instr_len, transl_len)
#define DUMP_JMP_TABLE_ENTRY(org_addr, transl_addr) \
  debug_dump_jmptable(org_addr, transl_addr)
#else
/* do not dump generated code */
#define DUMP_START()
#define DUMP_END()
#define DUMP_CODE(ts, instr_len, transl_len)
#define DUMP_JMP_TABLE_ENTRY(org_addr, transl_addr)
#endif

#ifdef __cplusplus
}
#endif

#endif  /* IA32_FBT_IA32_DEBUG_H */

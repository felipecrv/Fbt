
#include <sys/fcntl.h>
#include <pthread.h>

#include "../fbt_debug.h"
#include "../fbt_datatypes.h"
#include "../fbt_code_cache.h"
#include "../generic/fbt_libc.h"
#include "fbt_x86_opcode.h"

#ifdef DUMP_GENERATED_CODE
static pthread_mutex_t dump_mutex  = PTHREAD_MUTEX_INITIALIZER;
static int dumpCodeStream = 0;
static int dumpJmpTableStream = 0;

/** Number of threads using the dump stream */
static long dump_references = 0;

static int printOperandString(int f, const unsigned int operandFlags,
                              const unsigned char implOperandFlags,
                              const unsigned char tableFlags,
                              const unsigned char operandSize,
                              struct translate* ts, unsigned int instr_len);

void print_disasm_inst(int f, struct translate* ts, unsigned int instr_len);

void debug_dump_start()
{
  pthread_mutex_lock(&dump_mutex);
  dump_references += 1;

  if (dumpCodeStream == 0) {
    fbt_open(CODE_DUMP_FILE_NAME,
             O_CREAT | O_TRUNC | O_WRONLY,
             S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH,
             dumpCodeStream);
    SYSCALL_SUCCESS_OR_SUICIDE_STR(
        dumpCodeStream, "Could not open dump file (debug_dump_start: ia32/fbt_ia32_debug.c)\n");
  }
  if (dumpJmpTableStream == 0) {
    fbt_open(JMP_TABLE_DUMP_FILE_NAME,
             O_CREAT | O_TRUNC | O_WRONLY,
             S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH,
             dumpJmpTableStream);
    SYSCALL_SUCCESS_OR_SUICIDE_STR(
        dumpJmpTableStream, "Could not open jmptable file (debug_dump_start: ia32/fbt_ia32_debug.c)\n");
  }
  pthread_mutex_unlock(&dump_mutex);
}

void debug_dump_end()
{
  pthread_mutex_lock(&dump_mutex);
  dump_references -= 1;
  int destroy = dump_references == 0;
  pthread_mutex_unlock(&dump_mutex);

  if (destroy) {
    //pthread_mutex_destroy(&dump_mutex);
    int ret;
    fbt_close(dumpCodeStream, ret);
    SYSCALL_SUCCESS_OR_SUICIDE_STR(
        ret, "Could not close code dump file (debug_dump_end: ia32/fbt_ia32_debug.c)\n");
    fbt_close(dumpJmpTableStream, ret);
    SYSCALL_SUCCESS_OR_SUICIDE_STR(
        ret, "Could not close jmptable file (debug_dump_end: ia32/fbt_ia32_debug.c)\n");
    dumpCodeStream = 0;
    dumpJmpTableStream = 0;
  }
}

void debug_dump_code(struct translate *ts, int instr_len, int transl_len)
{
  if (dumpCodeStream == 0) {
    fbt_suicide_str("Dump stream is not open.\n");
  }

  pthread_mutex_lock(&dump_mutex);
  /* print address of instruction */
  fllprintf(dumpCodeStream, "0x%.8x: ", (unsigned long)ts->cur_instr);
  print_disasm_inst(dumpCodeStream, ts, instr_len);
  fllprintf(dumpCodeStream, "--> %p (%d)\n", (char*)(ts->transl_instr-transl_len), transl_len);
  /*fflush(dumpCodeStream);*/
  pthread_mutex_unlock(&dump_mutex);
}

void debug_dump_jmptable(char *orig_addr, char *transl_addr)
{
  if (dumpCodeStream == 0) {
    fbt_suicide_str("Jmptable stream is not open.\n");
  }

  pthread_mutex_lock(&dump_mutex);
  fllprintf(dumpJmpTableStream, "0x%x %p --> %p\n",
            C_MAPPING_FUNCTION((long)orig_addr),
            (void*)orig_addr,
            (void*)transl_addr);
  /*fsync(dumpJmpTableStream);*/
  pthread_mutex_unlock(&dump_mutex);
}

/* implizit operand masks */
#define		REG_IDX_MASK		0x0000000F
#define		REG_TYPE_MASK		0x000000F0
static int printOperandString(int f, const unsigned int operandFlags,
                              const unsigned char implOperandFlags,
                              const unsigned char tableFlags,
                              const unsigned char operandSize,
                              struct translate* ts,
                              unsigned int instr_len)
{

  /* tables with the names of the registers */
  static const char const
  *register_names[10][8]={
    { "al",    "cl",    "dl",    "bl",    "ah",    "ch",    "dh",    "bh"    },
    { "ax",    "cx",    "dx",    "bx",    "sp",    "bp",    "si",    "di"    },
    { "eax",   "ecx",   "edx",   "ebx",   "esp",   "ebp",   "esi",   "edi"   },
    { "mm0",   "mm1",   "mm2",   "mm3",   "mm4",   "mm5",   "mm6",   "mm7"   },
    { "xmm0",  "xmm1",  "xmm2",  "xmm3",  "xmm4",  "xmm5",  "xmm6",  "xmm7"  },
    { "es",    "cs",    "ss",    "ds",    "fs",    "gs",    "ERR",   "ERR"   },
    { "tr0",   "tr1",   "tr2",   "tr3",   "tr4",   "tr5",   "tr6",   "tr7"   },
    { "st(0)", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)" },
    /* only ring 0 */
    { "cr0",   "ERR",   "cr2",   "cr3",   "cr4",   "ERR",   "ERR",   "ERR"   },
    /* only ring 0 */
    { "dr0",   "dr1",   "dr2",   "dr3",   "dr4",   "dr5",   "dr6",   "dr7"   }
  };
  unsigned char prefix = 0x0;
  const char const *seg_ovr = NULL;
  if (ts->num_prefixes!=0) {
    prefix = *(ts->cur_instr);
    int nriters = 0;
    /* look out for a prefix we handle */
    for (nriters = 0; nriters < ts->num_prefixes; ++nriters) {
      unsigned char cur_prefix = *(ts->cur_instr+nriters);
      if ((cur_prefix == PREFIX_ADDR_SZ_OVR) || (cur_prefix == PREFIX_OP_SZ_OVR))
        prefix = cur_prefix;
      if (prefix == PREFIX_ES_SEG_OVR) seg_ovr = register_names[5][0];
      if (prefix == PREFIX_CS_SEG_OVR) seg_ovr = register_names[5][1];
      if (prefix == PREFIX_SS_SEG_OVR) seg_ovr = register_names[5][2];
      if (prefix == PREFIX_DS_SEG_OVR) seg_ovr = register_names[5][3];
      if (prefix == PREFIX_FS_SEG_OVR) seg_ovr = register_names[5][4];
      if (prefix == PREFIX_GS_SEG_OVR) seg_ovr = register_names[5][5];
    }
  }

  int len = 0;
  if (seg_ovr != NULL && hasMemOp(operandFlags)) {
    len += fllprintf(f, "%%");
    len += fllprintf(f, seg_ovr);
    len += fllprintf(f, ":");
  }

  if (implOperandFlags!=NONE) {
    /* implicit operands */
    if (!(implOperandFlags & REG_TYPE_MASK)) {
      len += fllprintf(f, "$%d", implOperandFlags & REG_IDX_MASK);
      return len;
    } else {
      int table_select = ((implOperandFlags&REG_TYPE_MASK)>>4)-1;
      if (prefix==PREFIX_OP_SZ_OVR || prefix==PREFIX_ADDR_SZ_OVR)
        table_select--;
      len += fllprintf(f, "%%%s",
                        register_names[table_select][(implOperandFlags &
                                                      REG_IDX_MASK)]);
      return len;
    }
  } else if (hasImmOp(operandFlags)) {
    /* immediate operands (after whole instruction) */
    if (operandFlags & EXECUTE) {
      len += fllprintf(f,"+");
    } else if (hasMemOp(operandFlags) && !(operandFlags & EXECUTE)) {
      len += fllprintf(f,"(");
    } else {
      len += fllprintf(f,"$");
    }
    len += fllprintf(f,"0x");
    unsigned char *startaddr = (ts->cur_instr + instr_len - operandSize);
    switch (operandSize) {
    case 1:
      len += fllprintf(f, "%.2x", *(startaddr));
      break;
    case 2:
      len += fllprintf(f, "%.4x", *((unsigned short*)startaddr));
      break;
    case 4:
      len += fllprintf(f, "%.8x", *((unsigned int*)startaddr));
      break;
    default:
      len += fllprintf(f, "not supported");
    }
    if (hasMemOp(operandFlags) && !(operandFlags&EXECUTE)) {
      len += fllprintf(f,")");
    }
    return len;
  } else if (tableFlags&HAS_MODRM) {
    /* modrm byte */
    if (ModRMparseRM(operandFlags)) {
      /* we read our information from the RM part, this is the regular 'free'
         option */
      int table_select = 0;
      switch (operandFlags&OP_ADDRM_MASK) {
      case ADDRM_E:
      case ADDRM_M:
      case ADDRM_R:
        table_select = 2;
        break;
      case ADDRM_Q:
      case ADDRM_U:
      case ADDRM_W:
        table_select = 4;
        break;
      }
      if (prefix==PREFIX_OP_SZ_OVR || prefix==PREFIX_ADDR_SZ_OVR)
        table_select--;
      unsigned char modrm = *(ts->first_byte_after_opcode);
      /* decode ModRM byte */
      if (MODRM_MOD(modrm)==0x3) {
        /* only regs - plain and simple, just print it */
        len += fllprintf(f, "%%%s",
                         register_names[table_select][MODRM_RM(modrm)]);
      } else if (MODRM_MOD(modrm)==0 && MODRM_RM(modrm)==5) {
        /* special disp32 - we just print int */
        len += fllprintf(f, "%.8x",
                         *((unsigned int*)(ts->first_byte_after_opcode+1)));
      } else {
        if (prefix==PREFIX_ADDR_SZ_OVR) {
          return fllprintf(f, "ModRMERR");
        };
        /* we have some compination of disp and register and maybe a sib
           escape */
        /* offset for disp value */
        int dispstarts = (MODRM_RM(modrm)==4) ? 2 : 1;
        switch (MODRM_MOD(modrm)) {
        case 0:
          if (MODRM_RM(modrm)==4 &&
              SIB_BASE(*(ts->first_byte_after_opcode+1))==5) {
            /* sib byte includes a backward reference to an disp32 */
            len += fllprintf(f, "0x%.8x",
                             *((unsigned int*)(ts->first_byte_after_opcode +
                                               dispstarts)));
          }
          break;
        case 1:
          len += fllprintf(f, "0x%.2x", *(ts->first_byte_after_opcode +
                                          dispstarts));
          break;
        case 2:
          len += fllprintf(f, "0x%.8x",
                           *((unsigned int*)(ts->first_byte_after_opcode +
                                             dispstarts)));
          break;
        }
        len += fllprintf(f, "(");
        if (MODRM_RM(modrm)==4) {
          /* sib byte - we need to decode that as well */
          unsigned char sib = *(ts->first_byte_after_opcode+1);
          if (SIB_BASE(sib)!=5) {
            /* sib base register */
            len += fllprintf(f, "%%%s", register_names[2][SIB_BASE(sib)]);
          } else {
            /* special sib position */
            switch (MODRM_MOD(modrm)) {
            case 1:
            case 2:
              fllprintf(f, "%%ebp");
              len += 4;
            }
          }
          if (SIB_INDEX(sib)!=4) {
            /* print scaled index register */
            len += fllprintf(f, ", %%%s", register_names[2][SIB_INDEX(sib)]);
            switch (SIB_SCALE(sib)) {
              /* sib byte used to scale index */
            case 0:
              break;
            case 1:
              len+=fllprintf(f, "*2");
              break;
            case 2:
              len+=fllprintf(f, "*4");
              break;
            case 3:
              len+=fllprintf(f, "*8");
              break;
            }
          }
        } else {
          len += fllprintf(f, "%%%s",
                           register_names[table_select][MODRM_RM(modrm)]);
        }
        len += fllprintf(f, ")");
      }
      return len;
    } else if (ModRMparseREG(operandFlags)) {
      /* we parse the REG part of the ModRM byte, this is the more restricted
         option (the top column of the ModR/M table)
       */
      int table_select=0;
      switch (operandFlags&OP_ADDRM_MASK) {
      case ADDRM_G:
      case ADDRM_S:
        table_select = 2;
        break; /* unsure about S */
      case ADDRM_N:
      case ADDRM_V:
        table_select = 4;
        break;
        /* these two need ring 0 privs: */
      case ADDRM_C:
        table_select = 8;
        break;
      case ADDRM_D:
        table_select = 9;
        break;
      }
      unsigned char modrm = *(ts->first_byte_after_opcode);
      len += fllprintf(f, "%%%s",
                        register_names[table_select][MODRM_REG(modrm)]);
      return len;
    } else {
      /* although this instructions has a ModR/M byte,
         this argument (either dst, src, aux) does not use it*/
      return 0;
    }
  } else if ((operandFlags&ADDRM_X) == ADDRM_X) {
    return len + fllprintf(f, "%ds:(%esi)");
  } else if ((operandFlags&ADDRM_Y) == ADDRM_Y) {
    return len + fllprintf(f, "%es:(%edi)");
  }
  return 0;
}

/**
 * Prints instructions to the file (and disassembles it)
 */
void print_disasm_inst(int f, struct translate* ts,
                              unsigned int instr_len)
/* we need to pass instr_len of the current instruction because we can't trust
   the ts struct the problem is that a call instruction will tether next_instr
   and we cannot calculate the length of the current instruction by subtracting
   next_instr - cur_instr as next_instr will follow the call! so we need to pass
   the length as well!
 */
{
  unsigned int j, plen = 0, args = 0;
  fllprintf(f, "0x");
  for (j=0; j<instr_len; ++j) {
    fllprintf(f, "%.2x", (unsigned char)(*(ts->cur_instr+j)));
  }
  for (j=0; j<24-2*instr_len; ++j) {
    fllprintf(f, " ");
  }
  plen = fllprintf(f, "%s ", ts->cur_instr_info->mnemonic);

  if (ts->cur_instr_info->srcFlags) {
    plen += printOperandString(f, ts->cur_instr_info->srcFlags,
                               ts->cur_instr_info->implSrcFlags,
                               ts->cur_instr_info->tableFlags,
                               ts->src_operand_size, ts, instr_len);
    args = 1;
  }
  if (ts->cur_instr_info->auxFlags) {
    if (args) {
      plen+=fllprintf(f, ", ");
    }
    plen+=printOperandString(f, ts->cur_instr_info->auxFlags,
                             ts->cur_instr_info->implAuxFlags,
                             ts->cur_instr_info->tableFlags,
                             ts->aux_operand_size, ts, instr_len);
    args=1;
  }
  if (ts->cur_instr_info->destFlags) {
    if (args) {
      plen+=fllprintf(f, ", ");
    }
    plen+=printOperandString(f, ts->cur_instr_info->destFlags,
                             ts->cur_instr_info->implDestFlags,
                             ts->cur_instr_info->tableFlags,
                             ts->dest_operand_size, ts, instr_len);
  }

  if (plen<32) {
    for (j=0; j<32-plen; ++j) {
      fllprintf(f, " ");
    }
  } else {
      fllprintf(f, " ");
  }
}

#endif  /* DUMP_GENERATED_CODE */

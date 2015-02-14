#ifndef FBT_ARM_OPCODE
#define FBT_ARM_OPCODE

/* no flag */
#define NONE       0x00000000

/*
 * Instruction Groups & Instructions
 *
 * An extension of the groups defined in
 * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0204j/Cacbjbdg.html
 */
#define DATA_OTHER                0x00000000  // Data processing
#define DATA_ARITH                0x00000100  // Data processing: arithmetic
#define DATA_LOGIC                0x00000200  // Data processing: logical
#define DATA_COND                 0x00000300  // Data processing: conditional tests
#define BRANCH                    0x00000400  // Branch and control (EXEC on the ia32 version)
#define LOAD_STORE                0x00000500  // Register load and store
#define LOAD_STORE_EXT            0x00000600  // Register load and store (M-extension)
#define MULTI_LOAD_STORE          0x00000700  // Multiple register load and store
#define STATUS                    0x00000800  // Status register access
#define COPROCESSOR               0x00000900  // Coprocessor instructions
#define MISC                      0x00000A00

#define SET_APSR                  0x00001000
/* flags for load/store instructions */
#define INSTR_LS_DATATYPE_MASK    0x0000e000
// type/length of data being loaded/stored
#define INSTR_WORD_LS             0x00000000
#define INSTR_BYTE_LS             0x00002000
#define INSTR_HALFWORD_LS         0x00004000
#define INSTR_DUAL_LS             0x00006000
#define INSTR_SIGNED_BYTE_LS      0x00008000
#define INSTR_SIGNED_HALFWORD_LS  0x0000A000
// whether the load/store instruction is a store
#define INSTR_IS_STORE            0x00010000

/*
 * These constants are used as opcode_flags in the instruction structs.
 *
 *   ...   |      1 bit      |   3 bits    |   1 bit       | 4 bits |      8 bits
 * --------+-----------------+-------------+---------------+--------+-----------------
 *         | INSTR_IS_STORE  | LS_DATATYPE |  S (SET_APSR) | group  | id within group
 */
#define INSTR_GROUP_MASK   0xF00

/* operand flags for DATA instructions (AND, EOR, ADD, MOV...) */
#define OPND_IMM                          0x0001
#define OPND_REG_SHIFT_BY_IMM             0x0002
#define OPND_REG_SHIFT_BY_REG             0x0004
/* operand flags for LOAD_STORE instructions (LDR, STR...) */
#define OPND_IMM_OFFSET                   0x0001
#define OPND_REG_OFFSET_SHIFT_BY_IMM      0x0002
#define OPND_REG_OFFSET                   0x0004
#define OPND_PRE_INDEX                    0x0008
#define OPND_INCR_OFFSET                  0x0010
#define OPND_WRITE_BACK                   0x0020

/* DATA_OTHER group */
#define MOV        DATA_OTHER | 0x00
#define MVN        DATA_OTHER | 0x01
#define MOVS       MOV | SET_APSR
#define MVNS       MVN | SET_APSR
#define CLZ        DATA_OTHER | 0x02 // FIX: doesn't belong to data?

/* DATA_ARITH group */
#define SUB        DATA_ARITH | 0x00
#define RSB        DATA_ARITH | 0x01
#define ADD        DATA_ARITH | 0x02
#define ADC        DATA_ARITH | 0x03
#define SBC        DATA_ARITH | 0x04
#define RSC        DATA_ARITH | 0x05
// ADR (not listed) is a pseudo instruction
#define SUBS       SUB | SET_APSR
#define RSBS       RSB | SET_APSR
#define ADDS       ADD | SET_APSR
#define ADCS       ADC | SET_APSR
#define SBCS       SBC | SET_APSR
#define RSCS       RSC | SET_APSR

// FIX: doesn't belong to DATA?
/* general multiply instructions */
#define MLA        DATA_ARITH | 0x06
#define MLS        DATA_ARITH | 0x07 // available in ARMv6T2, ARMv7
#define MUL        DATA_ARITH | 0x08
#define MLAS       MLA | SET_APSR
#define MULS       MUL | SET_APSR

// FIX: doesn't belong to DATA?
/* Signed Multiply (halfwords) */
#define SMLABB     DATA_ARITH | 0x09
#define SMLABT     DATA_ARITH | 0x0A
#define SMLATB     DATA_ARITH | 0x0B
#define SMLATT     DATA_ARITH | 0x0C
/* Signed Multiply Accumulate Dual */
#define SMLAD      DATA_ARITH | 0x0D // available in ARMv6* (TODO: add to tables)
/* Signed Multiply Accumulate Long */
#define SMLAL      DATA_ARITH | 0x0E
/* Signed Multiply Accumulate Long (halfwords) */
#define SMLALBB    DATA_ARITH | 0x0F
#define SMLALBT    DATA_ARITH | 0x10
#define SMLALTB    DATA_ARITH | 0x11
#define SMLALTT    DATA_ARITH | 0x12
/* Signed Multiply Accumulate Long Dual */
#define SMLALD     DATA_ARITH | 0x13 // available in ARMv6T2, ARMv7
/* Signed Multiply Accumulate (word by halfword) */
#define SMLAWB     DATA_ARITH | 0x14
#define SMLAWT     DATA_ARITH | 0x15
/* Signed Multiply Subtract Dual */
#define SMLSD      DATA_ARITH | 0x16 // available in ARMv6* (TODO: add to tables)
/* Signed Multiply Subtract Lang Dual */
#define SMLSLD     DATA_ARITH | 0x17 // available in ARMv6* (TODO: add to tables)
/* Signed Most Significant Word Multiply Accumulate */
#define SMMLA      DATA_ARITH | 0x18 // available in ARMv6* (TODO: add to tables)
/* Signed Most Significant Word Multiply Subtract */
#define SMMLS      DATA_ARITH | 0x19 // available in ARMv6* (TODO: add to tables)
/* Signed Most Significant Word Multiply */
#define SMMUL      DATA_ARITH | 0x1A // available in ARMv6* (TODO: add to tables)
/* Signed Dual Multiply Add */
#define SMUAD      DATA_ARITH | 0x1B // available in ARMv6* (TODO: add to tables)
/* Signed Multiply (halfwords) */
#define SMULBB     DATA_ARITH | 0x1C
#define SMULBT     DATA_ARITH | 0x1D
#define SMULTB     DATA_ARITH | 0x1E
#define SMULTT     DATA_ARITH | 0x1F
/* Signed Multiply Long */
#define SMULL      DATA_ARITH | 0x20
#define SMULLS     SMULL | SET_APSR
/* Signed Multiply (word by halfword) */
#define SMULWB     DATA_ARITH | 0x21
#define SMULWT     DATA_ARITH | 0x22
/* Signed Dual Multiply Subtract */
#define SMUSD      DATA_ARITH | 0x23 // available in ARMv6* (TODO: add to tables)

/* Unsigned Multiply Accumulate Accumulate Long */
#define UMAAL      DATA_ARITH | 0x24 // available in ARMv6* (TODO: add to tables)
/* Unsigned Multiply Accumulate Long */
#define UMLAL      DATA_ARITH | 0x25
#define UMLALS     UMLAL | SET_APSR
/* Unsigned Multiply Long */
#define UMULL      DATA_ARITH | 0x26
#define UMULLS     UMULL | SET_APSR

// FIX: doesn't belong to DATA?
/* Saturating addition and subtraction instructions */
#define QADD       DATA_ARITH | 0x27
#define QSUB       DATA_ARITH | 0x28
#define QDADD      DATA_ARITH | 0x29
#define QDSUB      DATA_ARITH | 0x2A

/* DATA_LOGIC group */
#define AND        DATA_LOGIC | 0x00
#define EOR        DATA_LOGIC | 0x01
#define ORR        DATA_LOGIC | 0x02
#define BIC        DATA_LOGIC | 0x03
#define ANDS       AND | SET_APSR
#define EORS       EOR | SET_APSR
#define ORRS       ORR | SET_APSR
#define BICS       BIC | SET_APSR

/* DATA_COND group */
#define TST        DATA_COND | 0x00
#define TEQ        DATA_COND | 0x02
#define CMP        DATA_COND | 0x03
#define CMN        DATA_COND | 0x04
#define TSTS       TST | SET_APSR
#define TEQS       TEQ | SET_APSR
#define CMPS       CMP | SET_APSR
#define CMNS       CMN | SET_APSR

/* BRANCH group */
#define B          BRANCH | 0x00
#define BX         BRANCH | 0x01
#define BL         BRANCH | 0x02
#define BLX        BRANCH | 0x03

/* LOAD_STORE group */
#define STR        LOAD_STORE | 0x00 | INSTR_WORD_LS | INSTR_IS_STORE
#define LDR        LOAD_STORE | 0x01 | INSTR_WORD_LS
#define STRB       LOAD_STORE | 0x02 | INSTR_BYTE_LS | INSTR_IS_STORE
#define LDRB       LOAD_STORE | 0x03 | INSTR_BYTE_LS
#define STRT       LOAD_STORE | 0x04 | INSTR_WORD_LS | INSTR_IS_STORE
#define LDRT       LOAD_STORE | 0x05 | INSTR_WORD_LS
#define STRBT      LOAD_STORE | 0x06 | INSTR_BYTE_LS | INSTR_IS_STORE
#define LDRBT      LOAD_STORE | 0x07 | INSTR_BYTE_LS

/* LOAD_STORE_EXT group */
#define STRH       LOAD_STORE_EXT | 0x08 | INSTR_HALFWORD_LS        | INSTR_IS_STORE
#define LDRH       LOAD_STORE_EXT | 0x09 | INSTR_HALFWORD_LS
#define STRD       LOAD_STORE_EXT | 0x0A | INSTR_WORD_LS            | INSTR_IS_STORE
#define LDRD       LOAD_STORE_EXT | 0x0B | INSTR_DUAL_LS
#define LDRSB      LOAD_STORE_EXT | 0x0C | INSTR_SIGNED_BYTE_LS
#define LDRSH      LOAD_STORE_EXT | 0x0D | INSTR_SIGNED_HALFWORD_LS

/* MULTI_LOAD_STORE group */
#define STM        MULTI_LOAD_STORE | 0x00 | INSTR_IS_STORE
#define LDM        MULTI_LOAD_STORE | 0x01
#define STMDA      MULTI_LOAD_STORE | 0x02 | INSTR_IS_STORE
#define LDMDA      MULTI_LOAD_STORE | 0x03
#define STMDB      MULTI_LOAD_STORE | 0x04 | INSTR_IS_STORE
#define LDMDB      MULTI_LOAD_STORE | 0x05
#define STMIA      MULTI_LOAD_STORE | 0x06 | INSTR_IS_STORE
#define LDMIA      MULTI_LOAD_STORE | 0x07
#define STMIB      MULTI_LOAD_STORE | 0x08 | INSTR_IS_STORE
#define LDMIB      MULTI_LOAD_STORE | 0x09

/* STATUS group */
#define MRS        STATUS | 0x01
#define MSR        STATUS | 0x02

/* COPROCESSOR group */
#define LDC        COPROCESSOR | 0x01
#define STC        COPROCESSOR | 0x02

/* MISC group */
#define SWP        MISC | 0x00
#define SWPB       MISC | 0x01
#define BKPT       MISC | 0x02
#define SWI        MISC | 0x03

/* registers */
#define   R0       0x00000000
#define   R1       0x00000001
#define   R2       0x00000002
#define   R3       0x00000003
#define   R4       0x00000004
#define   R5       0x00000005
#define   R6       0x00000006
#define   R7       0x00000007
#define   R8       0x00000008
#define   R9       0x00000009
#define   R10      0x0000000A
#define   R11      0x0000000B
#define   R12      0x0000000C
#define   R13      0x0000000D
#define   R14      0x0000000E
#define   R15      0x0000000F
#define   SP       R13
#define   LR       R14
#define   PC       R15

#ifndef ARM_TABLE_GENERATOR

/* entry for opcode table */
struct arm_opcode {
  unsigned int opcode_flags;
  unsigned int operand_flags;

  union {
    /* pointer to the function that shall handle that instruction */
    const actionFunP_t handler;
  } opcode;

  //#ifdef DEBUG
  const char* mnemonic;
  //#endif
};

#endif  // !ARM_TABLE_GENERATOR

#endif  /* FBT_ARM_OPCODE */

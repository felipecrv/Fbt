#ifndef ARM_OPCODE_MAP
#define ARM_OPCODE_MAP

#include "arm_opcode.h"

/* Basic Mnemonics
 *
 * AND = Logical And
 * MUL = Multiply registers
 * EOR = Logical Exclusive-or
 * MLA = Multiply and accumulate registers
 * SUB = Subtract from register
 * RSB = Subtract register from value
 * ADD = Add to register
 * ADC = Add to register with carry
 * SBC = Subtract from register with borrow
 * RSC = Subtract register from value with borrow
 * MRS = Move status word to register  (ARM6 and later)
 * SWP = Swap registers with memory word
 * TST = Test bits in register (Logical And)
 * MSR = Move value to status word  (ARM6 and later)
 * TEQ = Test equivalence of bits in register (Logical Exclusive-or)
 * CMP = Compare register to value (Subtract), setting flags
 * CMN = Compare register to negation of value (Add), setting flags
 * ORR = Logical Or
 * MOV = Move value to a register
 * BIC = Clear bits in register (NAND)
 * MVN = Move negation of value to a register
 * STR = Store word
 * LDR = Load word
 * STM = Store multiple words
 * LDM = Load multiple words
 * B = Branch
 * BL = Branch and link
 * SWI = Software interrupt
 *
 * Pseudo Instructions -- Shifts (MOV with shifted registers)
 *  ASR LSL LSR ROR RRX
 *
 *
 * Operand configurations
 *
 * lli = Logical shift-left by immediate
 * llr = Logical shift-left by register
 * lri = Logical shift-right by immediate
 * lrr = Logical shift-right by register
 * ari = Arithmetic shift-right by immediate
 * arr = Arithmetic shift-right by register
 * rri = Rotate right by immediate, or rotate right with extend (RRX)
 * rrr = Rotate right by register
 * lli = Logical shift-left by immediate
 * lri = Logical shift-right by immediate
 * ari = Arithmetic shift-right by immediate
 * rri = Rotate right by immediate, or rotate right with extend (RRX)
 * ptrm = Register offset, post-decrement
 * ptim = Immediate offset, post-decrement
 * ptrp = Register offset, post-increment
 * prrm = Register offset, pre-decrement
 * ofrm = Negative register offset
 * ofim = Negative immediate offset
 * prim = Immediate offset, pre-decrement
 * ofrp = Positive register offset
 * prrp = Register offset, pre-increment"
 * prip = Immediate offset, pre-increment
 * imm = Immediate value
 * ic = Immediate, CPSR
 * is = Immediate, SPSR
 * ptim = Immediate offset, post-decrement
 * ptip = Immediate offset, post-increment
 * ofip = Positive immediate offset
 * prrmll = Left-shifted register offset, pre-decrement
 * prrmlr = Right-shifted register offset, pre-decrement
 * prrmar = Arithmetic-right-shifted register offset, pre-decrement
 * prrmrr = Right-rotated register offset, pre-decrement
 * ofrmll = Negative left-shifted register offset
 * ofrmlr = Negative right-shifted register offset
 * ofrmar = Negative arithmetic-right-shifted register offset
 * ofrmrr = Negative right-rotated register offset
 * ofrpll = Positive left-shifted register offset
 * ofrplr = Positive right-shifted register offset
 * ofrpar = Positive arithmetic-right-shifted register offset
 * ofrprr = Positive right-rotated register offset
 * prrpll = Left-shifted register offset, pre-increment
 * prrplr = Right-shifted register offset, pre-increment
 * prrpar = Arithmetic-right-shifted register offset, pre-increment
 * prrprr = Right-rotated register offset, pre-increment
 * ofm = Negative offset
 * prm = Pre-decrement
 * ofp = Positive offset
 * prp = Pre-increment
 * unm = Unindexed, bits 7-0 available for copro use
 * ptm = Post-decrement
 * unp = Unindexed, bits 7-0 available for copro use
 * ptp = Post-increment
 * w = Write-Back
 * u = Use user-mode registers
 */

/* bits 7-4 */
instr_description table_opcode_00[] = {
/* 0x0 */ {0, "AND lli", AND, "action_copy", "Logical And"},
/* 0x1 */ {0, "AND llr", AND, "action_copy", "Logical And"},
/* 0x2 */ {0, "AND lri", AND, "action_copy", "Logical And"},
/* 0x3 */ {0, "AND lrr", AND, "action_copy", "Logical And"},
/* 0x4 */ {0, "AND ari", AND, "action_copy", "Logical And"},
/* 0x5 */ {0, "AND arr", AND, "action_copy", "Logical And"},
/* 0x6 */ {0, "AND rri", AND, "action_copy", "Logical And"},
/* 0x7 */ {0, "AND rrr", AND, "action_copy", "Logical And"},
/* 0x8 */ {0, "AND lli", AND, "action_copy", "Logical And"},
/* 0x9 */ {0, "MUL",     MUL, "action_copy", "Multiply registers"},
/* 0xa */ {0, "AND lri", AND, "action_copy", "Logical And"},
/* 0xb */ {0, "STRH ptrm", STRH, "action_copy", "Store halfword"},
/* 0xc */ {0, "AND ari",   AND, "action_copy", "Logical And"},
/* 0xd */ {0, "LDRD ptrm", LDRD, "action_copy", "Load doubleword"},
/* 0xe */ {0, "AND rri",   AND, "action_copy", "Logical And"},
/* 0xf */ {0, "STRD ptrm", STRD, "action_copy", "Store doubleword"},
};

/* bits 7-4 */
instr_description table_opcode_01[] = {
/* 0x0 */ {0, "ANDS lli", ANDS, "action_copy", "Logical And, setting flags"},
/* 0x1 */ {0, "ANDS llr", ANDS, "action_copy", "Logical And, setting flags"},
/* 0x2 */ {0, "ANDS lri", ANDS, "action_copy", "Logical And, setting flags"},
/* 0x3 */ {0, "ANDS lrr", ANDS, "action_copy", "Logical And, setting flags"},
/* 0x4 */ {0, "ANDS ari", ANDS, "action_copy", "Logical And, setting flags"},
/* 0x5 */ {0, "ANDS arr", ANDS, "action_copy", "Logical And, setting flags"},
/* 0x6 */ {0, "ANDS rri", ANDS, "action_copy", "Logical And, setting flags"},
/* 0x7 */ {0, "ANDS rrr", ANDS, "action_copy", "Logical And, setting flags"},
/* 0x8 */ {0, "ANDS lli", ANDS, "action_copy", "Logical And, setting flags"},
/* 0x9 */ {0, "MULS", MULS, "action_copy", "Multiply registers, setting flag"},
/* 0xa */ {0, "ANDS lri", ANDS, "action_copy", "Logical And, setting flags"},
/* 0xb */ {0, "LDRH ptrm", LDRH, "action_copy", "Load halfword"},
/* 0xc */ {0, "ANDS ari", ANDS, "action_copy", "Logical And, setting flags"},
/* 0xd */ {0, "LDRSB ptrm", LDRSB, "action_copy", "Load signed byte"},
/* 0xe */ {0, "ANDS rri", ANDS, "action_copy", "Logical And, setting flags"},
/* 0xf */ {0, "LDRSH ptrm", LDRSH, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_02[] = {
/* 0x0 */ {0, "EOR lli", EOR, "action_copy", "Logical Exclusive-or"},
/* 0x1 */ {0, "EOR llr", EOR, "action_copy", "Logical Exclusive-or"},
/* 0x2 */ {0, "EOR lri", EOR, "action_copy", "Logical Exclusive-or"},
/* 0x3 */ {0, "EOR lrr", EOR, "action_copy", "Logical Exclusive-or"},
/* 0x4 */ {0, "EOR ari", EOR, "action_copy", "Logical Exclusive-or"},
/* 0x5 */ {0, "EOR arr", EOR, "action_copy", "Logical Exclusive-or"},
/* 0x6 */ {0, "EOR rri", EOR, "action_copy", "Logical Exclusive-or"},
/* 0x7 */ {0, "EOR rrr", EOR, "action_copy", "Logical Exclusive-or"},
/* 0x8 */ {0, "EOR lli", EOR, "action_copy", "Logical Exclusive-or"},
/* 0x9 */ {0, "MLA aa", MLA, "action_copy", "Multiply and accumulate registers"},
/* 0xa */ {0, "EOR lri", EOR, "action_copy", "Logical Exclusive-or"},
/* 0xb */ {0, "STRH ptrm", STRH, "action_copy", "Store halfword"},
/* 0xc */ {0, "EOR ari", EOR, "action_copy", "Logical Exclusive-or"},
/* 0xd */ {0, "LDRD ptrm", LDRD, "action_copy", "Load doubleword"},
/* 0xe */ {0, "EOR rri", EOR, "action_copy", "Logical Exclusive-or"},
/* 0xf */ {0, "STRD ptrm", STRD, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_03[] = {
/* 0x0 */ {0, "EORS lli", EORS, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x1 */ {0, "EORS llr", EORS, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x2 */ {0, "EORS lri", EORS, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x3 */ {0, "EORS lrr", EORS, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x4 */ {0, "EORS ari", EORS, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x5 */ {0, "EORS arr", EORS, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x6 */ {0, "EORS rri", EORS, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x7 */ {0, "EORS rrr", EORS, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x8 */ {0, "EORS lli", EORS, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x9 */ {0, "MLAS", MLAS, "action_copy", "Multiply and accumulate registers, setting flags"},
/* 0xa */ {0, "EORS lri", EORS, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0xb */ {0, "LDRH ptrm", LDRH, "action_copy", "Load halfword"},
/* 0xc */ {0, "EORS ari", EORS, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0xd */ {0, "LDRSB ptrm", LDRSB, "action_copy", "Load signed byte"},
/* 0xe */ {0, "EORS rri", EORS, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0xf */ {0, "LDRSH ptrm", LDRSH, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_04[] = {
/* 0x0 */ {0, "SUB lli", SUB, "action_copy", "Subtract from register"},
/* 0x1 */ {0, "SUB llr", SUB, "action_copy", "Subtract from register"},
/* 0x2 */ {0, "SUB lri", SUB, "action_copy", "Subtract from register"},
/* 0x3 */ {0, "SUB lrr", SUB, "action_copy", "Subtract from register"},
/* 0x4 */ {0, "SUB ari", SUB, "action_copy", "Subtract from register"},
/* 0x5 */ {0, "SUB arr", SUB, "action_copy", "Subtract from register"},
/* 0x6 */ {0, "SUB rri", SUB, "action_copy", "Subtract from register"},
/* 0x7 */ {0, "SUB rrr", SUB, "action_copy", "Subtract from register"},
/* 0x8 */ {0, "SUB lli", SUB, "action_copy", "Subtract from register"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "SUB lri", SUB, "action_copy", "Subtract from register"},
/* 0xb */ {0, "STRH ptim", STRH, "action_copy", "Store halfword"},
/* 0xc */ {0, "SUB ari", SUB, "action_copy", "Subtract from register"},
/* 0xd */ {0, "LDRD ptim", LDRD, "action_copy", "Load doubleword"},
/* 0xe */ {0, "SUB rri", SUB, "action_copy", "Subtract from register"},
/* 0xf */ {0, "STRD ptim", STRD, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_05[] = {
/* 0x0 */ {0, "SUBS lli", SUBS, "action_copy", "Subtract, setting flags"},
/* 0x1 */ {0, "SUBS llr", SUBS, "action_copy", "Subtract, setting flags"},
/* 0x2 */ {0, "SUBS lri", SUBS, "action_copy", "Subtract, setting flags"},
/* 0x3 */ {0, "SUBS lrr", SUBS, "action_copy", "Subtract, setting flags"},
/* 0x4 */ {0, "SUBS ari", SUBS, "action_copy", "Subtract, setting flags"},
/* 0x5 */ {0, "SUBS arr", SUBS, "action_copy", "Subtract, setting flags"},
/* 0x6 */ {0, "SUBS rri", SUBS, "action_copy", "Subtract, setting flags"},
/* 0x7 */ {0, "SUBS rrr", SUBS, "action_copy", "Subtract, setting flags"},
/* 0x8 */ {0, "SUBS lli", SUBS, "action_copy", "Subtract, setting flags"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "SUBS lri", SUBS, "action_copy", "Subtract, setting flags"},
/* 0xb */ {0, "LDRH ptim", LDRH, "action_copy", "Load halfword"},
/* 0xc */ {0, "SUBS ari", SUBS, "action_copy", "Subtract, setting flags"},
/* 0xd */ {0, "LDRSB ptim", LDRSB, "action_copy", "Load signed byte"},
/* 0xe */ {0, "SUBS rri", SUBS, "action_copy", "Subtract, setting flags"},
/* 0xf */ {0, "LDRSH ptim", LDRSH, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_06[] = {
/* 0x0 */ {0, "RSB lli", RSB, "action_copy", "Subtract register from value"},
/* 0x1 */ {0, "RSB llr", RSB, "action_copy", "Subtract register from value"},
/* 0x2 */ {0, "RSB lri", RSB, "action_copy", "Subtract register from value"},
/* 0x3 */ {0, "RSB lrr", RSB, "action_copy", "Subtract register from value"},
/* 0x4 */ {0, "RSB ari", RSB, "action_copy", "Subtract register from value"},
/* 0x5 */ {0, "RSB arr", RSB, "action_copy", "Subtract register from value"},
/* 0x6 */ {0, "RSB rri", RSB, "action_copy", "Subtract register from value"},
/* 0x7 */ {0, "RSB rrr", RSB, "action_copy", "Subtract register from value"},
/* 0x8 */ {0, "RSB lli", RSB, "action_copy", "Subtract register from value"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "RSB lri", RSB, "action_copy", "Subtract register from value"},
/* 0xb */ {0, "STRH ptim", STRH, "action_copy", "Store halfword"},
/* 0xc */ {0, "RSB ari", RSB, "action_copy", "Subtract register from value"},
/* 0xd */ {0, "LDRD ptim", LDRD, "action_copy", "Load doubleword"},
/* 0xe */ {0, "RSB rri", RSB, "action_copy", "Subtract register from value"},
/* 0xf */ {0, "STRD ptim", STRD, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_07[] = {
/* 0x0 */ {0, "RSBS lli", RSBS, "action_copy", "Reverse Subtract, setting flags"},
/* 0x1 */ {0, "RSBS llr", RSBS, "action_copy", "Reverse Subtract, setting flags"},
/* 0x2 */ {0, "RSBS lri", RSBS, "action_copy", "Reverse Subtract, setting flags"},
/* 0x3 */ {0, "RSBS lrr", RSBS, "action_copy", "Reverse Subtract, setting flags"},
/* 0x4 */ {0, "RSBS ari", RSBS, "action_copy", "Reverse Subtract, setting flags"},
/* 0x5 */ {0, "RSBS arr", RSBS, "action_copy", "Reverse Subtract, setting flags"},
/* 0x6 */ {0, "RSBS rri", RSBS, "action_copy", "Reverse Subtract, setting flags"},
/* 0x7 */ {0, "RSBS rrr", RSBS, "action_copy", "Reverse Subtract, setting flags"},
/* 0x8 */ {0, "RSBS lli", RSBS, "action_copy", "Reverse Subtract, setting flags"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "RSBS lri", RSBS, "action_copy", "Reverse Subtract, setting flags"},
/* 0xb */ {0, "LDRH ptim", LDRH, "action_copy", "Load halfword"},
/* 0xc */ {0, "RSBS ari", RSBS, "action_copy", "Reverse Subtract, setting flags"},
/* 0xd */ {0, "LDRSB ptim", LDRSB, "action_copy", "Load signed byte"},
/* 0xe */ {0, "RSBS rri", RSBS, "action_copy", "Reverse Subtract, setting flags"},
/* 0xf */ {0, "LDRSH ptim", LDRSH, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_08[] = {
/* 0x0 */ {0, "ADD lli", ADD, "action_copy", "Add to register"},
/* 0x1 */ {0, "ADD llr", ADD, "action_copy", "Add to register"},
/* 0x2 */ {0, "ADD lri", ADD, "action_copy", "Add to register"},
/* 0x3 */ {0, "ADD lrr", ADD, "action_copy", "Add to register"},
/* 0x4 */ {0, "ADD ari", ADD, "action_copy", "Add to register"},
/* 0x5 */ {0, "ADD arr", ADD, "action_copy", "Add to register"},
/* 0x6 */ {0, "ADD rri", ADD, "action_copy", "Add to register"},
/* 0x7 */ {0, "ADD rrr", ADD, "action_copy", "Add to register"},
/* 0x8 */ {0, "ADD lli", ADD, "action_copy", "Add to register"},
/* 0x9 */ {0, "UMULL", UMULL, "action_copy", "Unsigned long multiply (32x32 to 64)"},
/* 0xa */ {0, "ADD lri", ADD, "action_copy", "Add to register"},
/* 0xb */ {0, "STRH ptrp", STRH, "action_copy", "Store halfword"},
/* 0xc */ {0, "ADD ari", ADD, "action_copy", "Add to register"},
/* 0xd */ {0, "LDRD ptrp", LDRD, "action_copy", "Load doubleword"},
/* 0xe */ {0, "ADD rri", ADD, "action_copy", "Add to register"},
/* 0xf */ {0, "STRD ptrp", STRD, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_09[] = {
/* 0x0 */ {0, "ADDS lli", ADDS, "action_copy", "Add to register, setting flags"},
/* 0x1 */ {0, "ADDS llr", ADDS, "action_copy", "Add to register, setting flags"},
/* 0x2 */ {0, "ADDS lri", ADDS, "action_copy", "Add to register, setting flags"},
/* 0x3 */ {0, "ADDS lrr", ADDS, "action_copy", "Add to register, setting flags"},
/* 0x4 */ {0, "ADDS ari", ADDS, "action_copy", "Add to register, setting flags"},
/* 0x5 */ {0, "ADDS arr", ADDS, "action_copy", "Add to register, setting flags"},
/* 0x6 */ {0, "ADDS rri", ADDS, "action_copy", "Add to register, setting flags"},
/* 0x7 */ {0, "ADDS rrr", ADDS, "action_copy", "Add to register, setting flags"},
/* 0x8 */ {0, "ADDS lli", ADDS, "action_copy", "Add to register, setting flags"},
/* 0x9 */ {0, "UMULLS", UMULLS, "action_copy", "Unsigned long multiply, setting flags"},
/* 0xa */ {0, "ADDS lri", ADDS, "action_copy", "Add to register, setting flags"},
/* 0xb */ {0, "LDRH ptrp", LDRH, "action_copy", "Load halfword"},
/* 0xc */ {0, "ADDS ari", ADDS, "action_copy", "Add to register, setting flags"},
/* 0xd */ {0, "LDRSB ptrp", LDRSB, "action_copy", "Load signed byte"},
/* 0xe */ {0, "ADDS rri", ADDS, "action_copy", "Add to register, setting flags"},
/* 0xf */ {0, "LDRSH ptrp", LDRSH, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_0a[] = {
/* 0x0 */ {0, "ADC lli", ADC, "action_copy", "Add to register with carry"},
/* 0x1 */ {0, "ADC llr", ADC, "action_copy", "Add to register with carry"},
/* 0x2 */ {0, "ADC lri", ADC, "action_copy", "Add to register with carry"},
/* 0x3 */ {0, "ADC lrr", ADC, "action_copy", "Add to register with carry"},
/* 0x4 */ {0, "ADC ari", ADC, "action_copy", "Add to register with carry"},
/* 0x5 */ {0, "ADC arr", ADC, "action_copy", "Add to register with carry"},
/* 0x6 */ {0, "ADC rri", ADC, "action_copy", "Add to register with carry"},
/* 0x7 */ {0, "ADC rrr", ADC, "action_copy", "Add to register with carry"},
/* 0x8 */ {0, "ADC lli", ADC, "action_copy", "Add to register with carry"},
/* 0x9 */ {0, "UMLAL", UMLAL, "action_copy", "Unsigned long multiply and accumulate"},
/* 0xa */ {0, "ADC lri", ADC, "action_copy", "Add to register with carry"},
/* 0xb */ {0, "STRH ptrp", STRH, "action_copy", "Store halfword"},
/* 0xc */ {0, "ADC ari", ADC, "action_copy", "Add to register with carry"},
/* 0xd */ {0, "LDRD ptrp", LDRD, "action_copy", "Load doubleword"},
/* 0xe */ {0, "ADC rri", ADC, "action_copy", "Add to register with carry"},
/* 0xf */ {0, "STRD ptrp", STRD, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_0b[] = {
/* 0x0 */ {0, "ADCS lli", ADCS, "action_copy", "Add to register with carry, setting flags"},
/* 0x1 */ {0, "ADCS llr", ADCS, "action_copy", "Add to register with carry, setting flags"},
/* 0x2 */ {0, "ADCS lri", ADCS, "action_copy", "Add to register with carry, setting flags"},
/* 0x3 */ {0, "ADCS lrr", ADCS, "action_copy", "Add to register with carry, setting flags"},
/* 0x4 */ {0, "ADCS ari", ADCS, "action_copy", "Add to register with carry, setting flags"},
/* 0x5 */ {0, "ADCS arr", ADCS, "action_copy", "Add to register with carry, setting flags"},
/* 0x6 */ {0, "ADCS rri", ADCS, "action_copy", "Add to register with carry, setting flags"},
/* 0x7 */ {0, "ADCS rrr", ADCS, "action_copy", "Add to register with carry, setting flags"},
/* 0x8 */ {0, "ADCS lli", ADCS, "action_copy", "Add to register with carry, setting flags"},
/* 0x9 */ {0, "UMLALS", UMLALS, "action_copy", "Unsigned long multiply and accumulate, setting flags"},
/* 0xa */ {0, "ADCS lri", ADCS, "action_copy", "Add to register with carry, setting flags"},
/* 0xb */ {0, "LDRH ptrp", LDRH, "action_copy", "Load halfword"},
/* 0xc */ {0, "ADCS ari", ADCS, "action_copy", "Add to register with carry, setting flags"},
/* 0xd */ {0, "LDRSB ptrp", LDRSB, "action_copy", "Load signed byte"},
/* 0xe */ {0, "ADCS rri", ADCS, "action_copy", "Add to register with carry, setting flags"},
/* 0xf */ {0, "LDRSH ptrp", LDRSH, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_0c[] = {
/* 0x0 */ {0, "SBC lli", SBC, "action_copy", "Subtract from register with borrow"},
/* 0x1 */ {0, "SBC llr", SBC, "action_copy", "Subtract from register with borrow"},
/* 0x2 */ {0, "SBC lri", SBC, "action_copy", "Subtract from register with borrow"},
/* 0x3 */ {0, "SBC lrr", SBC, "action_copy", "Subtract from register with borrow"},
/* 0x4 */ {0, "SBC ari", SBC, "action_copy", "Subtract from register with borrow"},
/* 0x5 */ {0, "SBC arr", SBC, "action_copy", "Subtract from register with borrow"},
/* 0x6 */ {0, "SBC rri", SBC, "action_copy", "Subtract from register with borrow"},
/* 0x7 */ {0, "SBC rrr", SBC, "action_copy", "Subtract from register with borrow"},
/* 0x8 */ {0, "SBC lli", SBC, "action_copy", "Subtract from register with borrow"},
/* 0x9 */ {0, "SMULL", SMULL, "action_copy", "Signed long multiply (32x32 to 64)"},
/* 0xa */ {0, "SBC lri", SBC, "action_copy", "Subtract from register with borrow"},
/* 0xb */ {0, "STRH ptip", STRH, "action_copy", "Store halfword"},
/* 0xc */ {0, "SBC ari", SBC, "action_copy", "Subtract from register with borrow"},
/* 0xd */ {0, "LDRD ptip", LDRD, "action_copy", "Load doubleword"},
/* 0xe */ {0, "SBC rri", SBC, "action_copy", "Subtract from register with borrow"},
/* 0xf */ {0, "STRD ptip", STRD, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_0d[] = {
/* 0x0 */ {0, "SBCS lli", SBCS, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x1 */ {0, "SBCS llr", SBCS, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x2 */ {0, "SBCS lri", SBCS, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x3 */ {0, "SBCS lrr", SBCS, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x4 */ {0, "SBCS ari", SBCS, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x5 */ {0, "SBCS arr", SBCS, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x6 */ {0, "SBCS rri", SBCS, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x7 */ {0, "SBCS rrr", SBCS, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x8 */ {0, "SBCS lli", SBCS, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x9 */ {0, "SMULLS", SMULLS, "action_copy", "Signed long multiply, setting flags"},
/* 0xa */ {0, "SBCS lri", SBCS, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0xb */ {0, "LDRH ptip", LDRH, "action_copy", "Load halfword"},
/* 0xc */ {0, "SBCS ari", SBCS, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0xd */ {0, "LDRSB ptip", LDRSB, "action_copy", "Load signed byte"},
/* 0xe */ {0, "SBCS rri", SBCS, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0xf */ {0, "LDRSH ptip", LDRSH, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_0e[] = {
/* 0x0 */ {0, "RSC lli", RSC, "action_copy", "Subtract register from value with borrow"},
/* 0x1 */ {0, "RSC llr", RSC, "action_copy", "Subtract register from value with borrow"},
/* 0x2 */ {0, "RSC lri", RSC, "action_copy", "Subtract register from value with borrow"},
/* 0x3 */ {0, "RSC lrr", RSC, "action_copy", "Subtract register from value with borrow"},
/* 0x4 */ {0, "RSC ari", RSC, "action_copy", "Subtract register from value with borrow"},
/* 0x5 */ {0, "RSC arr", RSC, "action_copy", "Subtract register from value with borrow"},
/* 0x6 */ {0, "RSC rri", RSC, "action_copy", "Subtract register from value with borrow"},
/* 0x7 */ {0, "RSC rrr", RSC, "action_copy", "Subtract register from value with borrow"},
/* 0x8 */ {0, "RSC lli", RSC, "action_copy", "Subtract register from value with borrow"},
/* 0x9 */ {0, "SMLAL", SMLAL, "action_copy", "Signed long multiply and accumulate"},
/* 0xa */ {0, "RSC lri", RSC, "action_copy", "Subtract register from value with borrow"},
/* 0xb */ {0, "STRH ptip", STRH, "action_copy", "Store halfword"},
/* 0xc */ {0, "RSC ari", RSC, "action_copy", "Subtract register from value with borrow"},
/* 0xd */ {0, "LDRD ptip", LDRD, "action_copy", "Load doubleword"},
/* 0xe */ {0, "RSC rri", RSC, "action_copy", "Subtract register from value with borrow"},
/* 0xf */ {0, "STRD ptip", STRD, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_0f[] = {
/* 0x0 */ {0, "RSCS lli", RSCS, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x1 */ {0, "RSCS llr", RSCS, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x2 */ {0, "RSCS lri", RSCS, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x3 */ {0, "RSCS lrr", RSCS, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x4 */ {0, "RSCS ari", RSCS, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x5 */ {0, "RSCS arr", RSCS, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x6 */ {0, "RSCS rri", RSCS, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x7 */ {0, "RSCS rrr", RSCS, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x8 */ {0, "RSCS lli", RSCS, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x9 */ {0, "SMLALS", NONE, "action_copy", "Signed long multiply and ultiply , setting flags"},
/* 0xa */ {0, "RSCS lri", RSCS, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0xb */ {0, "LDRH ptip", LDRH, "action_copy", "Load halfword"},
/* 0xc */ {0, "RSCS ari", RSCS, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0xd */ {0, "LDRSB ptip", LDRSB, "action_copy", "Load signed byte"},
/* 0xe */ {0, "RSCS rri", RSCS, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0xf */ {0, "LDRSH ptip", LDRSH, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_10[] = {
/* 0x0 */ {0, "MRS rc", MRS, "action_copy", "Move status word to register"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x5 */ {0, "QADD", QADD, "action_copy", "Saturated add"},
/* 0x6 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "SMLABB", SMLABB, "action_copy", "Signed multiply bottom-half of first operand with bottom-half of second, and accumulate"},
/* 0x9 */ {0, "SWP", SWP, "action_copy", "Swap registers with memory word"},
/* 0xa */ {0, "SMLATB", SMLATB, "action_copy", "Signed multiply top-half of first operand with bottom-half of second, and accumulate"},
/* 0xb */ {0, "STRH ofrm", STRH, "action_copy", "Store halfword"},
/* 0xc */ {0, "SMLABT", SMLABT, "action_copy", "Signed multiply bottom-half of first operand with top-half of second, and accumulate"},
/* 0xd */ {0, "LDRD ofrm", LDRD, "action_copy", "Load doubleword"},
/* 0xe */ {0, "SMLATT", SMLATT, "action_copy", "Signed multiply top-half of first operand with top-half of second, and accumulate"},
/* 0xf */ {0, "STRD ofrm", STRD, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_11[] = {
/* 0x0 */ {0, "TSTS lli", TSTS, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x1 */ {0, "TSTS llr", TSTS, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x2 */ {0, "TSTS lri", TSTS, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x3 */ {0, "TSTS lrr", TSTS, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x4 */ {0, "TSTS ari", TSTS, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x5 */ {0, "TSTS arr", TSTS, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x6 */ {0, "TSTS rri", TSTS, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x7 */ {0, "TSTS rrr", TSTS, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x8 */ {0, "TSTS lli", TSTS, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "TSTS lri", TSTS, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0xb */ {0, "LDRH ofrm", LDRH, "action_copy", "Load halfword"},
/* 0xc */ {0, "TSTS ari", TSTS, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0xd */ {0, "LDRSB ofrm", LDRSB, "action_copy", "Load signed byte"},
/* 0xe */ {0, "TSTS rri", TSTS, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0xf */ {0, "LDRSH ofrm", LDRSH, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_12[] = {
/* 0x0 */ {0, "MSR rc", MSR, "action_copy", "Move value to status word"},
/* 0x1 */ {0, "BX", BX, "action_copy", "Branch and switch execution modes"},
/* 0x2 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x3 */ {0, "BLX reg", BLX, "action_copy", "Branch, link and switch execution modes"},
/* 0x4 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x5 */ {0, "QSUB", QSUB, "action_copy", "Saturated subtract"},
/* 0x6 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x7 */ {0, "BKPT", BKPT, "action_copy", "Software breakpoint"},
/* 0x8 */ {0, "SMLAWB", SMLAWB, "action_copy", "Signed multiply first operand with bottom-half of second operand, keeping top 32 bits, and accumulate"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "SMULWB", SMULWB, "action_copy", "Signed multiply first operand with bottom-half of second operand, keeping top 32 bits"},
/* 0xb */ {0, "STRH prrm", STRH, "action_copy", "Store halfword"},
/* 0xc */ {0, "SMLAWT", SMLAWT, "action_copy", "Signed multiply first operand with top-half of second operand, keeping top 32 bits, and accumulate"},
/* 0xd */ {0, "LDRD prrm", LDRD, "action_copy", "Load doubleword"},
/* 0xe */ {0, "SMULWT", SMULWT, "action_copy", "Signed multiply first operand with top-half of second operand, keeping top 32 bits"},
/* 0xf */ {0, "STRD prrm", STRD, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_13[] = {
/* 0x0 */ {0, "TEQS lli", TEQS, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x1 */ {0, "TEQS llr", TEQS, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x2 */ {0, "TEQS lri", TEQS, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x3 */ {0, "TEQS lrr", TEQS, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x4 */ {0, "TEQS ari", TEQS, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x5 */ {0, "TEQS arr", TEQS, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x6 */ {0, "TEQS rri", TEQS, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x7 */ {0, "TEQS rrr", TEQS, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x8 */ {0, "TEQS lli", TEQS, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "TEQS lri", TEQS, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0xb */ {0, "LDRH prrm", LDRH, "action_copy", "Load halfword"},
/* 0xc */ {0, "TEQS ari", TEQS, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0xd */ {0, "LDRSB prrm", LDRSB, "action_copy", "Load signed byte"},
/* 0xe */ {0, "TEQS rri", TEQS, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0xf */ {0, "LDRSH prrm", LDRSH, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_14[] = {
/* 0x0 */ {0, "MRS rs", MRS, "action_copy", "Move status word to register"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x5 */ {0, "QDADD", QDADD, "action_copy", "Saturated add with doubling of second operand"},
/* 0x6 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "SMLALBB", SMLALBB, "action_copy", "Signed multiply bottom-half of first operand with bottom-half of second, and 64-bit accumulate"},
/* 0x9 */ {0, "SWPB", SWPB, "action_copy", "Swap registers with memory byte"},
/* 0xa */ {0, "SMLALTB", SMLALTB, "action_copy", "Signed multiply top-half of first operand with bottom-half of second, and 64-bit accumulate"},
/* 0xb */ {0, "STRH ofim", STRH, "action_copy", "Store halfword"},
/* 0xc */ {0, "SMLALBT", SMLALBT, "action_copy", "Signed multiply bottom-half of first operand with top-half of second, and 64-bit accumulate"},
/* 0xd */ {0, "LDRD ofim", LDRD, "action_copy", "Load doubleword"},
/* 0xe */ {0, "SMLALTT", SMLALTT, "action_copy", "Signed multiply top-half of first operand with top-half of second, and 64-bit accumulate"},
/* 0xf */ {0, "STRD ofim", STRD, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_15[] = {
/* 0x0 */ {0, "CMPS lli", CMPS, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x1 */ {0, "CMPS llr", CMPS, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x2 */ {0, "CMPS lri", CMPS, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x3 */ {0, "CMPS lrr", CMPS, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x4 */ {0, "CMPS ari", CMPS, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x5 */ {0, "CMPS arr", CMPS, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x6 */ {0, "CMPS rri", CMPS, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x7 */ {0, "CMPS rrr", CMPS, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x8 */ {0, "CMPS lli", CMPS, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "CMPS lri", CMPS, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0xb */ {0, "LDRH ofim", LDRH, "action_copy", "Load halfword"},
/* 0xc */ {0, "CMPS ari", CMPS, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0xd */ {0, "LDRSB ofim", LDRSB, "action_copy", "Load signed byte"},
/* 0xe */ {0, "CMPS rri", CMPS, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0xf */ {0, "LDRSH ofim", LDRSH, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_16[] = {
/* 0x0 */ {0, "MSR rs", MSR, "action_copy", "Move value to status word"},
/* 0x1 */ {0, "CLZ", CLZ, "action_copy", "Count leading zeros in register"},
/* 0x2 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x5 */ {0, "QDSUB", QDSUB, "action_copy", "Saturated subtract with doubling of second operand"},
/* 0x6 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "SMULBB", SMULBB, "action_copy", "Signed multiply bottom-half of first operand with bottom-half of second"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "SMULTB", SMULTB, "action_copy", "Signed multiply top-half of first operand with bottom-half of second"},
/* 0xb */ {0, "STRH prim", STRH, "action_copy", "Store halfword"},
/* 0xc */ {0, "SMULBT", SMULBT, "action_copy", "Signed multiply bottom-half of first operand with top-half of second"},
/* 0xd */ {0, "LDRD prim", LDRD, "action_copy", "Load doubleword"},
/* 0xe */ {0, "SMULTT", SMULTT, "action_copy", "Signed multiply top-half of first operand with top-half of second"},
/* 0xf */ {0, "STRD prim", STRD, "action_copy", "Store doubleword"},
};

/* bits 7-4 */
instr_description table_opcode_17[] = {
/* 0x0 */ {0, "CMNS lli", CMNS, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x1 */ {0, "CMNS llr", CMNS, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x2 */ {0, "CMNS lri", CMNS, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x3 */ {0, "CMNS lrr", CMNS, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x4 */ {0, "CMNS ari", CMNS, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x5 */ {0, "CMNS arr", CMNS, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x6 */ {0, "CMNS rri", CMNS, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x7 */ {0, "CMNS rrr", CMNS, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x8 */ {0, "CMNS lli", CMNS, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "CMNS lri", CMNS, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0xb */ {0, "LDRH prim", LDRH, "action_copy", "Load halfword"},
/* 0xc */ {0, "CMNS ari", CMNS, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0xd */ {0, "LDRSB prim", LDRSB, "action_copy", "Load signed byte"},
/* 0xe */ {0, "CMNS rri", CMNS, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0xf */ {0, "LDRSH prim", LDRSH, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_18[] = {
/* 0x0 */ {0, "ORR lli", ORR, "action_copy", "Logical Or"},
/* 0x1 */ {0, "ORR llr", ORR, "action_copy", "Logical Or"},
/* 0x2 */ {0, "ORR lri", ORR, "action_copy", "Logical Or"},
/* 0x3 */ {0, "ORR lrr", ORR, "action_copy", "Logical Or"},
/* 0x4 */ {0, "ORR ari", ORR, "action_copy", "Logical Or"},
/* 0x5 */ {0, "ORR arr", ORR, "action_copy", "Logical Or"},
/* 0x6 */ {0, "ORR rri", ORR, "action_copy", "Logical Or"},
/* 0x7 */ {0, "ORR rrr", ORR, "action_copy", "Logical Or"},
/* 0x8 */ {0, "ORR lli", ORR, "action_copy", "Logical Or"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "ORR lri", ORR, "action_copy", "Logical Or"},
/* 0xb */ {0, "STRH ofrp", STRH, "action_copy", "Store halfword"},
/* 0xc */ {0, "ORR ari", ORR, "action_copy", "Logical Or"},
/* 0xd */ {0, "LDRD ofrp", LDRD, "action_copy", "Load doubleword"},
/* 0xe */ {0, "ORR rri", ORR, "action_copy", "Logical Or"},
/* 0xf */ {0, "STRD ofrp", STRD, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_19[] = {
/* 0x0 */ {0, "ORRS lli", ORRS, "action_copy", "Logical Or, setting flags"},
/* 0x1 */ {0, "ORRS llr", ORRS, "action_copy", "Logical Or, setting flags"},
/* 0x2 */ {0, "ORRS lri", ORRS, "action_copy", "Logical Or, setting flags"},
/* 0x3 */ {0, "ORRS lrr", ORRS, "action_copy", "Logical Or, setting flags"},
/* 0x4 */ {0, "ORRS ari", ORRS, "action_copy", "Logical Or, setting flags"},
/* 0x5 */ {0, "ORRS arr", ORRS, "action_copy", "Logical Or, setting flags"},
/* 0x6 */ {0, "ORRS rri", ORRS, "action_copy", "Logical Or, setting flags"},
/* 0x7 */ {0, "ORRS rrr", ORRS, "action_copy", "Logical Or, setting flags"},
/* 0x8 */ {0, "ORRS lli", ORRS, "action_copy", "Logical Or, setting flags"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "ORRS lri", ORRS, "action_copy", "Logical Or, setting flags"},
/* 0xb */ {0, "LDRH ofrp", LDRH, "action_copy", "Load halfword"},
/* 0xc */ {0, "ORRS ari", ORRS, "action_copy", "Logical Or, setting flags"},
/* 0xd */ {0, "LDRSB ofrp", LDRSB, "action_copy", "Load signed byte"},
/* 0xe */ {0, "ORRS rri", ORRS, "action_copy", "Logical Or, setting flags"},
/* 0xf */ {0, "LDRSH ofrp", LDRSH, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_1a[] = {
/* 0x0 */ {0, "MOV lli", MOV, "action_copy", "Move value to a register"},
/* 0x1 */ {0, "MOV llr", MOV, "action_copy", "Move value to a register"},
/* 0x2 */ {0, "MOV lri", MOV, "action_copy", "Move value to a register"},
/* 0x3 */ {0, "MOV lrr", MOV, "action_copy", "Move value to a register"},
/* 0x4 */ {0, "MOV ari", MOV, "action_copy", "Move value to a register"},
/* 0x5 */ {0, "MOV arr", MOV, "action_copy", "Move value to a register"},
/* 0x6 */ {0, "MOV rri", MOV, "action_copy", "Move value to a register"},
/* 0x7 */ {0, "MOV rrr", MOV, "action_copy", "Move value to a register"},
/* 0x8 */ {0, "MOV lli", MOV, "action_copy", "Move value to a register"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "MOV lri", MOV, "action_copy", "Move value to a register"},
/* 0xb */ {0, "STRH prrp", STRH, "action_copy", "Store halfword"},
/* 0xc */ {0, "MOV ari", MOV, "action_copy", "Move value to a register"},
/* 0xd */ {0, "LDRD prrp", LDRD, "action_copy", "Load doubleword"},
/* 0xe */ {0, "MOV rri", MOV, "action_copy", "Move value to a register"},
/* 0xf */ {0, "STRD prrp", STRD, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_1b[] = {
/* 0x0 */ {0, "MOVS lli", MOVS, "action_copy", "Move value to a register, setting flags"},
/* 0x1 */ {0, "MOVS llr", MOVS, "action_copy", "Move value to a register, setting flags"},
/* 0x2 */ {0, "MOVS lri", MOVS, "action_copy", "Move value to a register, setting flags"},
/* 0x3 */ {0, "MOVS lrr", MOVS, "action_copy", "Move value to a register, setting flags"},
/* 0x4 */ {0, "MOVS ari", MOVS, "action_copy", "Move value to a register, setting flags"},
/* 0x5 */ {0, "MOVS arr", MOVS, "action_copy", "Move value to a register, setting flags"},
/* 0x6 */ {0, "MOVS rri", MOVS, "action_copy", "Move value to a register, setting flags"},
/* 0x7 */ {0, "MOVS rrr", MOVS, "action_copy", "Move value to a register, setting flags"},
/* 0x8 */ {0, "MOVS lli", MOVS, "action_copy", "Move value to a register, setting flags"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "MOVS lri", MOVS, "action_copy", "Move value to a register, setting flags"},
/* 0xb */ {0, "LDRH prrp", LDRH, "action_copy", "Load halfword"},
/* 0xc */ {0, "MOVS ari", MOVS, "action_copy", "Move value to a register, setting flags"},
/* 0xd */ {0, "LDRSB prrp", LDRSB, "action_copy", "Load signed byte"},
/* 0xe */ {0, "MOVS rri", MOVS, "action_copy", "Move value to a register, setting flags"},
/* 0xf */ {0, "LDRSH prrp", LDRSH, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_1c[] = {
/* 0x0 */ {0, "BIC lli", BIC, "action_copy", "Clear bits in register (NAND)"},
/* 0x1 */ {0, "BIC llr", BIC, "action_copy", "Clear bits in register (NAND)"},
/* 0x2 */ {0, "BIC lri", BIC, "action_copy", "Clear bits in register (NAND)"},
/* 0x3 */ {0, "BIC lrr", BIC, "action_copy", "Clear bits in register (NAND)"},
/* 0x4 */ {0, "BIC ari", BIC, "action_copy", "Clear bits in register (NAND)"},
/* 0x5 */ {0, "BIC arr", BIC, "action_copy", "Clear bits in register (NAND)"},
/* 0x6 */ {0, "BIC rri", BIC, "action_copy", "Clear bits in register (NAND)"},
/* 0x7 */ {0, "BIC rrr", BIC, "action_copy", "Clear bits in register (NAND)"},
/* 0x8 */ {0, "BIC lli", BIC, "action_copy", "Clear bits in register (NAND)"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "BIC lri", BIC, "action_copy", "Clear bits in register (NAND)"},
/* 0xb */ {0, "STRH ofip", STRH, "action_copy", "Store halfword"},
/* 0xc */ {0, "BIC ari", BIC, "action_copy", "Clear bits in register (NAND)"},
/* 0xd */ {0, "LDRD ofip", LDRD, "action_copy", "Load doubleword"},
/* 0xe */ {0, "BIC rri", BIC, "action_copy", "Clear bits in register (NAND)"},
/* 0xf */ {0, "STRD ofip", STRD, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_1d[] = {
/* 0x0 */ {0, "BICS lli", BICS, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x1 */ {0, "BICS llr", BICS, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x2 */ {0, "BICS lri", BICS, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x3 */ {0, "BICS lrr", BICS, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x4 */ {0, "BICS ari", BICS, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x5 */ {0, "BICS arr", BICS, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x6 */ {0, "BICS rri", BICS, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x7 */ {0, "BICS rrr", BICS, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x8 */ {0, "BICS lli", BICS, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "BICS lri", BICS, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0xb */ {0, "LDRH ofip", LDRH, "action_copy", "Load halfword"},
/* 0xc */ {0, "BICS ari", BICS, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0xd */ {0, "LDRSB ofip", LDRSB, "action_copy", "Load signed byte"},
/* 0xe */ {0, "BICS rri", BICS, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0xf */ {0, "LDRSH ofip", LDRSH, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_1e[] = {
/* 0x0 */ {0, "MVN lli", MVN, "action_copy", "Move negation of value to a register"},
/* 0x1 */ {0, "MVN llr", MVN, "action_copy", "Move negation of value to a register"},
/* 0x2 */ {0, "MVN lri", MVN, "action_copy", "Move negation of value to a register"},
/* 0x3 */ {0, "MVN lrr", MVN, "action_copy", "Move negation of value to a register"},
/* 0x4 */ {0, "MVN ari", MVN, "action_copy", "Move negation of value to a register"},
/* 0x5 */ {0, "MVN arr", MVN, "action_copy", "Move negation of value to a register"},
/* 0x6 */ {0, "MVN rri", MVN, "action_copy", "Move negation of value to a register"},
/* 0x7 */ {0, "MVN rrr", MVN, "action_copy", "Move negation of value to a register"},
/* 0x8 */ {0, "MVN lli", MVN, "action_copy", "Move negation of value to a register"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "MVN lri", MVN, "action_copy", "Move negation of value to a register"},
/* 0xb */ {0, "STRH prip", STRH, "action_copy", "Store halfword"},
/* 0xc */ {0, "MVN ari", MVN, "action_copy", "Move negation of value to a register"},
/* 0xd */ {0, "LDRD prip", LDRD, "action_copy", "Load doubleword"},
/* 0xe */ {0, "MVN rri", MVN, "action_copy", "Move negation of value to a register"},
/* 0xf */ {0, "STRD prip", STRD, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_1f[] = {
/* 0x0 */ {0, "MVNS lli", MVNS, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x1 */ {0, "MVNS llr", MVNS, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x2 */ {0, "MVNS lri", MVNS, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x3 */ {0, "MVNS lrr", MVNS, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x4 */ {0, "MVNS ari", MVNS, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x5 */ {0, "MVNS arr", MVNS, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x6 */ {0, "MVNS rri", MVNS, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x7 */ {0, "MVNS rrr", MVNS, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x8 */ {0, "MVNS lli", MVNS, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "MVNS lri", MVNS, "action_copy", "Move negation of value to a register, setting flags"},
/* 0xb */ {0, "LDRH prip", LDRH, "action_copy", "Load halfword"},
/* 0xc */ {0, "MVNS ari", MVNS, "action_copy", "Move negation of value to a register, setting flags"},
/* 0xd */ {0, "LDRSB prip", LDRSB, "action_copy", "Load signed byte"},
/* 0xe */ {0, "MVNS rri", MVNS, "action_copy", "Move negation of value to a register, setting flags"},
/* 0xf */ {0, "LDRSH prip", LDRSH, "action_copy", "Load signed halfword"}
};

/* gap */

/* bits 7-4 */
instr_description table_opcode_60[] = {
/* 0x0 */ {0, "STR ptrmll", STR, "action_copy", "Store word"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STR ptrmlr", STR, "action_copy", "Store word"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STR ptrmar", STR, "action_copy", "Store word"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STR ptrmrr", STR, "action_copy", "Store word"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STR ptrmll", STR, "action_copy", "Store word"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STR ptrmlr", STR, "action_copy", "Store word"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STR ptrmar", STR, "action_copy", "Store word"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STR ptrmrr", STR, "action_copy", "Store word"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_61[] = {
/* 0x0 */ {0, "LDR ptrmll", LDR, "action_copy", "Load word"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDR ptrmlr", LDR, "action_copy", "Load word"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDR ptrmar", LDR, "action_copy", "Load word"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDR ptrmrr", LDR, "action_copy", "Load word"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDR ptrmll", LDR, "action_copy", "Load word"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDR ptrmlr", LDR, "action_copy", "Load word"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDR ptrmar", LDR, "action_copy", "Load word"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDR ptrmrr", LDR, "action_copy", "Load word"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_62[] = {
/* 0x0 */ {0, "STRT ptrmll", STRT, "action_copy", "Store word from user-mode register"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRT ptrmlr", STRT, "action_copy", "Store word from user-mode register"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRT ptrmar", STRT, "action_copy", "Store word from user-mode register"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRT ptrmrr", STRT, "action_copy", "Store word from user-mode register"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRT ptrmll", STRT, "action_copy", "Store word from user-mode register"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRT ptrmlr", STRT, "action_copy", "Store word from user-mode register"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRT ptrmar", STRT, "action_copy", "Store word from user-mode register"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRT ptrmrr", STRT, "action_copy", "Store word from user-mode register"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_63[] = {
/* 0x0 */ {0, "LDRT ptrmll", LDRT, "action_copy", "Load word into user-mode register"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRT ptrmlr", LDRT, "action_copy", "Load word into user-mode register"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRT ptrmar", LDRT, "action_copy", "Load word into user-mode register"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRT ptrmrr", LDRT, "action_copy", "Load word into user-mode register"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRT ptrmll", LDRT, "action_copy", "Load word into user-mode register"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRT ptrmlr", LDRT, "action_copy", "Load word into user-mode register"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRT ptrmar", LDRT, "action_copy", "Load word into user-mode register"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRT ptrmrr", LDRT, "action_copy", "Load word into user-mode register"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_64[] = {
/* 0x0 */ {0, "STRB ptrmll", STRB, "action_copy", "Store byte"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRB ptrmlr", STRB, "action_copy", "Store byte"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRB ptrmar", STRB, "action_copy", "Store byte"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRB ptrmrr", STRB, "action_copy", "Store byte"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRB ptrmll", STRB, "action_copy", "Store byte"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRB ptrmlr", STRB, "action_copy", "Store byte"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRB ptrmar", STRB, "action_copy", "Store byte"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRB ptrmrr", STRB, "action_copy", "Store byte"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_65[] = {
/* 0x0 */ {0, "LDRB ptrmll", LDRB, "action_copy", "Load byte"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRB ptrmlr", LDRB, "action_copy", "Load byte"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRB ptrmar", LDRB, "action_copy", "Load byte"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRB ptrmrr", LDRB, "action_copy", "Load byte"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRB ptrmll", LDRB, "action_copy", "Load byte"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRB ptrmlr", LDRB, "action_copy", "Load byte"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRB ptrmar", LDRB, "action_copy", "Load byte"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRB ptrmrr", LDRB, "action_copy", "Load byte"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_66[] = {
/* 0x0 */ {0, "STRBT ptrmll", STRBT, "action_copy", "Store byte from user-mode register"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRBT ptrmlr", STRBT, "action_copy", "Store byte from user-mode register"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRBT ptrmar", STRBT, "action_copy", "Store byte from user-mode register"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRBT ptrmrr", STRBT, "action_copy", "Store byte from user-mode register"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRBT ptrmll", STRBT, "action_copy", "Store byte from user-mode register"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRBT ptrmlr", STRBT, "action_copy", "Store byte from user-mode register"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRBT ptrmar", STRBT, "action_copy", "Store byte from user-mode register"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRBT ptrmrr", STRBT, "action_copy", "Store byte from user-mode register"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_67[] = {
/* 0x0 */ {0, "LDRBT ptrmll", LDRBT, "action_copy", "Load byte into user-mode register"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRBT ptrmlr", LDRBT, "action_copy", "Load byte into user-mode register"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRBT ptrmar", LDRBT, "action_copy", "Load byte into user-mode register"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRBT ptrmrr", LDRBT, "action_copy", "Load byte into user-mode register"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRBT ptrmll", LDRBT, "action_copy", "Load byte into user-mode register"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRBT ptrmlr", LDRBT, "action_copy", "Load byte into user-mode register"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRBT ptrmar", LDRBT, "action_copy", "Load byte into user-mode register"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRBT ptrmrr", LDRBT, "action_copy", "Load byte into user-mode register"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_68[] = {
/* 0x0 */ {0, "STR ptrpll", STR, "action_copy", "Store word"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STR ptrplr", STR, "action_copy", "Store word"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STR ptrpar", STR, "action_copy", "Store word"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STR ptrprr", STR, "action_copy", "Store word"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STR ptrpll", STR, "action_copy", "Store word"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STR ptrplr", STR, "action_copy", "Store word"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STR ptrpar", STR, "action_copy", "Store word"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STR ptrprr", STR, "action_copy", "Store word"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_69[] = {
/* 0x0 */ {0, "LDR ptrpll", LDR, "action_copy", "Load word"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDR ptrplr", LDR, "action_copy", "Load word"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDR ptrpar", LDR, "action_copy", "Load word"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDR ptrprr", LDR, "action_copy", "Load word"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDR ptrpll", LDR, "action_copy", "Load word"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDR ptrplr", LDR, "action_copy", "Load word"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDR ptrpar", LDR, "action_copy", "Load word"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDR ptrprr", LDR, "action_copy", "Load word"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_6a[] = {
/* 0x0 */ {0, "STRT ptrpll", STRT, "action_copy", "Store word from user-mode register"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRT ptrplr", STRT, "action_copy", "Store word from user-mode register"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRT ptrpar", STRT, "action_copy", "Store word from user-mode register"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRT ptrprr", STRT, "action_copy", "Store word from user-mode register"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRT ptrpll", STRT, "action_copy", "Store word from user-mode register"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRT ptrplr", STRT, "action_copy", "Store word from user-mode register"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRT ptrpar", STRT, "action_copy", "Store word from user-mode register"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRT ptrprr", STRT, "action_copy", "Store word from user-mode register"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_6b[] = {
/* 0x0 */ {0, "LDRT ptrpll", LDRT, "action_copy", "Load word into user-mode register"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRT ptrplr", LDRT, "action_copy", "Load word into user-mode register"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRT ptrpar", LDRT, "action_copy", "Load word into user-mode register"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRT ptrprr", LDRT, "action_copy", "Load word into user-mode register"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRT ptrpll", LDRT, "action_copy", "Load word into user-mode register"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRT ptrplr", LDRT, "action_copy", "Load word into user-mode register"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRT ptrpar", LDRT, "action_copy", "Load word into user-mode register"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRT ptrprr", LDRT, "action_copy", "Load word into user-mode register"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_6c[] = {
/* 0x0 */ {0, "STRB ptrpll", STRB, "action_copy", "Store byte"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRB ptrplr", STRB, "action_copy", "Store byte"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRB ptrpar", STRB, "action_copy", "Store byte"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRB ptrprr", STRB, "action_copy", "Store byte"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRB ptrpll", STRB, "action_copy", "Store byte"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRB ptrplr", STRB, "action_copy", "Store byte"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRB ptrpar", STRB, "action_copy", "Store byte"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRB ptrprr", STRB, "action_copy", "Store byte"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_6d[] = {
/* 0x0 */ {0, "LDRB ptrpll", LDRB, "action_copy", "Load byte"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRB ptrplr", LDRB, "action_copy", "Load byte"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRB ptrpar", LDRB, "action_copy", "Load byte"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRB ptrprr", LDRB, "action_copy", "Load byte"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRB ptrpll", LDRB, "action_copy", "Load byte"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRB ptrplr", LDRB, "action_copy", "Load byte"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRB ptrpar", LDRB, "action_copy", "Load byte"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRB ptrprr", LDRB, "action_copy", "Load byte"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_6e[] = {
/* 0x0 */ {0, "STRBT ptrpll", STRBT, "action_copy", "Store byte from user-mode register"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRBT ptrplr", STRBT, "action_copy", "Store byte from user-mode register"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRBT ptrpar", STRBT, "action_copy", "Store byte from user-mode register"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRBT ptrprr", STRBT, "action_copy", "Store byte from user-mode register"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRBT ptrpll", STRBT, "action_copy", "Store byte from user-mode register"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRBT ptrplr", STRBT, "action_copy", "Store byte from user-mode register"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRBT ptrpar", STRBT, "action_copy", "Store byte from user-mode register"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRBT ptrprr", STRBT, "action_copy", "Store byte from user-mode register"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_6f[] = {
/* 0x0 */ {0, "LDRBT ptrpll", LDRBT, "action_copy", "Load byte into user-mode register"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRBT ptrplr", LDRBT, "action_copy", "Load byte into user-mode register"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRBT ptrpar", LDRBT, "action_copy", "Load byte into user-mode register"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRBT ptrprr", LDRBT, "action_copy", "Load byte into user-mode register"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRBT ptrpll", LDRBT, "action_copy", "Load byte into user-mode register"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRBT ptrplr", LDRBT, "action_copy", "Load byte into user-mode register"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRBT ptrpar", LDRBT, "action_copy", "Load byte into user-mode register"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRBT ptrprr", LDRBT, "action_copy", "Load byte into user-mode register"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_70[] = {
/* 0x0 */ {0, "STR ofrmll", STR, "action_copy", "Store word"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STR ofrmlr", STR, "action_copy", "Store word"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STR ofrmar", STR, "action_copy", "Store word"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STR ofrmrr", STR, "action_copy", "Store word"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STR ofrmll", STR, "action_copy", "Store word"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STR ofrmlr", STR, "action_copy", "Store word"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STR ofrmar", STR, "action_copy", "Store word"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STR ofrmrr", STR, "action_copy", "Store word"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_71[] = {
/* 0x0 */ {0, "LDR ofrmll", LDR, "action_copy", "Load word"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDR ofrmlr", LDR, "action_copy", "Load word"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDR ofrmar", LDR, "action_copy", "Load word"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDR ofrmrr", LDR, "action_copy", "Load word"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDR ofrmll", LDR, "action_copy", "Load word"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDR ofrmlr", LDR, "action_copy", "Load word"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDR ofrmar", LDR, "action_copy", "Load word"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDR ofrmrr", LDR, "action_copy", "Load word"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_72[] = {
/* 0x0 */ {0, "STR prrmll", STR, "action_copy", "Store word"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STR prrmlr", STR, "action_copy", "Store word"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STR prrmar", STR, "action_copy", "Store word"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STR prrmrr", STR, "action_copy", "Store word"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STR prrmll", STR, "action_copy", "Store word"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STR prrmlr", STR, "action_copy", "Store word"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STR prrmar", STR, "action_copy", "Store word"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STR prrmrr", STR, "action_copy", "Store word"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_73[] = {
/* 0x0 */ {0, "LDR prrmll", LDR, "action_copy", "Load word"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDR prrmlr", LDR, "action_copy", "Load word"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDR prrmar", LDR, "action_copy", "Load word"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDR prrmrr", LDR, "action_copy", "Load word"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDR prrmll", LDR, "action_copy", "Load word"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDR prrmlr", LDR, "action_copy", "Load word"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDR prrmar", LDR, "action_copy", "Load word"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDR prrmrr", LDR, "action_copy", "Load word"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_74[] = {
/* 0x0 */ {0, "STRB ofrmll", STRB, "action_copy", "Store byte"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRB ofrmlr", STRB, "action_copy", "Store byte"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRB ofrmar", STRB, "action_copy", "Store byte"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRB ofrmrr", STRB, "action_copy", "Store byte"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRB ofrmll", STRB, "action_copy", "Store byte"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRB ofrmlr", STRB, "action_copy", "Store byte"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRB ofrmar", STRB, "action_copy", "Store byte"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRB ofrmrr", STRB, "action_copy", "Store byte"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_75[] = {
/* 0x0 */ {0, "LDRB ofrmll", LDRB, "action_copy", "Load byte"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRB ofrmlr", LDRB, "action_copy", "Load byte"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRB ofrmar", LDRB, "action_copy", "Load byte"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRB ofrmrr", LDRB, "action_copy", "Load byte"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRB ofrmll", LDRB, "action_copy", "Load byte"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRB ofrmlr", LDRB, "action_copy", "Load byte"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRB ofrmar", LDRB, "action_copy", "Load byte"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRB ofrmrr", LDRB, "action_copy", "Load byte"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_76[] = {
/* 0x0 */ {0, "STRB prrmll", STRB, "action_copy", "Store byte"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRB prrmlr", STRB, "action_copy", "Store byte"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRB prrmar", STRB, "action_copy", "Store byte"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRB prrmrr", STRB, "action_copy", "Store byte"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRB prrmll", STRB, "action_copy", "Store byte"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRB prrmlr", STRB, "action_copy", "Store byte"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRB prrmar", STRB, "action_copy", "Store byte"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRB prrmrr", STRB, "action_copy", "Store byte"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_77[] = {
/* 0x0 */ {0, "LDRB prrmll", LDRB, "action_copy", "Load byte"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRB prrmlr", LDRB, "action_copy", "Load byte"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRB prrmar", LDRB, "action_copy", "Load byte"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRB prrmrr", LDRB, "action_copy", "Load byte"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRB prrmll", LDRB, "action_copy", "Load byte"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRB prrmlr", LDRB, "action_copy", "Load byte"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRB prrmar", LDRB, "action_copy", "Load byte"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRB prrmrr", LDRB, "action_copy", "Load byte"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_78[] = {
/* 0x0 */ {0, "STR ofrpll", STR, "action_copy", "Store word"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STR ofrplr", STR, "action_copy", "Store word"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STR ofrpar", STR, "action_copy", "Store word"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STR ofrprr", STR, "action_copy", "Store word"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STR ofrpll", STR, "action_copy", "Store word"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STR ofrplr", STR, "action_copy", "Store word"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STR ofrpar", STR, "action_copy", "Store word"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STR ofrprr", STR, "action_copy", "Store word"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_79[] = {
/* 0x0 */ {0, "LDR ofrpll", LDR, "action_copy", "Load word"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDR ofrplr", LDR, "action_copy", "Load word"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDR ofrpar", LDR, "action_copy", "Load word"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDR ofrprr", LDR, "action_copy", "Load word"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDR ofrpll", LDR, "action_copy", "Load word"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDR ofrplr", LDR, "action_copy", "Load word"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDR ofrpar", LDR, "action_copy", "Load word"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDR ofrprr", LDR, "action_copy", "Load word"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_7a[] = {
/* 0x0 */ {0, "STR prrpll", STR, "action_copy", "Store word"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STR prrplr", STR, "action_copy", "Store word"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STR prrpar", STR, "action_copy", "Store word"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STR prrprr", STR, "action_copy", "Store word"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STR prrpll", STR, "action_copy", "Store word"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STR prrplr", STR, "action_copy", "Store word"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STR prrpar", STR, "action_copy", "Store word"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STR prrprr", STR, "action_copy", "Store word"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_7b[] = {
/* 0x0 */ {0, "LDR prrpll", LDR, "action_copy", "Load word"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDR prrplr", LDR, "action_copy", "Load word"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDR prrpar", LDR, "action_copy", "Load word"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDR prrprr", LDR, "action_copy", "Load word"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDR prrpll", LDR, "action_copy", "Load word"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDR prrplr", LDR, "action_copy", "Load word"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDR prrpar", LDR, "action_copy", "Load word"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDR prrprr", LDR, "action_copy", "Load word"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_7c[] = {
/* 0x0 */ {0, "STRB ofrpll", STRB, "action_copy", "Store byte"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRB ofrplr", STRB, "action_copy", "Store byte"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRB ofrpar", STRB, "action_copy", "Store byte"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRB ofrprr", STRB, "action_copy", "Store byte"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRB ofrpll", STRB, "action_copy", "Store byte"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRB ofrplr", STRB, "action_copy", "Store byte"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRB ofrpar", STRB, "action_copy", "Store byte"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRB ofrprr", STRB, "action_copy", "Store byte"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_7d[] = {
/* 0x0 */ {0, "LDRB ofrpll", LDRB, "action_copy", "Load byte"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRB ofrplr", LDRB, "action_copy", "Load byte"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRB ofrpar", LDRB, "action_copy", "Load byte"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRB ofrprr", LDRB, "action_copy", "Load byte"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRB ofrpll", LDRB, "action_copy", "Load byte"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRB ofrplr", LDRB, "action_copy", "Load byte"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRB ofrpar", LDRB, "action_copy", "Load byte"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRB ofrprr", LDRB, "action_copy", "Load byte"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_7e[] = {
/* 0x0 */ {0, "STRB prrpll", STRB, "action_copy", "Store byte"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRB prrplr", STRB, "action_copy", "Store byte"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRB prrpar", STRB, "action_copy", "Store byte"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRB prrprr", STRB, "action_copy", "Store byte"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRB prrpll", STRB, "action_copy", "Store byte"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRB prrplr", STRB, "action_copy", "Store byte"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRB prrpar", STRB, "action_copy", "Store byte"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRB prrprr", STRB, "action_copy", "Store byte"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_7f[] = {
/* 0x0 */ {0, "LDRB prrpll", LDRB, "action_copy", "Load byte"},
/* 0x1 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRB prrplr", LDRB, "action_copy", "Load byte"},
/* 0x3 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRB prrpar", LDRB, "action_copy", "Load byte"},
/* 0x5 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRB prrprr", LDRB, "action_copy", "Load byte"},
/* 0x7 */ {0, "", NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRB prrpll", LDRB, "action_copy", "Load byte"},
/* 0x9 */ {0, "", NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRB prrplr", LDRB, "action_copy", "Load byte"},
/* 0xb */ {0, "", NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRB prrpar", LDRB, "action_copy", "Load byte"},
/* 0xd */ {0, "", NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRB prrprr", LDRB, "action_copy", "Load byte"},
/* 0xf */ {0, "", NONE, "", "UNDEFINED"}
};

/* bits 27-20 */
instr_description table_opcode_onebyte[] = {
/* 0x00 */ {table_opcode_00, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x01 */ {table_opcode_01, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x02 */ {table_opcode_02, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x03 */ {table_opcode_03, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x04 */ {table_opcode_04, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x05 */ {table_opcode_05, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x06 */ {table_opcode_06, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x07 */ {table_opcode_07, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x08 */ {table_opcode_08, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x09 */ {table_opcode_09, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x0a */ {table_opcode_0a, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x0b */ {table_opcode_0b, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x0c */ {table_opcode_0c, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x0d */ {table_opcode_0d, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x0e */ {table_opcode_0e, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x0f */ {table_opcode_0f, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x10 */ {table_opcode_10, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x11 */ {table_opcode_11, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x12 */ {table_opcode_12, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x13 */ {table_opcode_13, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x14 */ {table_opcode_14, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x15 */ {table_opcode_15, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x16 */ {table_opcode_16, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x17 */ {table_opcode_17, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x18 */ {table_opcode_18, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x19 */ {table_opcode_19, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x1a */ {table_opcode_1a, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x1b */ {table_opcode_1b, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x1c */ {table_opcode_1c, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x1d */ {table_opcode_1d, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x1e */ {table_opcode_1e, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x1f */ {table_opcode_1f, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x20 */ {0, "AND imm", AND, "action_copy", "Logical And"},
/* 0x21 */ {0, "ANDS imm", ANDS, "action_copy", "Logical And, setting flags"},
/* 0x22 */ {0, "EOR imm", EOR, "action_copy", "Logical Exclusive-or"},
/* 0x23 */ {0, "EORS imm", EORS, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x24 */ {0, "SUB imm", SUB, "action_copy", "Subtract from register"},
/* 0x25 */ {0, "SUBS imm", SUBS, "action_copy", "Subtract, setting flags"},
/* 0x26 */ {0, "RSB imm", RSB, "action_copy", "Subtract register from value"},
/* 0x27 */ {0, "RSBS imm", RSBS, "action_copy", "Reverse Subtract, setting flags"},
/* 0x28 */ {0, "ADD imm", ADD, "action_copy", "Add to register"},
/* 0x29 */ {0, "ADDS imm", ADDS, "action_copy", "Add to register, setting flags"},
/* 0x2a */ {0, "ADC imm", ADC, "action_copy", "Add to register with carry"},
/* 0x2b */ {0, "ADCS imm", ADCS, "action_copy", "Add to register with carry, setting flags"},
/* 0x2c */ {0, "SBC imm", SBC, "action_copy", "Subtract from register with borrow"},
/* 0x2d */ {0, "SBCS imm", SBCS, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x2e */ {0, "RSC imm", RSC, "action_copy", "Subtract register from value with borrow"},
/* 0x2f */ {0, "RSCS imm", RSCS, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x30 */ {0, "UNDEFINED", NONE, "", "NO_ACTION_CALLED"},
/* 0x31 */ {0, "TSTS imm", TSTS, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x32 */ {0, "MSR ic", MSR, "action_copy", "Move value to status word"},
/* 0x33 */ {0, "TEQS imm", TEQS, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x34 */ {0, "UNDEFINED", NONE, "", "NO_ACTION_CALLED"},
/* 0x35 */ {0, "CMPS imm", CMPS, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x36 */ {0, "MSR is", MSR, "action_copy", "Move value to status word"},
/* 0x37 */ {0, "CMNS imm", CMNS, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x38 */ {0, "ORR imm", ORR, "action_copy", "Logical Or"},
/* 0x39 */ {0, "ORRS imm", ORRS, "action_copy", "Logical Or, setting flags"},
/* 0x3a */ {0, "MOV imm", MOV, "action_copy", "Move value to a register"},
/* 0x3b */ {0, "MOVS imm", MOVS, "action_copy", "Move value to a register, setting flags"},
/* 0x3c */ {0, "BIC imm", BIC, "action_copy", "Clear bits in register (NAND)"},
/* 0x3d */ {0, "BICS imm", BICS, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x3e */ {0, "MVN imm", MVN, "action_copy", "Move negation of value to a register"},
/* 0x3f */ {0, "MVNS imm", MVNS, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x40 */ {0, "STR ptim", STR, "action_copy", "Store word"},
/* 0x41 */ {0, "LDR ptim", LDR, "action_copy", "Load word"},
/* 0x42 */ {0, "STRT ptim", STRT, "action_copy", "Store word from user-mode register"},
/* 0x43 */ {0, "LDRT ptim", LDRT, "action_copy", "Load word into user-mode register"},
/* 0x44 */ {0, "STRB ptim", STRB, "action_copy", "Store byte"},
/* 0x45 */ {0, "LDRB ptim", LDRB, "action_copy", "Load byte"},
/* 0x46 */ {0, "STRBT ptim", STRBT, "action_copy", "Store byte from user-mode register"},
/* 0x47 */ {0, "LDRBT ptim", LDRBT, "action_copy", "Load byte into user-mode register"},
/* 0x48 */ {0, "STR ptip", STR, "action_copy", "Store word"},
/* 0x49 */ {0, "LDR ptip", LDR, "action_copy", "Load word"},
/* 0x4a */ {0, "STRT ptip", STRT, "action_copy", "Store word from user-mode register"},
/* 0x4b */ {0, "LDRT ptip", LDRT, "action_copy", "Load word into user-mode register"},
/* 0x4c */ {0, "STRB ptip", STRB, "action_copy", "Store byte"},
/* 0x4d */ {0, "LDRB ptip", LDRB, "action_copy", "Load byte"},
/* 0x4e */ {0, "STRBT ptip", STRBT, "action_copy", "Store byte from user-mode register"},
/* 0x4f */ {0, "LDRBT ptip", LDRBT, "action_copy", "Load byte into user-mode register"},
/* 0x50 */ {0, "STR ofim", STR, "action_copy", "Store word"},
/* 0x51 */ {0, "LDR ofim", LDR, "action_copy", "Load word"},
/* 0x52 */ {0, "STR prim", STR, "action_copy", "Store word"},
/* 0x53 */ {0, "LDR prim", LDR, "action_copy", "Load word"},
/* 0x54 */ {0, "STRB ofim", STRB, "action_copy", "Store byte"},
/* 0x55 */ {0, "LDRB ofim", LDRB, "action_copy", "Load byte"},
/* 0x56 */ {0, "STRB prim", STRB, "action_copy", "Store byte"},
/* 0x57 */ {0, "LDRB prim", LDRB, "action_copy", "Load byte"},
/* 0x58 */ {0, "STR ofip", STR, "action_copy", "Store word"},
/* 0x59 */ {0, "LDR ofip", LDR, "action_copy", "Load word"},
/* 0x5a */ {0, "STR prip", STR, "action_copy", "Store word"},
/* 0x5b */ {0, "LDR prip", LDR, "action_copy", "Load word"},
/* 0x5c */ {0, "STRB ofip", STRB, "action_copy", "Store byte"},
/* 0x5d */ {0, "LDRB ofip", LDRB, "action_copy", "Load byte"},
/* 0x5e */ {0, "STRB prip", STRB, "action_copy", "Store byte"},
/* 0x5f */ {0, "LDRB prip", LDRB, "action_copy", "Load byte"},
/* 0x60 */ {table_opcode_60, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x61 */ {table_opcode_61, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x62 */ {table_opcode_62, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x63 */ {table_opcode_63, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x64 */ {table_opcode_64, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x65 */ {table_opcode_65, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x66 */ {table_opcode_66, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x67 */ {table_opcode_67, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x68 */ {table_opcode_68, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x69 */ {table_opcode_69, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x6a */ {table_opcode_6a, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x6b */ {table_opcode_6b, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x6c */ {table_opcode_6c, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x6d */ {table_opcode_6d, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x6e */ {table_opcode_6e, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x6f */ {table_opcode_6f, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x70 */ {table_opcode_70, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x71 */ {table_opcode_71, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x72 */ {table_opcode_72, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x73 */ {table_opcode_73, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x74 */ {table_opcode_74, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x75 */ {table_opcode_75, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x76 */ {table_opcode_76, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x77 */ {table_opcode_77, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x78 */ {table_opcode_78, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x79 */ {table_opcode_79, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x7a */ {table_opcode_7a, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x7b */ {table_opcode_7b, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x7c */ {table_opcode_7c, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x7d */ {table_opcode_7d, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x7e */ {table_opcode_7e, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x7f */ {table_opcode_7f, "", NONE, "", "NO_ACTION_CALLED"},
/* 0x80 */ {0, "STMDA", STMDA, "action_copy", "Store multiple words, decrement after"},
/* 0x81 */ {0, "LDMDA", LDMDA, "action_copy", "Load multiple words, decrement after"},
/* 0x82 */ {0, "STMDA w", STMDA, "action_copy", "Store multiple words, decrement after"},
/* 0x83 */ {0, "LDMDA w", LDMDA, "action_copy", "Load multiple words, decrement after"},
/* 0x84 */ {0, "STMDA u", STMDA, "action_copy", "Store multiple words, decrement after"},
/* 0x85 */ {0, "LDMDA u", LDMDA, "action_copy", "Load multiple words, decrement after"},
/* 0x86 */ {0, "STMDA uw", STMDA, "action_copy", "Store multiple words, decrement after"},
/* 0x87 */ {0, "LDMDA uw", NONE, "action_copy", "Load multiple words, decrement after"},
/* 0x88 */ {0, "STMIA", STMIA, "action_copy", "Store multiple words, increment after"},
/* 0x89 */ {0, "LDMIA", LDMIA, "action_copy", "Load multiple words, increment after"},
/* 0x8a */ {0, "STMIA w", STMIA, "action_copy", "Store multiple words, increment after"},
/* 0x8b */ {0, "LDMIA w", LDMIA, "action_copy", "Load multiple words, increment after"},
/* 0x8c */ {0, "STMIA u", STMIA, "action_copy", "Store multiple words, increment after"},
/* 0x8d */ {0, "LDMIA u", LDMIA, "action_copy", "Load multiple words, increment after"},
/* 0x8e */ {0, "STMIA uw", STMIA, "action_copy", "Store multiple words, increment after"},
/* 0x8f */ {0, "LDMIA uw", LDMIA, "action_copy", "Load multiple words, increment after"},
/* 0x90 */ {0, "STMDB", STMDB, "action_copy", "Store multiple words, decrement before"},
/* 0x91 */ {0, "LDMDB", LDMDB, "action_copy", "Load multiple words, decrement before"},
/* 0x92 */ {0, "STMDB w", STMDB, "action_copy", "Store multiple words, decrement before"},
/* 0x93 */ {0, "LDMDB w", LDMDB, "action_copy", "Load multiple words, decrement before"},
/* 0x94 */ {0, "STMDB u", STMDB, "action_copy", "Store multiple words, decrement before"},
/* 0x95 */ {0, "LDMDB u", LDMDB, "action_copy", "Load multiple words, decrement before"},
/* 0x96 */ {0, "STMDB uw", STMDB, "action_copy", "Store multiple words, decrement before"},
/* 0x97 */ {0, "LDMDB uw", LDMDB, "action_copy", "Load multiple words, decrement before"},
/* 0x98 */ {0, "STMIB", STMIB, "action_copy", "Store multiple words, increment before"},
/* 0x99 */ {0, "LDMIB", LDMIB, "action_copy", "Load multiple words, increment before"},
/* 0x9a */ {0, "STMIB w", STMIB, "action_copy", "Store multiple words, increment before"},
/* 0x9b */ {0, "LDMIB w", LDMIB, "action_copy", "Load multiple words, increment before"},
/* 0x9c */ {0, "STMIB u", STMIB, "action_copy", "Store multiple words, increment before"},
/* 0x9d */ {0, "LDMIB u", LDMIB, "action_copy", "Load multiple words, increment before"},
/* 0x9e */ {0, "STMIB uw", STMIB, "action_copy", "Store multiple words, increment before"},
/* 0x9f */ {0, "LDMIB uw", LDMIB, "action_copy", "Load multiple words, increment before"},
/* 0xa0 */ {0, "B", B, "action_copy", "Branch"},
/* 0xa1 */ {0, "B", B, "action_copy", "Branch"},
/* 0xa2 */ {0, "B", B, "action_copy", "Branch"},
/* 0xa3 */ {0, "B", B, "action_copy", "Branch"},
/* 0xa4 */ {0, "B", B, "action_copy", "Branch"},
/* 0xa5 */ {0, "B", B, "action_copy", "Branch"},
/* 0xa6 */ {0, "B", B, "action_copy", "Branch"},
/* 0xa7 */ {0, "B", B, "action_copy", "Branch"},
/* 0xa8 */ {0, "B", B, "action_copy", "Branch"},
/* 0xa9 */ {0, "B", B, "action_copy", "Branch"},
/* 0xaa */ {0, "B", B, "action_copy", "Branch"},
/* 0xab */ {0, "B", B, "action_copy", "Branch"},
/* 0xac */ {0, "B", B, "action_copy", "Branch"},
/* 0xad */ {0, "B", B, "action_copy", "Branch"},
/* 0xae */ {0, "B", B, "action_copy", "Branch"},
/* 0xaf */ {0, "B", B, "action_copy", "Branch"},
/* 0xB0 */ {0, "BL", BL, "action_copy", "Branch and link"},
/* 0xB1 */ {0, "BL", BL, "action_copy", "Branch and link"},
/* 0xB2 */ {0, "BL", BL, "action_copy", "Branch and link"},
/* 0xB3 */ {0, "BL", BL, "action_copy", "Branch and link"},
/* 0xB4 */ {0, "BL", BL, "action_copy", "Branch and link"},
/* 0xB5 */ {0, "BL", BL, "action_copy", "Branch and link"},
/* 0xB6 */ {0, "BL", BL, "action_copy", "Branch and link"},
/* 0xB7 */ {0, "BL", BL, "action_copy", "Branch and link"},
/* 0xB8 */ {0, "BL", BL, "action_copy", "Branch and link"},
/* 0xB9 */ {0, "BL", BL, "action_copy", "Branch and link"},
/* 0xBA */ {0, "BL", BL, "action_copy", "Branch and link"},
/* 0xBB */ {0, "BL", BL, "action_copy", "Branch and link"},
/* 0xBC */ {0, "BL", BL, "action_copy", "Branch and link"},
/* 0xBD */ {0, "BL", BL, "action_copy", "Branch and link"},
/* 0xBE */ {0, "BL", BL, "action_copy", "Branch and link"},
/* 0xBF */ {0, "BL", BL, "action_copy", "Branch and link"},
/* 0xC0 */ {0, "STC ofm", STC, "action_copy", "Store coprocessor data to memory"},
/* 0xC1 */ {0, "LDC ofm", LDC, "action_copy", "Load coprocessor data from memory"},
/* 0xC2 */ {0, "STC prm", STC, "action_copy", "Store coprocessor data to memory"},
/* 0xC3 */ {0, "LDC prm", LDC, "action_copy", "Load coprocessor data from memory"},
/* 0xC4 */ {0, "STC ofm", STC, "action_copy", "Store coprocessor data to memory"},
/* 0xC5 */ {0, "LDC ofm", LDC, "action_copy", "Load coprocessor data from memory"},
/* 0xC6 */ {0, "STC prm", STC, "action_copy", "Store coprocessor data to memory"},
/* 0xC7 */ {0, "LDC prm", LDC, "action_copy", "Load coprocessor data from memory"},
/* 0xC8 */ {0, "STC ofp", STC, "action_copy", "Store coprocessor data to memory"},
/* 0xC9 */ {0, "LDC ofp", LDC, "action_copy", "Load coprocessor data from memory"},
/* 0xCA */ {0, "STC prp", STC, "action_copy", "Store coprocessor data to memory"},
/* 0xCB */ {0, "LDC prp", LDC, "action_copy", "Load coprocessor data from memory"},
/* 0xCC */ {0, "STC ofp", STC, "action_copy", "Store coprocessor data to memory"},
/* 0xCD */ {0, "LDC ofp", LDC, "action_copy", "Load coprocessor data from memory"},
/* 0xCE */ {0, "STC prp", STC, "action_copy", "Store coprocessor data to memory"},
/* 0xCF */ {0, "LDC prp", LDC, "action_copy", "Load coprocessor data from memory"},
/* 0xD0 */ {0, "STC unm", STC, "action_copy", "Store coprocessor data to memory"},
/* 0xD1 */ {0, "LDC unm", LDC, "action_copy", "Load coprocessor data from memory"},
/* 0xD2 */ {0, "STC ptm", STC, "action_copy", "Store coprocessor data to memory"},
/* 0xD3 */ {0, "LDC ptm", LDC, "action_copy", "Load coprocessor data from memory"},
/* 0xD4 */ {0, "STC unm", STC, "action_copy", "Store coprocessor data to memory"},
/* 0xD5 */ {0, "LDC unm", LDC, "action_copy", "Load coprocessor data from memory"},
/* 0xD6 */ {0, "STC ptm", STC, "action_copy", "Store coprocessor data to memory"},
/* 0xD7 */ {0, "LDC ptm", LDC, "action_copy", "Load coprocessor data from memory"},
/* 0xD8 */ {0, "STC unp", STC, "action_copy", "Store coprocessor data to memory"},
/* 0xD9 */ {0, "LDC unp", LDC, "action_copy", "Load coprocessor data from memory"},
/* 0xDA */ {0, "STC ptp", STC, "action_copy", "Store coprocessor data to memory"},
/* 0xDB */ {0, "LDC ptp", LDC, "action_copy", "Load coprocessor data from memory"},
/* 0xDC */ {0, "STC unp", STC, "action_copy", "Store coprocessor data to memory"},
/* 0xDD */ {0, "LDC unp", LDC, "action_copy", "Load coprocessor data from memory"},
/* 0xDE */ {0, "STC ptp", STC, "action_copy", "Store coprocessor data to memory"},
/* 0xDF */ {0, "LDC ptp", LDC, "action_copy", "Load coprocessor data from memory"}

/* 0xE0 - 0xEF: coprocessor data operations */
/* 0xF0 - 0xFF: software interrupts */
};

#endif  // ARM_OPCODE_MAP

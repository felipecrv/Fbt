#ifndef ARM_OPCODE_MAP
#define ARM_OPCODE_MAP

#include "arm_opcode.h"

/*
## Basic mnemonics

AND = Logical And
MUL = Multiply registers
EOR = Logical Exclusive-or
MLA = Multiply and accumulate registers
SUB = Subtract from register
RSB = Subtract register from value
ADD = Add to register
ADC = Add to register with carry
SBC = Subtract from register with borrow
RSC = Subtract register from value with borrow
MRS = Move status word to register  (ARM6 and later)
SWP = Swap registers with memory word
TST = Test bits in register (Logical And)
MSR = Move value to status word  (ARM6 and later)
TEQ = Test equivalence of bits in register (Logical Exclusive-or)
CMP = Compare register to value (Subtract), setting flags
CMN = Compare register to negation of value (Add), setting flags
ORR = Logical Or
MOV = Move value to a register
BIC = Clear bits in register (NAND)
MVN = Move negation of value to a register
STR = Store word
LDR = Load word
STM = Store multiple words
LDM = Load multiple words
B   = Branch
BL  = Branch and link
SWI = Software interrupt

## Shift descriptions

LSL = Logical Shift Left #n bits
LSR = Logical Shift Right #n bits
ASR = Arithmetic Shift Right #n bits
ROR = Rotate Right #n bits
RRX = Rotate Right 1 bit with Extend (not available in shift-by-register instructions)

## Operand configurations, encoding, and syntax

### Data processing

lli = Logical shift-left by immediate
lri = Logical shift-right by immediate
ari = Arithmetic shift-right by immediate
rri = Rotate right by immediate, or rotate right with extend (RRX)
+------------+-------------------------+-------------+-------------+---------------+-----+---+---------+
|31 30 29 28 | 27 26 25 24 23 22 21 20 | 19 18 17 16 | 15 14 13 12 | 11 10 9 8   7 | 6 5 | 4 | 3 2 1 0 |
+------------+-------------------------+-------------+-------------+---------------+-----+---+---------+
|    cond    |  _  _  0  _  _  _  _  S |      Rn     |      Rd     |      imm5     |type | 0 |   Rm    |
+------------+-------------------------+-------------+-------------+---------------+-----+---+---------+
<mnemonic>{S}{<c>} <Rd>, <Rm>, <Rn>{, shift}

llr = Logical shift-left by register
lrr = Logical shift-right by register
arr = Arithmetic shift-right by register
rrr = Rotate right by register
+------------+-------------------------+-------------+-------------+-----------+---+-----+---+---------+
|31 30 29 28 | 27 26 25 24 23 22 21 20 | 19 18 17 16 | 15 14 13 12 | 11 10 9 8 | 7 | 6 5 | 4 | 3 2 1 0 |
+------------+-------------------------+-------------+-------------+-----------+---+-----+---+---------+
|    cond    |  _  _  0  _  _  _  _  S |     Rn      |      Rd     |     Rs    | 0 |type | 1 |   Rm    |
+------------+-------------------------+-------------+-------------+-----------+---+-----+---+---------+
<mnemonic>{S}{<c>} <Rd>, <Rn>, <Rm>, <type> <Rs>

imm = Immediate value
+------------+-------------------------+-------------+-------------+-----------------------------------+
|31 30 29 28 | 27 26 25 24 23 22 21 20 | 19 18 17 16 | 15 14 13 12 | 11 10 9 8   7   6 5   4   3 2 1 0 |
+------------+-------------------------+-------------+-------------+-----------------------------------+
|    cond    |  _  _  1  _  _  _  _  S |     Rn      |      Rd     |              imm12                |
+------------+-------------------------+-------------+-------------+-----------------------------------+
<mnemonic>{S}{<c>} <Rd>, <Rn>, #<cons>

  Mnemonic   |        Bits 27:20       |      Remarks
-------------+-------------------------+-------------------
    AND{S}   |  0  0  I  0  0  0  0  S |
    EOR{S}   |  0  0  I  0  0  0  1  S |
    SUB{S}   |  0  0  I  0  0  1  0  S |
    RSB{S}   |  0  0  I  0  0  1  1  S |
    ADD{S}   |  0  0  I  0  1  0  0  S |
    ADC{S}   |  0  0  I  0  1  0  1  S |
    SBC{S}   |  0  0  I  0  1  1  0  S |
    RSC{S}   |  0  0  I  0  1  1  1  S |
    TST*     |  0  0  I  1  0  0  0  1 | Rd = (0)(0)(0)(0)
    TEQ*     |  0  0  I  1  0  0  1  1 | Rd = (0)(0)(0)(0)
    CMP*     |  0  0  I  1  0  1  0  1 | Rd = (0)(0)(0)(0)
    CMN*     |  0  0  I  1  0  1  1  1 | Rd = (0)(0)(0)(0)
    ORR{S}   |  0  0  I  1  1  0  0  S |
    MOV{S}   |  0  0  I  1  1  0  1  S | Rn = (0)(0)(0)(0)
    BIC{S}   |  0  0  I  1  1  1  0  S |
    MVN{S}   |  0  0  I  1  1  1  1  S | Rn = (0)(0)(0)(0)

* The data comparison instructions always have the S bit (setting flags) on.
  The S suffix in dropped in the assembly syntax as it would be redundant.

#### Shifts

##### Shifts by immediate

           |  type | by_reg |   imm5
           | [6:5] |   4    |  [11:7]
-----------+-------+--------+----------
           |  0  0 |   0    |    0
  LSL #<n> |  0  0 |   0    |   <n>
  LSR #<n> |  0  1 |   0    | <n> % 32
  ASR #<n> |  1  0 |   0    | <n> % 32
  ROR #<n> |  1  1 |   0    |   <n>
  RRX      |  1  1 |   0    |    0

##### Shifts by register

           |  type | by_reg
           | [6:5] |   4
-----------+-------+--------
  LSL Rs   |  0  0 |   1
  LSR Rs   |  0  1 |   1
  ASR Rs   |  1  0 |   1
  ROR Rs   |  1  1 |   1

### Branches

+------------+-------------+-------------+-------------+-------------+-----------+-------------+---------+
|31 30 29 28 | 27 26 25 24 | 23 22 21 20 | 19 18 17 16 | 15 14 13 12 | 11 10 9 8 | 7   6 5   4 | 3 2 1 0 |
+------------+-------------+-------------+-------------+-------------+-----------+-------------+---------+
|    cond    |  1  0  1  0 |                               imm24                                         | B
+------------+-------------+-------------+-------------+-------------+-----------+-------------+---------+
|    cond    |  1  0  1  1 |                               imm24                                         | BL
+------------+-------------+-------------+-------------+-------------+-----------+-------------+---------+
| 1  1  1  1 |  1  0  1  H |                               imm24                                         | BLX
+------------+-------------+-------------+-------------+-------------+-----------+-------------+---------+
|    cond    |  0  0  0  1    0  0  1  0 | (1)(1)(1)(1) (1)(1)(1)(1) (1)(1)(1)(1)| 0   0 1   1 |   Rm    | BLX
+------------+-------------+-------------+-------------+-------------+-----------+-------------+---------+
|    cond    |  0  0  0  1    0  0  1  0 | (1)(1)(1)(1) (1)(1)(1)(1) (1)(1)(1)(1)| 0   0 0   1 |   Rm    | BX
+------------+-------------+-------------+-------------+-------------+-----------+-------------+---------+
B{<c>} label
BL{<c>} label
BLX label
BLX{<c>} <Rm>
BX{<c>} <Rm>

### MUL and MLA

+------------+-------------------------+-------------+-------------+-----------+-------------+---------+
|31 30 29 28 | 27 26 25 24 23 22 21 20 | 19 18 17 16 | 15 14 13 12 | 11 10 9 8 | 7   6 5   4 | 3 2 1 0 |
+------------+-------------------------+-------------+-------------+-----------+-------------+---------+
|    cond    |  0  0  0  0  0  0  0  S |     Rd      | (0)(0)(0)(0)|    Rm     | 1   0 0   1 |   Rn    | MUL
+------------+-------------------------+-------------+-------------+-----------+-------------+---------+
|    cond    |  0  0  0  0  0  0  1  S |     Rd      |      Ra     |    Rm     | 1   0 0   1 |   Rn    | MLA
+------------+-------------------------+-------------+-------------+-----------+-------------+---------+
MUL{S}{<c>} <Rd>, <Rn>, <Rm>
MLA{S}{<c>} <Rd>, <Rn>, <Rm>, <Ra>

TODO: encoding rules of other multiplication functions

### Load/store

#### 0  1  _

Shifts are applied to the register offset -- Rm.

ptrm<shift> = Register offset, post-decrement
ptrp<shift> = Register offset, post-increment
ofrm<shift> = Negative register offset
prrm<shift> = Register offset, pre-decrement
ofrp<shift> = Positive register offset
prrp<shift> = Register offset, pre-increment"
+------------+-------------------------+-------------+-------------+---------------+-----+---+---------+
|31 30 29 28 | 27 26 25 24 23 22 21 20 | 19 18 17 16 | 15 14 13 12 | 11 10 9 8   7 | 6 5 | 4 | 3 2 1 0 |
+------------+-------------------------+-------------+-------------+---------------+-----+---+---------+
|    cond    |  0  1  1  P  U  B  W  L |      Rn     |      Rt     |      imm5     |type | 0 |   Rm    |
+------------+-------------------------+-------------+-------------+---------------+-----+---+---------+
STR{<c>} <Rt>, [<Rn>,  +/-<Rm>{, <shift>}]   Offset
STR{<c>} <Rt>, [<Rn>,  +/-<Rm>{, <shift>}]!  Pre-dec/increment
STR{<c>} <Rt>, [<Rn>], +/-<Rm>{, <shift>}    Post-dec/increment
Same for: STRB, LDR, LDRB

LDRT{<c>} <Rt>, [<Rn>], +/-<Rm> {, shift}  Post-dec/increment
Same for: LDRBT, STRT, STRBT

ptim = Immediate offset, post-decrement
ptip = Immediate offset, post-increment
ofim = Negative immediate offset
prim = Immediate offset, pre-decrement
ofip = Positive immediate offset
prip = Immediate offset, pre-increment
+------------+-------------------------+-------------+-------------+-----------------------------------+
|31 30 29 28 | 27 26 25 24 23 22 21 20 | 19 18 17 16 | 15 14 13 12 | 11 10 9 8   7   6 5   4   3 2 1 0 |
+------------+-------------------------+-------------+-------------+-----------------------------------+
|    cond    |  0  1  0  P  U  B  W  L |     Rn      |      Rt     |              imm12                |
+------------+-------------------------+-------------+-------------+-----------------------------------+
STR{<c>} <Rt>, [<Rn> {, #+/-<imm}]    Offset:             index=True,  wback=False | mem[Rn +/- imm] := Rt        |
STR{<c>} <Rt>, [<Rn>,   #+/-<imm>]!   Pre-dec/increment:  index=True,  wback=True  | mem[Rn += +/-imm] := Rt      | imm==1: mem[++Rn] := Rt
STR{<c>} <Rt>, [<Rn>],  #+/-<imm>     Post-dec/increment: index=False, wback=True  | mem[Rn] :=  Rt, Rn += +/-imm | imm==1: mem[Rn++] := Rt
Same for: STRB

LDR{<c>} <Rt>, [<Rn> {, #+/-<imm}]    Offset:             index=True,  wback=False | Rt := mem[Rn +/- imm]       |
LDR{<c>} <Rt>, [<Rn>,   #+/-<imm>]!   Pre-dec/increment:  index=True,  wback=True  | Rt := mem[Rn += +/-imm]     | imm==1: Rt := mem[++Rn]
LDR{<c>} <Rt>, [<Rn>],  #+/-<imm>     Post-dec/increment: index=False, wback=True  | Rt := mem[Rn], Rn += +/-imm | imm==1: Rt := mem[Rn++]
Same for: LDRB

LDRT{<c>} <Rt>, [<Rn>] {, #+/-<imm>}  Post-dec/increment
Same for: LDRBT, STRT, STRBT

  Mnemonic   |        Bits 27:20
-------------+-------------------------
    STR      |  0  1  R  P  U  0  W  0
    LDR      |  0  1  R  P  U  0  W  1
    STRB     |  0  1  R  P  U  1  W  0
    LDRB     |  0  1  R  P  U  1  W  1
    STRT     |  0  1  R  0  U  0  1  0
    LDRT     |  0  1  R  0  U  0  1  1
    STRBT    |  0  1  R  0  U  1  1  0
    LDRBT    |  0  1  R  0  U  1  1  1

R = set if the instructiont takes a Register offset
P = set for Pre-dec|increment - clear for post-dec|increment
U = Up/down bit - set for increment - clear for decrement
B = Byte/word transfer - set for Byte transfer
W = set for Write back into base register

#### 0  0  0 (M-extension)

ptrm = Register offset, post-decrement
ptrp = Register offset, post-increment
ofrm = Negative register offset
prrm = Register offset, pre-decrement
ofrp = Positive register offset
prrp = Register offset, pre-increment"
+------------+-------------------------+-------------+-------------+------------+---------+---------+
|31 30 29 28 | 27 26 25 24 23 22 21 20 | 19 18 17 16 | 15 14 13 12 | 11 10 9  8 | 7 6 5 4 | 3 2 1 0 |
+------------+-------------------------+-------------+-------------+------------+---------+---------+
|    cond    |  0  0  0  P  U  0  W  _ |    Rn       |      Rt     |(0)(0)(0)(0)| _ _ _ _ |    Rm   |
+------------+-------------------------+-------------+-------------+------------+---------+---------+
|    cond    |  0  0  0  P  U  0  W  _ |    Rn       |      Rt     |     Rt2    | _ _ _ _ |    Rm   | Dual
+------------+-------------------------+-------------+-------------+------------+---------+---------+
<mnemonic>{<c>} <Rt>, {<Rt2>,} [<Rn>,  +/-<Rm>]   Offset
<mnemonic>{<c>} <Rt>, {<Rt2>,} [<Rn>,  +/-<Rm>]!  Pre-dec/increment
<mnemonic>{<c>} <Rt>, {<Rt2>,} [<Rn>], +/-<Rm>    Post-dec/increment


ptim = Immediate offset, post-decrement
ptip = Immediate offset, post-increment
ofim = Negative immediate offset
prim = Immediate offset, pre-decrement
ofip = Positive immediate offset
prip = Immediate offset, pre-increment
+------------+-------------------------+-------------+-------------+-----------+---------+---------+
|31 30 29 28 | 27 26 25 24 23 22 21 20 | 19 18 17 16 | 15 14 13 12 | 11 10 9 8 | 7 6 5 4 | 3 2 1 0 |
+------------+-------------------------+-------------+-------------+-----------+---------+---------+
|    cond    |  0  0  0  P  U  1  W  _ |    Rn       |      Rt     |   imm4H   | _ _ _ _ |  imm4L  |
+------------+-------------------------+-------------+-------------+-----------+---------+---------+
<mnemonic>{<c>} <Rt>, {<Rt2>,} [<Rn> {, #+/-<imm}]    Offset
<mnemonic>{<c>} <Rt>, {<Rt2>,} [<Rn>,   #+/-<imm>]!   Pre-dec/increment
<mnemonic>{<c>} <Rt>, {<Rt2>,} [<Rn>],  #+/-<imm>     Post-dec/increment

  Mnemonic   |        Bits 27:20       |    Bits 7:4
-------------+-------------------------+--------------
    STRH     |  0  0  0  P  U  I  W  0 |  1  0  1  1
    LDRH     |  0  0  0  P  U  I  W  1 |  1  0  1  1
    STRD     |  0  0  0  P  U  I  W  0 |  1  1  1  1
    LDRD     |  0  0  0  P  U  I  W  0 |  1  1  0  1  The bit 20 is 0 and it's a load!
    LDRSB    |  0  0  0  P  U  I  W  1 |  1  1  0  1
    LDRSH    |  0  0  0  P  U  I  W  1 |  1  1  1  1


P = set for Pre-dec|increment - clear for post-dec|increment
U = Up/down bit - set for increment - clear for decrement
I = set if the instruction takes an Immediate offset
W = set for Write back into base register

###

rc =
rs =
TODO: MRS

ic = Immediate, CPSR
is = Immediate, SPSR
TODO: MSR

TODO: saturating addition/subtraction

prrmll = Left-shifted register offset, pre-decrement
prrmlr = Right-shifted register offset, pre-decrement
prrmar = Arithmetic-right-shifted register offset, pre-decrement
prrmrr = Right-rotated register offset, pre-decrement
ofrmll = Negative left-shifted register offset
ofrmlr = Negative right-shifted register offset
ofrmar = Negative arithmetic-right-shifted register offset
ofrmrr = Negative right-rotated register offset
ofrpll = Positive left-shifted register offset
ofrplr = Positive right-shifted register offset
ofrpar = Positive arithmetic-right-shifted register offset
ofrprr = Positive right-rotated register offset
prrpll = Left-shifted register offset, pre-increment
prrplr = Right-shifted register offset, pre-increment
prrpar = Arithmetic-right-shifted register offset, pre-increment
prrprr = Right-rotated register offset, pre-increment
ofm = Negative offset
prm = Pre-decrement
ofp = Positive offset
prp = Pre-increment
unm = Unindexed, bits 7-0 available for copro use
ptm = Post-decrement
unp = Unindexed, bits 7-0 available for copro use
ptp = Post-increment
w = Write-Back
u = Use user-mode registers
 */

/* bits 7-4 */
instr_description table_opcode_00[] = {
/* 0x0 */ {0, "AND lli",   AND,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical And"},
/* 0x1 */ {0, "AND llr",   AND,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical And"},
/* 0x2 */ {0, "AND lri",   AND,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical And"},
/* 0x3 */ {0, "AND lrr",   AND,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical And"},
/* 0x4 */ {0, "AND ari",   AND,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical And"},
/* 0x5 */ {0, "AND arr",   AND,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical And"},
/* 0x6 */ {0, "AND rri",   AND,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical And"},
/* 0x7 */ {0, "AND rrr",   AND,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical And"},
/* 0x8 */ {0, "AND lli",   AND,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical And"},
/* 0x9 */ {0, "MUL",       MUL,  NONE, "action_copy", "Multiply registers"},
/* 0xa */ {0, "AND lri",   AND,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical And"},
/* 0xb */ {0, "STRH ptrm", STRH, OPND_REG_OFFSET, "action_copy", "Store halfword"},
/* 0xc */ {0, "AND ari",   AND,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical And"},
/* 0xd */ {0, "LDRD ptrm", LDRD, OPND_REG_OFFSET, "action_copy", "Load doubleword"},
/* 0xe */ {0, "AND rri",   AND,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical And"},
/* 0xf */ {0, "STRD ptrm", STRD, OPND_REG_OFFSET, "action_copy", "Store doubleword"},
};

/* bits 7-4 */
instr_description table_opcode_01[] = {
/* 0x0 */ {0, "ANDS lli",   ANDS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical And, setting flags"},
/* 0x1 */ {0, "ANDS llr",   ANDS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical And, setting flags"},
/* 0x2 */ {0, "ANDS lri",   ANDS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical And, setting flags"},
/* 0x3 */ {0, "ANDS lrr",   ANDS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical And, setting flags"},
/* 0x4 */ {0, "ANDS ari",   ANDS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical And, setting flags"},
/* 0x5 */ {0, "ANDS arr",   ANDS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical And, setting flags"},
/* 0x6 */ {0, "ANDS rri",   ANDS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical And, setting flags"},
/* 0x7 */ {0, "ANDS rrr",   ANDS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical And, setting flags"},
/* 0x8 */ {0, "ANDS lli",   ANDS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical And, setting flags"},
/* 0x9 */ {0, "MULS",       MULS,  NONE, "action_copy", "Multiply registers, setting flag"},
/* 0xa */ {0, "ANDS lri",   ANDS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical And, setting flags"},
/* 0xb */ {0, "LDRH ptrm",  LDRH,  OPND_REG_OFFSET, "action_copy", "Load halfword"},
/* 0xc */ {0, "ANDS ari",   ANDS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical And, setting flags"},
/* 0xd */ {0, "LDRSB ptrm", LDRSB, OPND_REG_OFFSET, "action_copy", "Load signed byte"},
/* 0xe */ {0, "ANDS rri",   ANDS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical And, setting flags"},
/* 0xf */ {0, "LDRSH ptrm", LDRSH, OPND_REG_OFFSET, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_02[] = {
/* 0x0 */ {0, "EOR lli",   EOR,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Exclusive-or"},
/* 0x1 */ {0, "EOR llr",   EOR,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical Exclusive-or"},
/* 0x2 */ {0, "EOR lri",   EOR,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Exclusive-or"},
/* 0x3 */ {0, "EOR lrr",   EOR,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical Exclusive-or"},
/* 0x4 */ {0, "EOR ari",   EOR,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Exclusive-or"},
/* 0x5 */ {0, "EOR arr",   EOR,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical Exclusive-or"},
/* 0x6 */ {0, "EOR rri",   EOR,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Exclusive-or"},
/* 0x7 */ {0, "EOR rrr",   EOR,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical Exclusive-or"},
/* 0x8 */ {0, "EOR lli",   EOR,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Exclusive-or"},
/* 0x9 */ {0, "MLA aa",    MLA,  NONE, "action_copy", "Multiply and accumulate registers"},
/* 0xa */ {0, "EOR lri",   EOR,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Exclusive-or"},
/* 0xb */ {0, "STRH ptrm", STRH, OPND_REG_OFFSET | OPND_WRITE_BACK, "action_copy", "Store halfword"},
/* 0xc */ {0, "EOR ari",   EOR,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Exclusive-or"},
/* 0xd */ {0, "LDRD ptrm", LDRD, OPND_REG_OFFSET | OPND_WRITE_BACK, "action_copy", "Load doubleword"},
/* 0xe */ {0, "EOR rri",   EOR,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Exclusive-or"},
/* 0xf */ {0, "STRD ptrm", STRD, OPND_REG_OFFSET | OPND_WRITE_BACK, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_03[] = {
/* 0x0 */ {0, "EORS lli",   EORS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x1 */ {0, "EORS llr",   EORS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x2 */ {0, "EORS lri",   EORS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x3 */ {0, "EORS lrr",   EORS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x4 */ {0, "EORS ari",   EORS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x5 */ {0, "EORS arr",   EORS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x6 */ {0, "EORS rri",   EORS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x7 */ {0, "EORS rrr",   EORS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x8 */ {0, "EORS lli",   EORS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x9 */ {0, "MLAS",       MLAS,  NONE, "action_copy", "Multiply and accumulate registers, setting flags"},
/* 0xa */ {0, "EORS lri",   EORS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0xb */ {0, "LDRH ptrm",  LDRH,  OPND_REG_OFFSET | OPND_WRITE_BACK, "action_copy", "Load halfword"},
/* 0xc */ {0, "EORS ari",   EORS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0xd */ {0, "LDRSB ptrm", LDRSB, OPND_REG_OFFSET | OPND_WRITE_BACK, "action_copy", "Load signed byte"},
/* 0xe */ {0, "EORS rri",   EORS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0xf */ {0, "LDRSH ptrm", LDRSH, OPND_REG_OFFSET | OPND_WRITE_BACK, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_04[] = {
/* 0x0 */ {0, "SUB lli",   SUB,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register"},
/* 0x1 */ {0, "SUB llr",   SUB,  OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract from register"},
/* 0x2 */ {0, "SUB lri",   SUB,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register"},
/* 0x3 */ {0, "SUB lrr",   SUB,  OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract from register"},
/* 0x4 */ {0, "SUB ari",   SUB,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register"},
/* 0x5 */ {0, "SUB arr",   SUB,  OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract from register"},
/* 0x6 */ {0, "SUB rri",   SUB,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register"},
/* 0x7 */ {0, "SUB rrr",   SUB,  OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract from register"},
/* 0x8 */ {0, "SUB lli",   SUB,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register"},
/* 0x9 */ {0, "",          NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "SUB lri",   SUB,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register"},
/* 0xb */ {0, "STRH ptim", STRH, OPND_IMM_OFFSET, "action_copy", "Store halfword"},
/* 0xc */ {0, "SUB ari",   SUB,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register"},
/* 0xd */ {0, "LDRD ptim", LDRD, OPND_IMM_OFFSET, "action_copy", "Load doubleword"},
/* 0xe */ {0, "SUB rri",   SUB,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register"},
/* 0xf */ {0, "STRD ptim", STRD, OPND_IMM_OFFSET, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_05[] = {
/* 0x0 */ {0, "SUBS lli",   SUBS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract, setting flags"},
/* 0x1 */ {0, "SUBS llr",   SUBS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract, setting flags"},
/* 0x2 */ {0, "SUBS lri",   SUBS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract, setting flags"},
/* 0x3 */ {0, "SUBS lrr",   SUBS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract, setting flags"},
/* 0x4 */ {0, "SUBS ari",   SUBS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract, setting flags"},
/* 0x5 */ {0, "SUBS arr",   SUBS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract, setting flags"},
/* 0x6 */ {0, "SUBS rri",   SUBS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract, setting flags"},
/* 0x7 */ {0, "SUBS rrr",   SUBS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract, setting flags"},
/* 0x8 */ {0, "SUBS lli",   SUBS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract, setting flags"},
/* 0x9 */ {0, "",           NONE,  NONE, "", "UNDEFINED"},
/* 0xa */ {0, "SUBS lri",   SUBS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract, setting flags"},
/* 0xb */ {0, "LDRH ptim",  LDRH,  OPND_IMM_OFFSET, "action_copy", "Load halfword"},
/* 0xc */ {0, "SUBS ari",   SUBS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract, setting flags"},
/* 0xd */ {0, "LDRSB ptim", LDRSB, OPND_IMM_OFFSET, "action_copy", "Load signed byte"},
/* 0xe */ {0, "SUBS rri",   SUBS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract, setting flags"},
/* 0xf */ {0, "LDRSH ptim", LDRSH, OPND_IMM_OFFSET, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_06[] = {
/* 0x0 */ {0, "RSB lli",   RSB,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value"},
/* 0x1 */ {0, "RSB llr",   RSB,  OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract register from value"},
/* 0x2 */ {0, "RSB lri",   RSB,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value"},
/* 0x3 */ {0, "RSB lrr",   RSB,  OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract register from value"},
/* 0x4 */ {0, "RSB ari",   RSB,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value"},
/* 0x5 */ {0, "RSB arr",   RSB,  OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract register from value"},
/* 0x6 */ {0, "RSB rri",   RSB,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value"},
/* 0x7 */ {0, "RSB rrr",   RSB,  OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract register from value"},
/* 0x8 */ {0, "RSB lli",   RSB,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value"},
/* 0x9 */ {0, "",          NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "RSB lri",   RSB,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value"},
/* 0xb */ {0, "STRH ptim", STRH, OPND_IMM_OFFSET | OPND_WRITE_BACK, "action_copy", "Store halfword"},
/* 0xc */ {0, "RSB ari",   RSB,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value"},
/* 0xd */ {0, "LDRD ptim", LDRD, OPND_IMM_OFFSET | OPND_WRITE_BACK, "action_copy", "Load doubleword"},
/* 0xe */ {0, "RSB rri",   RSB,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value"},
/* 0xf */ {0, "STRD ptim", STRD, OPND_IMM_OFFSET | OPND_WRITE_BACK, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_07[] = {
/* 0x0 */ {0, "RSBS lli",   RSBS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Reverse Subtract, setting flags"},
/* 0x1 */ {0, "RSBS llr",   RSBS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Reverse Subtract, setting flags"},
/* 0x2 */ {0, "RSBS lri",   RSBS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Reverse Subtract, setting flags"},
/* 0x3 */ {0, "RSBS lrr",   RSBS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Reverse Subtract, setting flags"},
/* 0x4 */ {0, "RSBS ari",   RSBS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Reverse Subtract, setting flags"},
/* 0x5 */ {0, "RSBS arr",   RSBS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Reverse Subtract, setting flags"},
/* 0x6 */ {0, "RSBS rri",   RSBS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Reverse Subtract, setting flags"},
/* 0x7 */ {0, "RSBS rrr",   RSBS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Reverse Subtract, setting flags"},
/* 0x8 */ {0, "RSBS lli",   RSBS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Reverse Subtract, setting flags"},
/* 0x9 */ {0, "",           NONE,  NONE, "", "UNDEFINED"},
/* 0xa */ {0, "RSBS lri",   RSBS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Reverse Subtract, setting flags"},
/* 0xb */ {0, "LDRH ptim",  LDRH,  OPND_IMM_OFFSET | OPND_WRITE_BACK, "action_copy", "Load halfword"},
/* 0xc */ {0, "RSBS ari",   RSBS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Reverse Subtract, setting flags"},
/* 0xd */ {0, "LDRSB ptim", LDRSB, OPND_IMM_OFFSET | OPND_WRITE_BACK, "action_copy", "Load signed byte"},
/* 0xe */ {0, "RSBS rri",   RSBS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Reverse Subtract, setting flags"},
/* 0xf */ {0, "LDRSH ptim", LDRSH, OPND_IMM_OFFSET | OPND_WRITE_BACK, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_08[] = {
/* 0x0 */ {0, "ADD lli",   ADD,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register"},
/* 0x1 */ {0, "ADD llr",   ADD,   OPND_REG_SHIFT_BY_REG, "action_copy", "Add to register"},
/* 0x2 */ {0, "ADD lri",   ADD,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register"},
/* 0x3 */ {0, "ADD lrr",   ADD,   OPND_REG_SHIFT_BY_REG, "action_copy", "Add to register"},
/* 0x4 */ {0, "ADD ari",   ADD,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register"},
/* 0x5 */ {0, "ADD arr",   ADD,   OPND_REG_SHIFT_BY_REG, "action_copy", "Add to register"},
/* 0x6 */ {0, "ADD rri",   ADD,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register"},
/* 0x7 */ {0, "ADD rrr",   ADD,   OPND_REG_SHIFT_BY_REG, "action_copy", "Add to register"},
/* 0x8 */ {0, "ADD lli",   ADD,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register"},
/* 0x9 */ {0, "UMULL",     UMULL, NONE, "action_copy", "Unsigned long multiply (32x32 to 64)"},
/* 0xa */ {0, "ADD lri",   ADD,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register"},
/* 0xb */ {0, "STRH ptrp", STRH,  OPND_REG_OFFSET | OPND_INCR_OFFSET, "action_copy", "Store halfword"},
/* 0xc */ {0, "ADD ari",   ADD,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register"},
/* 0xd */ {0, "LDRD ptrp", LDRD,  OPND_REG_OFFSET | OPND_INCR_OFFSET, "action_copy", "Load doubleword"},
/* 0xe */ {0, "ADD rri",   ADD,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register"},
/* 0xf */ {0, "STRD ptrp", STRD,  OPND_REG_OFFSET | OPND_INCR_OFFSET, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_09[] = {
/* 0x0 */ {0, "ADDS lli",   ADDS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register, setting flags"},
/* 0x1 */ {0, "ADDS llr",   ADDS,   OPND_REG_SHIFT_BY_REG, "action_copy", "Add to register, setting flags"},
/* 0x2 */ {0, "ADDS lri",   ADDS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register, setting flags"},
/* 0x3 */ {0, "ADDS lrr",   ADDS,   OPND_REG_SHIFT_BY_REG, "action_copy", "Add to register, setting flags"},
/* 0x4 */ {0, "ADDS ari",   ADDS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register, setting flags"},
/* 0x5 */ {0, "ADDS arr",   ADDS,   OPND_REG_SHIFT_BY_REG, "action_copy", "Add to register, setting flags"},
/* 0x6 */ {0, "ADDS rri",   ADDS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register, setting flags"},
/* 0x7 */ {0, "ADDS rrr",   ADDS,   OPND_REG_SHIFT_BY_REG, "action_copy", "Add to register, setting flags"},
/* 0x8 */ {0, "ADDS lli",   ADDS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register, setting flags"},
/* 0x9 */ {0, "UMULLS",     UMULLS, NONE, "action_copy", "Unsigned long multiply, setting flags"},
/* 0xa */ {0, "ADDS lri",   ADDS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register, setting flags"},
/* 0xb */ {0, "LDRH ptrp",  LDRH,   OPND_REG_OFFSET | OPND_INCR_OFFSET, "action_copy", "Load halfword"},
/* 0xc */ {0, "ADDS ari",   ADDS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register, setting flags"},
/* 0xd */ {0, "LDRSB ptrp", LDRSB,  OPND_REG_OFFSET | OPND_INCR_OFFSET, "action_copy", "Load signed byte"},
/* 0xe */ {0, "ADDS rri",   ADDS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register, setting flags"},
/* 0xf */ {0, "LDRSH ptrp", LDRSH,  OPND_REG_OFFSET | OPND_INCR_OFFSET, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_0a[] = {
/* 0x0 */ {0, "ADC lli",   ADC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register with carry"},
/* 0x1 */ {0, "ADC llr",   ADC,   OPND_REG_SHIFT_BY_REG, "action_copy", "Add to register with carry"},
/* 0x2 */ {0, "ADC lri",   ADC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register with carry"},
/* 0x3 */ {0, "ADC lrr",   ADC,   OPND_REG_SHIFT_BY_REG, "action_copy", "Add to register with carry"},
/* 0x4 */ {0, "ADC ari",   ADC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register with carry"},
/* 0x5 */ {0, "ADC arr",   ADC,   OPND_REG_SHIFT_BY_REG, "action_copy", "Add to register with carry"},
/* 0x6 */ {0, "ADC rri",   ADC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register with carry"},
/* 0x7 */ {0, "ADC rrr",   ADC,   OPND_REG_SHIFT_BY_REG, "action_copy", "Add to register with carry"},
/* 0x8 */ {0, "ADC lli",   ADC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register with carry"},
/* 0x9 */ {0, "UMLAL",     UMLAL, NONE, "action_copy", "Unsigned long multiply and accumulate"},
/* 0xa */ {0, "ADC lri",   ADC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register with carry"},
/* 0xb */ {0, "STRH ptrp", STRH,  OPND_REG_OFFSET | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store halfword"},
/* 0xc */ {0, "ADC ari",   ADC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register with carry"},
/* 0xd */ {0, "LDRD ptrp", LDRD,  OPND_REG_OFFSET | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load doubleword"},
/* 0xe */ {0, "ADC rri",   ADC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register with carry"},
/* 0xf */ {0, "STRD ptrp", STRD,  OPND_REG_OFFSET | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_0b[] = {
/* 0x0 */ {0, "ADCS lli",   ADCS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register with carry, setting flags"},
/* 0x1 */ {0, "ADCS llr",   ADCS,   OPND_REG_SHIFT_BY_REG, "action_copy", "Add to register with carry, setting flags"},
/* 0x2 */ {0, "ADCS lri",   ADCS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register with carry, setting flags"},
/* 0x3 */ {0, "ADCS lrr",   ADCS,   OPND_REG_SHIFT_BY_REG, "action_copy", "Add to register with carry, setting flags"},
/* 0x4 */ {0, "ADCS ari",   ADCS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register with carry, setting flags"},
/* 0x5 */ {0, "ADCS arr",   ADCS,   OPND_REG_SHIFT_BY_REG, "action_copy", "Add to register with carry, setting flags"},
/* 0x6 */ {0, "ADCS rri",   ADCS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register with carry, setting flags"},
/* 0x7 */ {0, "ADCS rrr",   ADCS,   OPND_REG_SHIFT_BY_REG, "action_copy", "Add to register with carry, setting flags"},
/* 0x8 */ {0, "ADCS lli",   ADCS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register with carry, setting flags"},
/* 0x9 */ {0, "UMLALS",     UMLALS, NONE, "action_copy", "Unsigned long multiply and accumulate, setting flags"},
/* 0xa */ {0, "ADCS lri",   ADCS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register with carry, setting flags"},
/* 0xb */ {0, "LDRH ptrp",  LDRH,   OPND_REG_OFFSET | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load halfword"},
/* 0xc */ {0, "ADCS ari",   ADCS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register with carry, setting flags"},
/* 0xd */ {0, "LDRSB ptrp", LDRSB,  OPND_REG_OFFSET | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load signed byte"},
/* 0xe */ {0, "ADCS rri",   ADCS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Add to register with carry, setting flags"},
/* 0xf */ {0, "LDRSH ptrp", LDRSH,  OPND_REG_OFFSET | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_0c[] = {
/* 0x0 */ {0, "SBC lli",   SBC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register with borrow"},
/* 0x1 */ {0, "SBC llr",   SBC,   OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract from register with borrow"},
/* 0x2 */ {0, "SBC lri",   SBC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register with borrow"},
/* 0x3 */ {0, "SBC lrr",   SBC,   OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract from register with borrow"},
/* 0x4 */ {0, "SBC ari",   SBC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register with borrow"},
/* 0x5 */ {0, "SBC arr",   SBC,   OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract from register with borrow"},
/* 0x6 */ {0, "SBC rri",   SBC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register with borrow"},
/* 0x7 */ {0, "SBC rrr",   SBC,   OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract from register with borrow"},
/* 0x8 */ {0, "SBC lli",   SBC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register with borrow"},
/* 0x9 */ {0, "SMULL",     SMULL, NONE, "action_copy", "Signed long multiply (32x32 to 64)"},
/* 0xa */ {0, "SBC lri",   SBC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register with borrow"},
/* 0xb */ {0, "STRH ptip", STRH,  OPND_IMM_OFFSET | OPND_INCR_OFFSET, "action_copy", "Store halfword"},
/* 0xc */ {0, "SBC ari",   SBC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register with borrow"},
/* 0xd */ {0, "LDRD ptip", LDRD,  OPND_IMM_OFFSET | OPND_INCR_OFFSET, "action_copy", "Load doubleword"},
/* 0xe */ {0, "SBC rri",   SBC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register with borrow"},
/* 0xf */ {0, "STRD ptip", STRD,  OPND_IMM_OFFSET | OPND_INCR_OFFSET, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_0d[] = {
/* 0x0 */ {0, "SBCS lli",   SBCS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x1 */ {0, "SBCS llr",   SBCS,   OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x2 */ {0, "SBCS lri",   SBCS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x3 */ {0, "SBCS lrr",   SBCS,   OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x4 */ {0, "SBCS ari",   SBCS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x5 */ {0, "SBCS arr",   SBCS,   OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x6 */ {0, "SBCS rri",   SBCS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x7 */ {0, "SBCS rrr",   SBCS,   OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x8 */ {0, "SBCS lli",   SBCS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x9 */ {0, "SMULLS",     SMULLS, NONE, "action_copy", "Signed long multiply, setting flags"},
/* 0xa */ {0, "SBCS lri",   SBCS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0xb */ {0, "LDRH ptip",  LDRH,   OPND_IMM_OFFSET | OPND_INCR_OFFSET, "action_copy", "Load halfword"},
/* 0xc */ {0, "SBCS ari",   SBCS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0xd */ {0, "LDRSB ptip", LDRSB,  OPND_IMM_OFFSET | OPND_INCR_OFFSET, "action_copy", "Load signed byte"},
/* 0xe */ {0, "SBCS rri",   SBCS,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0xf */ {0, "LDRSH ptip", LDRSH,  OPND_IMM_OFFSET | OPND_INCR_OFFSET, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_0e[] = {
/* 0x0 */ {0, "RSC lli",   RSC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value with borrow"},
/* 0x1 */ {0, "RSC llr",   RSC,   OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract register from value with borrow"},
/* 0x2 */ {0, "RSC lri",   RSC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value with borrow"},
/* 0x3 */ {0, "RSC lrr",   RSC,   OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract register from value with borrow"},
/* 0x4 */ {0, "RSC ari",   RSC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value with borrow"},
/* 0x5 */ {0, "RSC arr",   RSC,   OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract register from value with borrow"},
/* 0x6 */ {0, "RSC rri",   RSC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value with borrow"},
/* 0x7 */ {0, "RSC rrr",   RSC,   OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract register from value with borrow"},
/* 0x8 */ {0, "RSC lli",   RSC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value with borrow"},
/* 0x9 */ {0, "SMLAL",     SMLAL, NONE, "action_copy", "Signed long multiply and accumulate"},
/* 0xa */ {0, "RSC lri",   RSC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value with borrow"},
/* 0xb */ {0, "STRH ptip", STRH,  OPND_IMM_OFFSET | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store halfword"},
/* 0xc */ {0, "RSC ari",   RSC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value with borrow"},
/* 0xd */ {0, "LDRD ptip", LDRD,  OPND_IMM_OFFSET | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load doubleword"},
/* 0xe */ {0, "RSC rri",   RSC,   OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value with borrow"},
/* 0xf */ {0, "STRD ptip", STRD,  OPND_IMM_OFFSET | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_0f[] = {
/* 0x0 */ {0, "RSCS lli",   RSCS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x1 */ {0, "RSCS llr",   RSCS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x2 */ {0, "RSCS lri",   RSCS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x3 */ {0, "RSCS lrr",   RSCS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x4 */ {0, "RSCS ari",   RSCS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x5 */ {0, "RSCS arr",   RSCS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x6 */ {0, "RSCS rri",   RSCS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x7 */ {0, "RSCS rrr",   RSCS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x8 */ {0, "RSCS lli",   RSCS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x9 */ {0, "SMLALS",     NONE,  NONE, "action_copy", "Signed long multiply and ultiply , setting flags"},
/* 0xa */ {0, "RSCS lri",   RSCS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0xb */ {0, "LDRH ptip",  LDRH,  OPND_IMM_OFFSET | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load halfword"},
/* 0xc */ {0, "RSCS ari",   RSCS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0xd */ {0, "LDRSB ptip", LDRSB, OPND_IMM_OFFSET | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load signed byte"},
/* 0xe */ {0, "RSCS rri",   RSCS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0xf */ {0, "LDRSH ptip", LDRSH, OPND_IMM_OFFSET | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_10[] = {
/* 0x0 */ {0, "MRS rc",    MRS,    NONE, "action_copy", "Move status word to register"},
/* 0x1 */ {0, "",          NONE,   NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "",          NONE,   NONE, "", "UNDEFINED"},
/* 0x3 */ {0, "",          NONE,   NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "",          NONE,   NONE, "", "UNDEFINED"},
/* 0x5 */ {0, "QADD",      QADD,   NONE, "action_copy", "Saturated add"},
/* 0x6 */ {0, "",          NONE,   NONE, "", "UNDEFINED"},
/* 0x7 */ {0, "",          NONE,   NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "SMLABB",    SMLABB, NONE, "action_copy", "Signed multiply bottom-half of first operand with bottom-half of second, and accumulate"},
/* 0x9 */ {0, "SWP",       SWP,    NONE, "action_copy", "Swap registers with memory word"},
/* 0xa */ {0, "SMLATB",    SMLATB, NONE, "action_copy", "Signed multiply top-half of first operand with bottom-half of second, and accumulate"},
/* 0xb */ {0, "STRH ofrm", STRH,   OPND_PRE_INDEX, "action_copy", "Store halfword"},
/* 0xc */ {0, "SMLABT",    SMLABT, NONE, "action_copy", "Signed multiply bottom-half of first operand with top-half of second, and accumulate"},
/* 0xd */ {0, "LDRD ofrm", LDRD,   OPND_PRE_INDEX, "action_copy", "Load doubleword"},
/* 0xe */ {0, "SMLATT",    SMLATT, NONE, "action_copy", "Signed multiply top-half of first operand with top-half of second, and accumulate"},
/* 0xf */ {0, "STRD ofrm", STRD,   OPND_PRE_INDEX, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_11[] = {
/* 0x0 */ {0, "TST lli",    TSTS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x1 */ {0, "TST llr",    TSTS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x2 */ {0, "TST lri",    TSTS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x3 */ {0, "TST lrr",    TSTS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x4 */ {0, "TST ari",    TSTS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x5 */ {0, "TST arr",    TSTS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x6 */ {0, "TST rri",    TSTS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x7 */ {0, "TST rrr",    TSTS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x8 */ {0, "TST lli",    TSTS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x9 */ {0, "",           NONE,  NONE, "", "UNDEFINED"},
/* 0xa */ {0, "TST lri",    TSTS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0xb */ {0, "LDRH ofrm",  LDRH,  OPND_PRE_INDEX, "action_copy", "Load halfword"},
/* 0xc */ {0, "TST ari",    TSTS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0xd */ {0, "LDRSB ofrm", LDRSB, OPND_PRE_INDEX, "action_copy", "Load signed byte"},
/* 0xe */ {0, "TST rri",    TSTS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0xf */ {0, "LDRSH ofrm", LDRSH, OPND_PRE_INDEX, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_12[] = {
/* 0x0 */ {0, "MSR rc",    MSR,    NONE, "action_copy", "Move value to status word"},
/* 0x1 */ {0, "BX reg",    BX,     NONE, "action_copy", "Branch and switch execution modes"},
/* 0x2 */ {0, "",          NONE,   NONE, "", "UNDEFINED"},
/* 0x3 */ {0, "BLX reg",   BLX,    NONE, "action_copy", "Branch, link and switch execution modes"},
/* 0x4 */ {0, "",          NONE,   NONE, "", "UNDEFINED"},
/* 0x5 */ {0, "QSUB",      QSUB,   NONE, "action_copy", "Saturated subtract"},
/* 0x6 */ {0, "",          NONE,   NONE, "", "UNDEFINED"},
/* 0x7 */ {0, "BKPT",      BKPT,   NONE, "action_copy", "Software breakpoint"},
/* 0x8 */ {0, "SMLAWB",    SMLAWB, NONE, "action_copy", "Signed multiply first operand with bottom-half of second operand, keeping top 32 bits, and accumulate"},
/* 0x9 */ {0, "",          NONE,   NONE, "", "UNDEFINED"},
/* 0xa */ {0, "SMULWB",    SMULWB, NONE, "action_copy", "Signed multiply first operand with bottom-half of second operand, keeping top 32 bits"},
/* 0xb */ {0, "STRH prrm", STRH,   OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store halfword"},
/* 0xc */ {0, "SMLAWT",    SMLAWT, NONE, "action_copy", "Signed multiply first operand with top-half of second operand, keeping top 32 bits, and accumulate"},
/* 0xd */ {0, "LDRD prrm", LDRD,   OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load doubleword"},
/* 0xe */ {0, "SMULWT",    SMULWT, NONE, "action_copy", "Signed multiply first operand with top-half of second operand, keeping top 32 bits"},
/* 0xf */ {0, "STRD prrm", STRD,   OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_13[] = {
/* 0x0 */ {0, "TEQ lli",    TEQS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x1 */ {0, "TEQ llr",    TEQS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x2 */ {0, "TEQ lri",    TEQS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x3 */ {0, "TEQ lrr",    TEQS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x4 */ {0, "TEQ ari",    TEQS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x5 */ {0, "TEQ arr",    TEQS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x6 */ {0, "TEQ rri",    TEQS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x7 */ {0, "TEQ rrr",    TEQS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x8 */ {0, "TEQ lli",    TEQS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x9 */ {0, "",           NONE,  NONE, "", "UNDEFINED"},
/* 0xa */ {0, "TEQ lri",    TEQS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0xb */ {0, "LDRH prrm",  LDRH,  OPND_PRE_INDEX  | OPND_WRITE_BACK, "action_copy", "Load halfword"},
/* 0xc */ {0, "TEQ ari",    TEQS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0xd */ {0, "LDRSB prrm", LDRSB, OPND_PRE_INDEX  | OPND_WRITE_BACK, "action_copy", "Load signed byte"},
/* 0xe */ {0, "TEQ rri",    TEQS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0xf */ {0, "LDRSH prrm", LDRSH, OPND_PRE_INDEX  | OPND_WRITE_BACK, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_14[] = {
/* 0x0 */ {0, "MRS rs",    MRS,     NONE, "action_copy", "Move status word to register"},
/* 0x1 */ {0, "",          NONE,    NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "",          NONE,    NONE, "", "UNDEFINED"},
/* 0x3 */ {0, "",          NONE,    NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "",          NONE,    NONE, "", "UNDEFINED"},
/* 0x5 */ {0, "QDADD",     QDADD,   NONE, "action_copy", "Saturated add with doubling of second operand"},
/* 0x6 */ {0, "",          NONE,    NONE, "", "UNDEFINED"},
/* 0x7 */ {0, "",          NONE,    NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "SMLALBB",   SMLALBB, NONE, "action_copy", "Signed multiply bottom-half of first operand with bottom-half of second, and 64-bit accumulate"},
/* 0x9 */ {0, "SWPB",      SWPB,    NONE, "action_copy", "Swap registers with memory byte"},
/* 0xa */ {0, "SMLALTB",   SMLALTB, NONE, "action_copy", "Signed multiply top-half of first operand with bottom-half of second, and 64-bit accumulate"},
/* 0xb */ {0, "STRH ofim", STRH,    OPND_IMM_OFFSET | OPND_PRE_INDEX, "action_copy", "Store halfword"},
/* 0xc */ {0, "SMLALBT",   SMLALBT, NONE, "action_copy", "Signed multiply bottom-half of first operand with top-half of second, and 64-bit accumulate"},
/* 0xd */ {0, "LDRD ofim", LDRD,    OPND_IMM_OFFSET | OPND_PRE_INDEX, "action_copy", "Load doubleword"},
/* 0xe */ {0, "SMLALTT",   SMLALTT, NONE, "action_copy", "Signed multiply top-half of first operand with top-half of second, and 64-bit accumulate"},
/* 0xf */ {0, "STRD ofim", STRD,    OPND_IMM_OFFSET | OPND_PRE_INDEX, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_15[] = {
/* 0x0 */ {0, "CMP lli",    CMPS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x1 */ {0, "CMP llr",    CMPS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x2 */ {0, "CMP lri",    CMPS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x3 */ {0, "CMP lrr",    CMPS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x4 */ {0, "CMP ari",    CMPS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x5 */ {0, "CMP arr",    CMPS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x6 */ {0, "CMP rri",    CMPS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x7 */ {0, "CMP rrr",    CMPS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x8 */ {0, "CMP lli",    CMPS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x9 */ {0, "",           NONE,  NONE, "", "UNDEFINED"},
/* 0xa */ {0, "CMP lri",    CMPS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0xb */ {0, "LDRH ofim",  LDRH,  OPND_IMM_OFFSET | OPND_PRE_INDEX, "action_copy", "Load halfword"},
/* 0xc */ {0, "CMP ari",    CMPS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0xd */ {0, "LDRSB ofim", LDRSB, OPND_IMM_OFFSET | OPND_PRE_INDEX, "action_copy", "Load signed byte"},
/* 0xe */ {0, "CMP rri",    CMPS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0xf */ {0, "LDRSH ofim", LDRSH, OPND_IMM_OFFSET | OPND_PRE_INDEX, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_16[] = {
/* 0x0 */ {0, "MSR rs",    MSR,    NONE, "action_copy", "Move value to status word"},
/* 0x1 */ {0, "CLZ",       CLZ,    NONE, "action_copy", "Count leading zeros in register"},
/* 0x2 */ {0, "",          NONE,   NONE, "", "UNDEFINED"},
/* 0x3 */ {0, "",          NONE,   NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "",          NONE,   NONE, "", "UNDEFINED"},
/* 0x5 */ {0, "QDSUB",     QDSUB,  NONE, "action_copy", "Saturated subtract with doubling of second operand"},
/* 0x6 */ {0, "",          NONE,   NONE, "", "UNDEFINED"},
/* 0x7 */ {0, "",          NONE,   NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "SMULBB",    SMULBB, NONE, "action_copy", "Signed multiply bottom-half of first operand with bottom-half of second"},
/* 0x9 */ {0, "",          NONE,   NONE, "", "UNDEFINED"},
/* 0xa */ {0, "SMULTB",    SMULTB, NONE, "action_copy", "Signed multiply top-half of first operand with bottom-half of second"},
/* 0xb */ {0, "STRH prim", STRH,   OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store halfword"},
/* 0xc */ {0, "SMULBT",    SMULBT, NONE, "action_copy", "Signed multiply bottom-half of first operand with top-half of second"},
/* 0xd */ {0, "LDRD prim", LDRD,   OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load doubleword"},
/* 0xe */ {0, "SMULTT",    SMULTT, NONE, "action_copy", "Signed multiply top-half of first operand with top-half of second"},
/* 0xf */ {0, "STRD prim", STRD,   OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store doubleword"},
};

/* bits 7-4 */
instr_description table_opcode_17[] = {
/* 0x0 */ {0, "CMN lli",    CMNS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x1 */ {0, "CMN llr",    CMNS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x2 */ {0, "CMN lri",    CMNS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x3 */ {0, "CMN lrr",    CMNS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x4 */ {0, "CMN ari",    CMNS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x5 */ {0, "CMN arr",    CMNS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x6 */ {0, "CMN rri",    CMNS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x7 */ {0, "CMN rrr",    CMNS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x8 */ {0, "CMN lli",    CMNS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x9 */ {0, "",           NONE,  NONE, "", "UNDEFINED"},
/* 0xa */ {0, "CMN lri",    CMNS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0xb */ {0, "LDRH prim",  LDRH,  OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load halfword"},
/* 0xc */ {0, "CMN ari",    CMNS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0xd */ {0, "LDRSB prim", LDRSB, OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load signed byte"},
/* 0xe */ {0, "CMN rri",    CMNS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0xf */ {0, "LDRSH prim", LDRSH, OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_18[] = {
/* 0x0 */ {0, "ORR lli",   ORR,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Or"},
/* 0x1 */ {0, "ORR llr",   ORR,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical Or"},
/* 0x2 */ {0, "ORR lri",   ORR,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Or"},
/* 0x3 */ {0, "ORR lrr",   ORR,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical Or"},
/* 0x4 */ {0, "ORR ari",   ORR,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Or"},
/* 0x5 */ {0, "ORR arr",   ORR,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical Or"},
/* 0x6 */ {0, "ORR rri",   ORR,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Or"},
/* 0x7 */ {0, "ORR rrr",   ORR,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical Or"},
/* 0x8 */ {0, "ORR lli",   ORR,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Or"},
/* 0x9 */ {0, "",          NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "ORR lri",   ORR,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Or"},
/* 0xb */ {0, "STRH ofrp", STRH, OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store halfword"},
/* 0xc */ {0, "ORR ari",   ORR,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Or"},
/* 0xd */ {0, "LDRD ofrp", LDRD, OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load doubleword"},
/* 0xe */ {0, "ORR rri",   ORR,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Or"},
/* 0xf */ {0, "STRD ofrp", STRD, OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_19[] = {
/* 0x0 */ {0, "ORRS lli",   ORRS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Or, setting flags"},
/* 0x1 */ {0, "ORRS llr",   ORRS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical Or, setting flags"},
/* 0x2 */ {0, "ORRS lri",   ORRS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Or, setting flags"},
/* 0x3 */ {0, "ORRS lrr",   ORRS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical Or, setting flags"},
/* 0x4 */ {0, "ORRS ari",   ORRS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Or, setting flags"},
/* 0x5 */ {0, "ORRS arr",   ORRS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical Or, setting flags"},
/* 0x6 */ {0, "ORRS rri",   ORRS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Or, setting flags"},
/* 0x7 */ {0, "ORRS rrr",   ORRS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Logical Or, setting flags"},
/* 0x8 */ {0, "ORRS lli",   ORRS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Or, setting flags"},
/* 0x9 */ {0, "",           NONE,  NONE, "", "UNDEFINED"},
/* 0xa */ {0, "ORRS lri",   ORRS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Or, setting flags"},
/* 0xb */ {0, "LDRH ofrp",  LDRH,  OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load halfword"},
/* 0xc */ {0, "ORRS ari",   ORRS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Or, setting flags"},
/* 0xd */ {0, "LDRSB ofrp", LDRSB, OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load signed byte"},
/* 0xe */ {0, "ORRS rri",   ORRS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Logical Or, setting flags"},
/* 0xf */ {0, "LDRSH ofrp", LDRSH, OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_1a[] = {
/* 0x0 */ {0, "MOV lli",   MOV,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move value to a register"},
/* 0x1 */ {0, "MOV llr",   MOV,  OPND_REG_SHIFT_BY_REG, "action_copy", "Move value to a register"},
/* 0x2 */ {0, "MOV lri",   MOV,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move value to a register"},
/* 0x3 */ {0, "MOV lrr",   MOV,  OPND_REG_SHIFT_BY_REG, "action_copy", "Move value to a register"},
/* 0x4 */ {0, "MOV ari",   MOV,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move value to a register"},
/* 0x5 */ {0, "MOV arr",   MOV,  OPND_REG_SHIFT_BY_REG, "action_copy", "Move value to a register"},
/* 0x6 */ {0, "MOV rri",   MOV,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move value to a register"},
/* 0x7 */ {0, "MOV rrr",   MOV,  OPND_REG_SHIFT_BY_REG, "action_copy", "Move value to a register"},
/* 0x8 */ {0, "MOV lli",   MOV,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move value to a register"},
/* 0x9 */ {0, "",          NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "MOV lri",   MOV,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move value to a register"},
/* 0xb */ {0, "STRH prrp", STRH, OPND_PRE_INDEX  | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store halfword"},
/* 0xc */ {0, "MOV ari",   MOV,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move value to a register"},
/* 0xd */ {0, "LDRD prrp", LDRD, OPND_PRE_INDEX  | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load doubleword"},
/* 0xe */ {0, "MOV rri",   MOV,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move value to a register"},
/* 0xf */ {0, "STRD prrp", STRD, OPND_PRE_INDEX  | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_1b[] = {
/* 0x0 */ {0, "MOVS lli",   MOVS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move value to a register, setting flags"},
/* 0x1 */ {0, "MOVS llr",   MOVS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Move value to a register, setting flags"},
/* 0x2 */ {0, "MOVS lri",   MOVS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move value to a register, setting flags"},
/* 0x3 */ {0, "MOVS lrr",   MOVS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Move value to a register, setting flags"},
/* 0x4 */ {0, "MOVS ari",   MOVS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move value to a register, setting flags"},
/* 0x5 */ {0, "MOVS arr",   MOVS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Move value to a register, setting flags"},
/* 0x6 */ {0, "MOVS rri",   MOVS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move value to a register, setting flags"},
/* 0x7 */ {0, "MOVS rrr",   MOVS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Move value to a register, setting flags"},
/* 0x8 */ {0, "MOVS lli",   MOVS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move value to a register, setting flags"},
/* 0x9 */ {0, "",           NONE,  NONE, "", "UNDEFINED"},
/* 0xa */ {0, "MOVS lri",   MOVS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move value to a register, setting flags"},
/* 0xb */ {0, "LDRH prrp",  LDRH,  OPND_PRE_INDEX  | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load halfword"},
/* 0xc */ {0, "MOVS ari",   MOVS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move value to a register, setting flags"},
/* 0xd */ {0, "LDRSB prrp", LDRSB, OPND_PRE_INDEX  | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load signed byte"},
/* 0xe */ {0, "MOVS rri",   MOVS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move value to a register, setting flags"},
/* 0xf */ {0, "LDRSH prrp", LDRSH, OPND_PRE_INDEX  | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_1c[] = {
/* 0x0 */ {0, "BIC lli",   BIC,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Clear bits in register (NAND)"},
/* 0x1 */ {0, "BIC llr",   BIC,  OPND_REG_SHIFT_BY_REG, "action_copy", "Clear bits in register (NAND)"},
/* 0x2 */ {0, "BIC lri",   BIC,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Clear bits in register (NAND)"},
/* 0x3 */ {0, "BIC lrr",   BIC,  OPND_REG_SHIFT_BY_REG, "action_copy", "Clear bits in register (NAND)"},
/* 0x4 */ {0, "BIC ari",   BIC,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Clear bits in register (NAND)"},
/* 0x5 */ {0, "BIC arr",   BIC,  OPND_REG_SHIFT_BY_REG, "action_copy", "Clear bits in register (NAND)"},
/* 0x6 */ {0, "BIC rri",   BIC,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Clear bits in register (NAND)"},
/* 0x7 */ {0, "BIC rrr",   BIC,  OPND_REG_SHIFT_BY_REG, "action_copy", "Clear bits in register (NAND)"},
/* 0x8 */ {0, "BIC lli",   BIC,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Clear bits in register (NAND)"},
/* 0x9 */ {0, "",          NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "BIC lri",   BIC,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Clear bits in register (NAND)"},
/* 0xb */ {0, "STRH ofip", STRH, OPND_IMM_OFFSET | OPND_INCR_OFFSET | OPND_PRE_INDEX, "action_copy", "Store halfword"},
/* 0xc */ {0, "BIC ari",   BIC,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Clear bits in register (NAND)"},
/* 0xd */ {0, "LDRD ofip", LDRD, OPND_IMM_OFFSET | OPND_INCR_OFFSET | OPND_PRE_INDEX, "action_copy", "Load doubleword"},
/* 0xe */ {0, "BIC rri",   BIC,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Clear bits in register (NAND)"},
/* 0xf */ {0, "STRD ofip", STRD, OPND_IMM_OFFSET | OPND_INCR_OFFSET | OPND_PRE_INDEX, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_1d[] = {
/* 0x0 */ {0, "BICS lli",   BICS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x1 */ {0, "BICS llr",   BICS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x2 */ {0, "BICS lri",   BICS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x3 */ {0, "BICS lrr",   BICS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x4 */ {0, "BICS ari",   BICS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x5 */ {0, "BICS arr",   BICS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x6 */ {0, "BICS rri",   BICS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x7 */ {0, "BICS rrr",   BICS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x8 */ {0, "BICS lli",   BICS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x9 */ {0, "",           NONE,  NONE, "", "UNDEFINED"},
/* 0xa */ {0, "BICS lri",   BICS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0xb */ {0, "LDRH ofip",  LDRH,  OPND_IMM_OFFSET | OPND_INCR_OFFSET | OPND_PRE_INDEX, "action_copy", "Load halfword"},
/* 0xc */ {0, "BICS ari",   BICS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0xd */ {0, "LDRSB ofip", LDRSB, OPND_IMM_OFFSET | OPND_INCR_OFFSET | OPND_PRE_INDEX, "action_copy", "Load signed byte"},
/* 0xe */ {0, "BICS rri",   BICS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0xf */ {0, "LDRSH ofip", LDRSH, OPND_IMM_OFFSET | OPND_INCR_OFFSET | OPND_PRE_INDEX, "action_copy", "Load signed halfword"}
};

/* bits 7-4 */
instr_description table_opcode_1e[] = {
/* 0x0 */ {0, "MVN lli",   MVN,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move negation of value to a register"},
/* 0x1 */ {0, "MVN llr",   MVN,  OPND_REG_SHIFT_BY_REG, "action_copy", "Move negation of value to a register"},
/* 0x2 */ {0, "MVN lri",   MVN,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move negation of value to a register"},
/* 0x3 */ {0, "MVN lrr",   MVN,  OPND_REG_SHIFT_BY_REG, "action_copy", "Move negation of value to a register"},
/* 0x4 */ {0, "MVN ari",   MVN,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move negation of value to a register"},
/* 0x5 */ {0, "MVN arr",   MVN,  OPND_REG_SHIFT_BY_REG, "action_copy", "Move negation of value to a register"},
/* 0x6 */ {0, "MVN rri",   MVN,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move negation of value to a register"},
/* 0x7 */ {0, "MVN rrr",   MVN,  OPND_REG_SHIFT_BY_REG, "action_copy", "Move negation of value to a register"},
/* 0x8 */ {0, "MVN lli",   MVN,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move negation of value to a register"},
/* 0x9 */ {0, "",          NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "MVN lri",   MVN,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move negation of value to a register"},
/* 0xb */ {0, "STRH prip", STRH, OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store halfword"},
/* 0xc */ {0, "MVN ari",   MVN,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move negation of value to a register"},
/* 0xd */ {0, "LDRD prip", LDRD, OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load doubleword"},
/* 0xe */ {0, "MVN rri",   MVN,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move negation of value to a register"},
/* 0xf */ {0, "STRD prip", STRD, OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store doubleword"}
};

/* bits 7-4 */
instr_description table_opcode_1f[] = {
/* 0x0 */ {0, "MVNS lli",   MVNS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x1 */ {0, "MVNS llr",   MVNS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x2 */ {0, "MVNS lri",   MVNS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x3 */ {0, "MVNS lrr",   MVNS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x4 */ {0, "MVNS ari",   MVNS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x5 */ {0, "MVNS arr",   MVNS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x6 */ {0, "MVNS rri",   MVNS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x7 */ {0, "MVNS rrr",   MVNS,  OPND_REG_SHIFT_BY_REG, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x8 */ {0, "MVNS lli",   MVNS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x9 */ {0, "",           NONE,  NONE, "", "UNDEFINED"},
/* 0xa */ {0, "MVNS lri",   MVNS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move negation of value to a register, setting flags"},
/* 0xb */ {0, "LDRH prip",  LDRH,  OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load halfword"},
/* 0xc */ {0, "MVNS ari",   MVNS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move negation of value to a register, setting flags"},
/* 0xd */ {0, "LDRSB prip", LDRSB, OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load signed byte"},
/* 0xe */ {0, "MVNS rri",   MVNS,  OPND_REG_SHIFT_BY_IMM, "action_copy", "Move negation of value to a register, setting flags"},
/* 0xf */ {0, "LDRSH prip", LDRSH, OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load signed halfword"}
};

/* gap */

/* bits 7-4 */
instr_description table_opcode_60[] = {
/* 0x0 */ {0, "STR ptrmll", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Store word"},
/* 0x1 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STR ptrmlr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Store word"},
/* 0x3 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STR ptrmar", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Store word"},
/* 0x5 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STR ptrmrr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Store word"},
/* 0x7 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STR ptrmll", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Store word"},
/* 0x9 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STR ptrmlr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Store word"},
/* 0xb */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STR ptrmar", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Store word"},
/* 0xd */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STR ptrmrr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Store word"},
/* 0xf */ {0, "",           NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_61[] = {
/* 0x0 */ {0, "LDR ptrmll", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Load word"},
/* 0x1 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDR ptrmlr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Load word"},
/* 0x3 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDR ptrmar", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Load word"},
/* 0x5 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDR ptrmrr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Load word"},
/* 0x7 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDR ptrmll", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Load word"},
/* 0x9 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDR ptrmlr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Load word"},
/* 0xb */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDR ptrmar", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Load word"},
/* 0xd */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDR ptrmrr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Load word"},
/* 0xf */ {0, "",           NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_62[] = {
/* 0x0 */ {0, "STRT ptrmll", STRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Store word from user-mode register"},
/* 0x1 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRT ptrmlr", STRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Store word from user-mode register"},
/* 0x3 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRT ptrmar", STRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Store word from user-mode register"},
/* 0x5 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRT ptrmrr", STRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Store word from user-mode register"},
/* 0x7 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRT ptrmll", STRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Store word from user-mode register"},
/* 0x9 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRT ptrmlr", STRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Store word from user-mode register"},
/* 0xb */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRT ptrmar", STRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Store word from user-mode register"},
/* 0xd */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRT ptrmrr", STRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Store word from user-mode register"},
/* 0xf */ {0, "",            NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_63[] = {
/* 0x0 */ {0, "LDRT ptrmll", LDRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Load word into user-mode register"},
/* 0x1 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRT ptrmlr", LDRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Load word into user-mode register"},
/* 0x3 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRT ptrmar", LDRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Load word into user-mode register"},
/* 0x5 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRT ptrmrr", LDRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Load word into user-mode register"},
/* 0x7 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRT ptrmll", LDRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Load word into user-mode register"},
/* 0x9 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRT ptrmlr", LDRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Load word into user-mode register"},
/* 0xb */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRT ptrmar", LDRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Load word into user-mode register"},
/* 0xd */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRT ptrmrr", LDRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Load word into user-mode register"},
/* 0xf */ {0, "",            NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_64[] = {
/* 0x0 */ {0, "STRB ptrmll", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Store byte"},
/* 0x1 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRB ptrmlr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Store byte"},
/* 0x3 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRB ptrmar", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Store byte"},
/* 0x5 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRB ptrmrr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Store byte"},
/* 0x7 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRB ptrmll", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Store byte"},
/* 0x9 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRB ptrmlr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Store byte"},
/* 0xb */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRB ptrmar", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Store byte"},
/* 0xd */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRB ptrmrr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Store byte"},
/* 0xf */ {0, "",            NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_65[] = {
/* 0x0 */ {0, "LDRB ptrmll", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Load byte"},
/* 0x1 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRB ptrmlr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Load byte"},
/* 0x3 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRB ptrmar", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Load byte"},
/* 0x5 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRB ptrmrr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Load byte"},
/* 0x7 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRB ptrmll", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Load byte"},
/* 0x9 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRB ptrmlr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Load byte"},
/* 0xb */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRB ptrmar", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Load byte"},
/* 0xd */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRB ptrmrr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM, "action_copy", "Load byte"},
/* 0xf */ {0, "",            NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_66[] = {
/* 0x0 */ {0, "STRBT ptrmll", STRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Store byte from user-mode register"},
/* 0x1 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRBT ptrmlr", STRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Store byte from user-mode register"},
/* 0x3 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRBT ptrmar", STRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Store byte from user-mode register"},
/* 0x5 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRBT ptrmrr", STRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Store byte from user-mode register"},
/* 0x7 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRBT ptrmll", STRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Store byte from user-mode register"},
/* 0x9 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRBT ptrmlr", STRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Store byte from user-mode register"},
/* 0xb */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRBT ptrmar", STRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Store byte from user-mode register"},
/* 0xd */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRBT ptrmrr", STRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Store byte from user-mode register"},
/* 0xf */ {0, "",             NONE,  NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_67[] = {
/* 0x0 */ {0, "LDRBT ptrmll", LDRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Load byte into user-mode register"},
/* 0x1 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRBT ptrmlr", LDRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Load byte into user-mode register"},
/* 0x3 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRBT ptrmar", LDRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Load byte into user-mode register"},
/* 0x5 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRBT ptrmrr", LDRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Load byte into user-mode register"},
/* 0x7 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRBT ptrmll", LDRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Load byte into user-mode register"},
/* 0x9 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRBT ptrmlr", LDRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Load byte into user-mode register"},
/* 0xb */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRBT ptrmar", LDRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Load byte into user-mode register"},
/* 0xd */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRBT ptrmrr", LDRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_WRITE_BACK, "action_copy", "Load byte into user-mode register"},
/* 0xf */ {0, "",             NONE,  NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_68[] = {
/* 0x0 */ {0, "STR ptrpll", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Store word"},
/* 0x1 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STR ptrplr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Store word"},
/* 0x3 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STR ptrpar", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Store word"},
/* 0x5 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STR ptrprr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Store word"},
/* 0x7 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STR ptrpll", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Store word"},
/* 0x9 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STR ptrplr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Store word"},
/* 0xb */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STR ptrpar", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Store word"},
/* 0xd */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STR ptrprr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Store word"},
/* 0xf */ {0, "",           NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_69[] = {
/* 0x0 */ {0, "LDR ptrpll", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Load word"},
/* 0x1 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDR ptrplr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Load word"},
/* 0x3 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDR ptrpar", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Load word"},
/* 0x5 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDR ptrprr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Load word"},
/* 0x7 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDR ptrpll", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Load word"},
/* 0x9 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDR ptrplr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Load word"},
/* 0xb */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDR ptrpar", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Load word"},
/* 0xd */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDR ptrprr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Load word"},
/* 0xf */ {0, "",           NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_6a[] = {
/* 0x0 */ {0, "STRT ptrpll", STRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store word from user-mode register"},
/* 0x1 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRT ptrplr", STRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store word from user-mode register"},
/* 0x3 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRT ptrpar", STRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store word from user-mode register"},
/* 0x5 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRT ptrprr", STRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store word from user-mode register"},
/* 0x7 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRT ptrpll", STRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store word from user-mode register"},
/* 0x9 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRT ptrplr", STRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store word from user-mode register"},
/* 0xb */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRT ptrpar", STRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store word from user-mode register"},
/* 0xd */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRT ptrprr", STRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store word from user-mode register"},
/* 0xf */ {0, "",            NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_6b[] = {
/* 0x0 */ {0, "LDRT ptrpll", LDRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load word into user-mode register"},
/* 0x1 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRT ptrplr", LDRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load word into user-mode register"},
/* 0x3 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRT ptrpar", LDRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load word into user-mode register"},
/* 0x5 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRT ptrprr", LDRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load word into user-mode register"},
/* 0x7 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRT ptrpll", LDRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load word into user-mode register"},
/* 0x9 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRT ptrplr", LDRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load word into user-mode register"},
/* 0xb */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRT ptrpar", LDRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load word into user-mode register"},
/* 0xd */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRT ptrprr", LDRT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load word into user-mode register"},
/* 0xf */ {0, "",            NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_6c[] = {
/* 0x0 */ {0, "STRB ptrpll", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Store byte"},
/* 0x1 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRB ptrplr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Store byte"},
/* 0x3 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRB ptrpar", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Store byte"},
/* 0x5 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRB ptrprr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Store byte"},
/* 0x7 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRB ptrpll", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Store byte"},
/* 0x9 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRB ptrplr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Store byte"},
/* 0xb */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRB ptrpar", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Store byte"},
/* 0xd */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRB ptrprr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Store byte"},
/* 0xf */ {0, "",            NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_6d[] = {
/* 0x0 */ {0, "LDRB ptrpll", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Load byte"},
/* 0x1 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRB ptrplr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Load byte"},
/* 0x3 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRB ptrpar", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Load byte"},
/* 0x5 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRB ptrprr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Load byte"},
/* 0x7 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRB ptrpll", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Load byte"},
/* 0x9 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRB ptrplr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Load byte"},
/* 0xb */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRB ptrpar", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Load byte"},
/* 0xd */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRB ptrprr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET, "action_copy", "Load byte"},
/* 0xf */ {0, "",            NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_6e[] = {
/* 0x0 */ {0, "STRBT ptrpll", STRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store byte from user-mode register"},
/* 0x1 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRBT ptrplr", STRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store byte from user-mode register"},
/* 0x3 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRBT ptrpar", STRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store byte from user-mode register"},
/* 0x5 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRBT ptrprr", STRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store byte from user-mode register"},
/* 0x7 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRBT ptrpll", STRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store byte from user-mode register"},
/* 0x9 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRBT ptrplr", STRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store byte from user-mode register"},
/* 0xb */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRBT ptrpar", STRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store byte from user-mode register"},
/* 0xd */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRBT ptrprr", STRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store byte from user-mode register"},
/* 0xf */ {0, "",             NONE,  NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_6f[] = {
/* 0x0 */ {0, "LDRBT ptrpll", LDRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load byte into user-mode register"},
/* 0x1 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRBT ptrplr", LDRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load byte into user-mode register"},
/* 0x3 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRBT ptrpar", LDRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load byte into user-mode register"},
/* 0x5 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRBT ptrprr", LDRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load byte into user-mode register"},
/* 0x7 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRBT ptrpll", LDRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load byte into user-mode register"},
/* 0x9 */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRBT ptrplr", LDRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load byte into user-mode register"},
/* 0xb */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRBT ptrpar", LDRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load byte into user-mode register"},
/* 0xd */ {0, "",             NONE,  NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRBT ptrprr", LDRBT, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load byte into user-mode register"},
/* 0xf */ {0, "",             NONE,  NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_70[] = {
/* 0x0 */ {0, "STR ofrmll", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Store word"},
/* 0x1 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STR ofrmlr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Store word"},
/* 0x3 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STR ofrmar", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Store word"},
/* 0x5 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STR ofrmrr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Store word"},
/* 0x7 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STR ofrmll", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Store word"},
/* 0x9 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STR ofrmlr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Store word"},
/* 0xb */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STR ofrmar", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Store word"},
/* 0xd */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STR ofrmrr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Store word"},
/* 0xf */ {0, "",           NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_71[] = {
/* 0x0 */ {0, "LDR ofrmll", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Load word"},
/* 0x1 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDR ofrmlr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Load word"},
/* 0x3 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDR ofrmar", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Load word"},
/* 0x5 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDR ofrmrr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Load word"},
/* 0x7 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDR ofrmll", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Load word"},
/* 0x9 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDR ofrmlr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Load word"},
/* 0xb */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDR ofrmar", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Load word"},
/* 0xd */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDR ofrmrr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Load word"},
/* 0xf */ {0, "",           NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_72[] = {
/* 0x0 */ {0, "STR prrmll", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store word"},
/* 0x1 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STR prrmlr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store word"},
/* 0x3 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STR prrmar", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store word"},
/* 0x5 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STR prrmrr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store word"},
/* 0x7 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STR prrmll", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store word"},
/* 0x9 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STR prrmlr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store word"},
/* 0xb */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STR prrmar", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store word"},
/* 0xd */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STR prrmrr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store word"},
/* 0xf */ {0, "",           NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_73[] = {
/* 0x0 */ {0, "LDR prrmll", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load word"},
/* 0x1 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDR prrmlr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load word"},
/* 0x3 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDR prrmar", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load word"},
/* 0x5 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDR prrmrr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load word"},
/* 0x7 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDR prrmll", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load word"},
/* 0x9 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDR prrmlr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load word"},
/* 0xb */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDR prrmar", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load word"},
/* 0xd */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDR prrmrr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load word"},
/* 0xf */ {0, "",           NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_74[] = {
/* 0x0 */ {0, "STRB ofrmll", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0x1 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRB ofrmlr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0x3 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRB ofrmar", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0x5 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRB ofrmrr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0x7 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRB ofrmll", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0x9 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRB ofrmlr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0xb */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRB ofrmar", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0xd */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRB ofrmrr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0xf */ {0, "",            NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_75[] = {
/* 0x0 */ {0, "LDRB ofrmll", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Load byte"},
/* 0x1 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRB ofrmlr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Load byte"},
/* 0x3 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRB ofrmar", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Load byte"},
/* 0x5 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRB ofrmrr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Load byte"},
/* 0x7 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRB ofrmll", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Load byte"},
/* 0x9 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRB ofrmlr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Load byte"},
/* 0xb */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRB ofrmar", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Load byte"},
/* 0xd */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRB ofrmrr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX, "action_copy", "Load byte"},
/* 0xf */ {0, "",            NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_76[] = {
/* 0x0 */ {0, "STRB prrmll", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0x1 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRB prrmlr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0x3 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRB prrmar", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0x5 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRB prrmrr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0x7 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRB prrmll", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0x9 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRB prrmlr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0xb */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRB prrmar", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0xd */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRB prrmrr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0xf */ {0, "",            NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_77[] = {
/* 0x0 */ {0, "LDRB prrmll", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load byte"},
/* 0x1 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRB prrmlr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load byte"},
/* 0x3 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRB prrmar", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load byte"},
/* 0x5 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRB prrmrr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load byte"},
/* 0x7 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRB prrmll", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load byte"},
/* 0x9 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRB prrmlr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load byte"},
/* 0xb */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRB prrmar", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load byte"},
/* 0xd */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRB prrmrr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load byte"},
/* 0xf */ {0, "",            NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_78[] = {
/* 0x0 */ {0, "STR ofrpll", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store word"},
/* 0x1 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STR ofrplr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store word"},
/* 0x3 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STR ofrpar", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store word"},
/* 0x5 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STR ofrprr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store word"},
/* 0x7 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STR ofrpll", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store word"},
/* 0x9 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STR ofrplr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store word"},
/* 0xb */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STR ofrpar", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store word"},
/* 0xd */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STR ofrprr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store word"},
/* 0xf */ {0, "",           NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_79[] = {
/* 0x0 */ {0, "LDR ofrpll", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load word"},
/* 0x1 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDR ofrplr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load word"},
/* 0x3 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDR ofrpar", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load word"},
/* 0x5 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDR ofrprr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load word"},
/* 0x7 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDR ofrpll", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load word"},
/* 0x9 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDR ofrplr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load word"},
/* 0xb */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDR ofrpar", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load word"},
/* 0xd */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDR ofrprr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load word"},
/* 0xf */ {0, "",           NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_7a[] = {
/* 0x0 */ {0, "STR prrpll", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store word"},
/* 0x1 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STR prrplr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store word"},
/* 0x3 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STR prrpar", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store word"},
/* 0x5 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STR prrprr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store word"},
/* 0x7 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STR prrpll", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store word"},
/* 0x9 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STR prrplr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store word"},
/* 0xb */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STR prrpar", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store word"},
/* 0xd */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STR prrprr", STR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store word"},
/* 0xf */ {0, "",           NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_7b[] = {
/* 0x0 */ {0, "LDR prrpll", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load word"},
/* 0x1 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDR prrplr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load word"},
/* 0x3 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDR prrpar", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load word"},
/* 0x5 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDR prrprr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load word"},
/* 0x7 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDR prrpll", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load word"},
/* 0x9 */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDR prrplr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load word"},
/* 0xb */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDR prrpar", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load word"},
/* 0xd */ {0, "",           NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDR prrprr", LDR,  OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load word"},
/* 0xf */ {0, "",           NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_7c[] = {
/* 0x0 */ {0, "STRB ofrpll", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store byte"},
/* 0x1 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRB ofrplr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store byte"},
/* 0x3 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRB ofrpar", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store byte"},
/* 0x5 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRB ofrprr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store byte"},
/* 0x7 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRB ofrpll", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store byte"},
/* 0x9 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRB ofrplr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store byte"},
/* 0xb */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRB ofrpar", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store byte"},
/* 0xd */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRB ofrprr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store byte"},
/* 0xf */ {0, "",            NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_7d[] = {
/* 0x0 */ {0, "LDRB ofrpll", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load byte"},
/* 0x1 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRB ofrplr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load byte"},
/* 0x3 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRB ofrpar", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load byte"},
/* 0x5 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRB ofrprr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load byte"},
/* 0x7 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRB ofrpll", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load byte"},
/* 0x9 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRB ofrplr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load byte"},
/* 0xb */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRB ofrpar", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load byte"},
/* 0xd */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRB ofrprr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load byte"},
/* 0xf */ {0, "",            NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_7e[] = {
/* 0x0 */ {0, "STRB prrpll", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0x1 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "STRB prrplr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0x3 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "STRB prrpar", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0x5 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "STRB prrprr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0x7 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "STRB prrpll", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0x9 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "STRB prrplr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0xb */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "STRB prrpar", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0xd */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "STRB prrprr", STRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0xf */ {0, "",            NONE, NONE, "", "UNDEFINED"}
};

/* bits 7-4 */
instr_description table_opcode_7f[] = {
/* 0x0 */ {0, "LDRB prrpll", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load byte"},
/* 0x1 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x2 */ {0, "LDRB prrplr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load byte"},
/* 0x3 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x4 */ {0, "LDRB prrpar", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load byte"},
/* 0x5 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x6 */ {0, "LDRB prrprr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load byte"},
/* 0x7 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0x8 */ {0, "LDRB prrpll", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load byte"},
/* 0x9 */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xa */ {0, "LDRB prrplr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load byte"},
/* 0xb */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xc */ {0, "LDRB prrpar", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load byte"},
/* 0xd */ {0, "",            NONE, NONE, "", "UNDEFINED"},
/* 0xe */ {0, "LDRB prrprr", LDRB, OPND_REG_OFFSET_SHIFT_BY_IMM | OPND_INCR_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load byte"},
/* 0xf */ {0, "",            NONE, NONE, "", "UNDEFINED"}
};

/* bits 27-20 */
instr_description table_opcode_onebyte[] = {
/* 0x00 */ {table_opcode_00, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x01 */ {table_opcode_01, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x02 */ {table_opcode_02, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x03 */ {table_opcode_03, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x04 */ {table_opcode_04, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x05 */ {table_opcode_05, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x06 */ {table_opcode_06, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x07 */ {table_opcode_07, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x08 */ {table_opcode_08, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x09 */ {table_opcode_09, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x0a */ {table_opcode_0a, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x0b */ {table_opcode_0b, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x0c */ {table_opcode_0c, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x0d */ {table_opcode_0d, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x0e */ {table_opcode_0e, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x0f */ {table_opcode_0f, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x10 */ {table_opcode_10, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x11 */ {table_opcode_11, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x12 */ {table_opcode_12, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x13 */ {table_opcode_13, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x14 */ {table_opcode_14, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x15 */ {table_opcode_15, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x16 */ {table_opcode_16, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x17 */ {table_opcode_17, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x18 */ {table_opcode_18, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x19 */ {table_opcode_19, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x1a */ {table_opcode_1a, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x1b */ {table_opcode_1b, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x1c */ {table_opcode_1c, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x1d */ {table_opcode_1d, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x1e */ {table_opcode_1e, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x1f */ {table_opcode_1f, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x20 */ {0, "AND imm",    AND,    OPND_IMM, "action_copy", "Logical And"},
/* 0x21 */ {0, "ANDS imm",   ANDS,   OPND_IMM, "action_copy", "Logical And, setting flags"},
/* 0x22 */ {0, "EOR imm",    EOR,    OPND_IMM, "action_copy", "Logical Exclusive-or"},
/* 0x23 */ {0, "EORS imm",   EORS,   OPND_IMM, "action_copy", "Logical Exclusive-or, setting flags"},
/* 0x24 */ {0, "SUB imm",    SUB,    OPND_IMM, "action_copy", "Subtract from register"},
/* 0x25 */ {0, "SUBS imm",   SUBS,   OPND_IMM, "action_copy", "Subtract, setting flags"},
/* 0x26 */ {0, "RSB imm",    RSB,    OPND_IMM, "action_copy", "Subtract register from value"},
/* 0x27 */ {0, "RSBS imm",   RSBS,   OPND_IMM, "action_copy", "Reverse Subtract, setting flags"},
/* 0x28 */ {0, "ADD imm",    ADD,    OPND_IMM, "action_copy", "Add to register"},
/* 0x29 */ {0, "ADDS imm",   ADDS,   OPND_IMM, "action_copy", "Add to register, setting flags"},
/* 0x2a */ {0, "ADC imm",    ADC,    OPND_IMM, "action_copy", "Add to register with carry"},
/* 0x2b */ {0, "ADCS imm",   ADCS,   OPND_IMM, "action_copy", "Add to register with carry, setting flags"},
/* 0x2c */ {0, "SBC imm",    SBC,    OPND_IMM, "action_copy", "Subtract from register with borrow"},
/* 0x2d */ {0, "SBCS imm",   SBCS,   OPND_IMM, "action_copy", "Subtract from register with borrow, setting flags"},
/* 0x2e */ {0, "RSC imm",    RSC,    OPND_IMM, "action_copy", "Subtract register from value with borrow"},
/* 0x2f */ {0, "RSCS imm",   RSCS,   OPND_IMM, "action_copy", "Subtract register from value with borrow, setting flags"},
/* 0x30 */ {0, "UNDEFINED",  NONE,   NONE, "", "NO_ACTION_CALLED"},
/* 0x31 */ {0, "TST imm",    TSTS,   OPND_IMM, "action_copy", "Test bits in register (Logical And), setting flags"},
/* 0x32 */ {0, "MSR ic",     MSR,    NONE, "action_copy", "Move value to status word"},
/* 0x33 */ {0, "TEQ imm",    TEQS,   OPND_IMM, "action_copy", "Test equivalence of bits in register (Logical Exclusive-or), setting flags"},
/* 0x34 */ {0, "UNDEFINED",  NONE,   NONE, "", "NO_ACTION_CALLED"},
/* 0x35 */ {0, "CMP imm",    CMPS,   OPND_IMM, "action_copy", "Compare register to value (Subtract), setting flags"},
/* 0x36 */ {0, "MSR is",     MSR,    NONE, "action_copy", "Move value to status word"},
/* 0x37 */ {0, "CMN imm",    CMNS,   OPND_IMM, "action_copy", "Compare register to negation of value (Add), setting flags"},
/* 0x38 */ {0, "ORR imm",    ORR,    OPND_IMM, "action_copy", "Logical Or"},
/* 0x39 */ {0, "ORRS imm",   ORRS,   OPND_IMM, "action_copy", "Logical Or, setting flags"},
/* 0x3a */ {0, "MOV imm",    MOV,    OPND_IMM, "action_copy", "Move value to a register"},
/* 0x3b */ {0, "MOVS imm",   MOVS,   OPND_IMM, "action_copy", "Move value to a register, setting flags"},
/* 0x3c */ {0, "BIC imm",    BIC,    OPND_IMM, "action_copy", "Clear bits in register (NAND)"},
/* 0x3d */ {0, "BICS imm",   BICS,   OPND_IMM, "action_copy", "Clear bits in register (NAND), setting flags"},
/* 0x3e */ {0, "MVN imm",    MVN,    OPND_IMM, "action_copy", "Move negation of value to a register"},
/* 0x3f */ {0, "MVNS imm",   MVNS,   OPND_IMM, "action_copy", "Move negation of value to a register, setting flags"},
/* 0x40 */ {0, "STR ptim",   STR,    OPND_IMM_OFFSET, "action_copy", "Store word"},
/* 0x41 */ {0, "LDR ptim",   LDR,    OPND_IMM_OFFSET, "action_copy", "Load word"},
/* 0x42 */ {0, "STRT ptim",  STRT,   OPND_IMM_OFFSET | OPND_WRITE_BACK, "action_copy", "Store word from user-mode register"},
/* 0x43 */ {0, "LDRT ptim",  LDRT,   OPND_IMM_OFFSET | OPND_WRITE_BACK, "action_copy", "Load word into user-mode register"},
/* 0x44 */ {0, "STRB ptim",  STRB,   OPND_IMM_OFFSET, "action_copy", "Store byte"},
/* 0x45 */ {0, "LDRB ptim",  LDRB,   OPND_IMM_OFFSET, "action_copy", "Load byte"},
/* 0x46 */ {0, "STRBT ptim", STRBT,  OPND_IMM_OFFSET | OPND_WRITE_BACK, "action_copy", "Store byte from user-mode register"},
/* 0x47 */ {0, "LDRBT ptim", LDRBT,  OPND_IMM_OFFSET | OPND_WRITE_BACK, "action_copy", "Load byte into user-mode register"},
/* 0x48 */ {0, "STR ptip",   STR,    OPND_IMM_OFFSET | OPND_INCR_OFFSET, "action_copy", "Store word"},
/* 0x49 */ {0, "LDR ptip",   LDR,    OPND_IMM_OFFSET | OPND_INCR_OFFSET, "action_copy", "Load word"},
/* 0x4a */ {0, "STRT ptip",  STRT,   OPND_IMM_OFFSET | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store word from user-mode register"},
/* 0x4b */ {0, "LDRT ptip",  LDRT,   OPND_IMM_OFFSET | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load word into user-mode register"},
/* 0x4c */ {0, "STRB ptip",  STRB,   OPND_IMM_OFFSET | OPND_INCR_OFFSET, "action_copy", "Store byte"},
/* 0x4d */ {0, "LDRB ptip",  LDRB,   OPND_IMM_OFFSET | OPND_INCR_OFFSET, "action_copy", "Load byte"},
/* 0x4e */ {0, "STRBT ptip", STRBT,  OPND_IMM_OFFSET | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store byte from user-mode register"},
/* 0x4f */ {0, "LDRBT ptip", LDRBT,  OPND_IMM_OFFSET | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load byte into user-mode register"},
/* 0x50 */ {0, "STR ofim",   STR,    OPND_IMM_OFFSET | OPND_PRE_INDEX, "action_copy", "Store word"},
/* 0x51 */ {0, "LDR ofim",   LDR,    OPND_IMM_OFFSET | OPND_PRE_INDEX, "action_copy", "Load word"},
/* 0x52 */ {0, "STR prim",   STR,    OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store word"},
/* 0x53 */ {0, "LDR prim",   LDR,    OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load word"},
/* 0x54 */ {0, "STRB ofim",  STRB,   OPND_IMM_OFFSET | OPND_PRE_INDEX, "action_copy", "Store byte"},
/* 0x55 */ {0, "LDRB ofim",  LDRB,   OPND_IMM_OFFSET | OPND_PRE_INDEX, "action_copy", "Load byte"},
/* 0x56 */ {0, "STRB prim",  STRB,   OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0x57 */ {0, "LDRB prim",  LDRB,   OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_WRITE_BACK, "action_copy", "Load byte"},
/* 0x58 */ {0, "STR ofip",   STR,    OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store word"},
/* 0x59 */ {0, "LDR ofip",   LDR,    OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load word"},
/* 0x5a */ {0, "STR prip",   STR,    OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store word"},
/* 0x5b */ {0, "LDR prip",   LDR,    OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load word"},
/* 0x5c */ {0, "STRB ofip",  STRB,   OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Store byte"},
/* 0x5d */ {0, "LDRB ofip",  LDRB,   OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_INCR_OFFSET, "action_copy", "Load byte"},
/* 0x5e */ {0, "STRB prip",  STRB,   OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Store byte"},
/* 0x5f */ {0, "LDRB prip",  LDRB,   OPND_IMM_OFFSET | OPND_PRE_INDEX | OPND_INCR_OFFSET | OPND_WRITE_BACK, "action_copy", "Load byte"},
/* 0x60 */ {table_opcode_60, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x61 */ {table_opcode_61, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x62 */ {table_opcode_62, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x63 */ {table_opcode_63, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x64 */ {table_opcode_64, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x65 */ {table_opcode_65, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x66 */ {table_opcode_66, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x67 */ {table_opcode_67, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x68 */ {table_opcode_68, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x69 */ {table_opcode_69, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x6a */ {table_opcode_6a, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x6b */ {table_opcode_6b, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x6c */ {table_opcode_6c, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x6d */ {table_opcode_6d, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x6e */ {table_opcode_6e, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x6f */ {table_opcode_6f, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x70 */ {table_opcode_70, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x71 */ {table_opcode_71, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x72 */ {table_opcode_72, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x73 */ {table_opcode_73, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x74 */ {table_opcode_74, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x75 */ {table_opcode_75, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x76 */ {table_opcode_76, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x77 */ {table_opcode_77, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x78 */ {table_opcode_78, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x79 */ {table_opcode_79, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x7a */ {table_opcode_7a, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x7b */ {table_opcode_7b, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x7c */ {table_opcode_7c, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x7d */ {table_opcode_7d, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x7e */ {table_opcode_7e, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x7f */ {table_opcode_7f, "", NONE, NONE, "", "NO_ACTION_CALLED"},
/* 0x80 */ {0, "STMDA",    STMDA, NONE, "action_copy", "Store multiple words, decrement after"},
/* 0x81 */ {0, "LDMDA",    LDMDA, NONE, "action_copy", "Load multiple words, decrement after"},
/* 0x82 */ {0, "STMDA w",  STMDA, NONE, "action_copy", "Store multiple words, decrement after"},
/* 0x83 */ {0, "LDMDA w",  LDMDA, NONE, "action_copy", "Load multiple words, decrement after"},
/* 0x84 */ {0, "STMDA u",  STMDA, NONE, "action_copy", "Store multiple words, decrement after"},
/* 0x85 */ {0, "LDMDA u",  LDMDA, NONE, "action_copy", "Load multiple words, decrement after"},
/* 0x86 */ {0, "STMDA uw", STMDA, NONE, "action_copy", "Store multiple words, decrement after"},
/* 0x87 */ {0, "LDMDA uw", NONE,  NONE, "action_copy", "Load multiple words, decrement after"},
/* 0x88 */ {0, "STMIA",    STMIA, NONE, "action_copy", "Store multiple words, increment after"},
/* 0x89 */ {0, "LDMIA",    LDMIA, NONE, "action_copy", "Load multiple words, increment after"},
/* 0x8a */ {0, "STMIA w",  STMIA, NONE, "action_copy", "Store multiple words, increment after"},
/* 0x8b */ {0, "LDMIA w",  LDMIA, NONE, "action_copy", "Load multiple words, increment after"},
/* 0x8c */ {0, "STMIA u",  STMIA, NONE, "action_copy", "Store multiple words, increment after"},
/* 0x8d */ {0, "LDMIA u",  LDMIA, NONE, "action_copy", "Load multiple words, increment after"},
/* 0x8e */ {0, "STMIA uw", STMIA, NONE, "action_copy", "Store multiple words, increment after"},
/* 0x8f */ {0, "LDMIA uw", LDMIA, NONE, "action_copy", "Load multiple words, increment after"},
/* 0x90 */ {0, "STMDB",    STMDB, NONE, "action_copy", "Store multiple words, decrement before"},
/* 0x91 */ {0, "LDMDB",    LDMDB, NONE, "action_copy", "Load multiple words, decrement before"},
/* 0x92 */ {0, "STMDB w",  STMDB, NONE, "action_copy", "Store multiple words, decrement before"},
/* 0x93 */ {0, "LDMDB w",  LDMDB, NONE, "action_copy", "Load multiple words, decrement before"},
/* 0x94 */ {0, "STMDB u",  STMDB, NONE, "action_copy", "Store multiple words, decrement before"},
/* 0x95 */ {0, "LDMDB u",  LDMDB, NONE, "action_copy", "Load multiple words, decrement before"},
/* 0x96 */ {0, "STMDB uw", STMDB, NONE, "action_copy", "Store multiple words, decrement before"},
/* 0x97 */ {0, "LDMDB uw", LDMDB, NONE, "action_copy", "Load multiple words, decrement before"},
/* 0x98 */ {0, "STMIB",    STMIB, NONE, "action_copy", "Store multiple words, increment before"},
/* 0x99 */ {0, "LDMIB",    LDMIB, NONE, "action_copy", "Load multiple words, increment before"},
/* 0x9a */ {0, "STMIB w",  STMIB, NONE, "action_copy", "Store multiple words, increment before"},
/* 0x9b */ {0, "LDMIB w",  LDMIB, NONE, "action_copy", "Load multiple words, increment before"},
/* 0x9c */ {0, "STMIB u",  STMIB, NONE, "action_copy", "Store multiple words, increment before"},
/* 0x9d */ {0, "LDMIB u",  LDMIB, NONE, "action_copy", "Load multiple words, increment before"},
/* 0x9e */ {0, "STMIB uw", STMIB, NONE, "action_copy", "Store multiple words, increment before"},
/* 0x9f */ {0, "LDMIB uw", LDMIB, NONE, "action_copy", "Load multiple words, increment before"},
/* 0xa0 */ {0, "B",  B,  NONE, "action_copy", "Branch"},
/* 0xa1 */ {0, "B",  B,  NONE, "action_copy", "Branch"},
/* 0xa2 */ {0, "B",  B,  NONE, "action_copy", "Branch"},
/* 0xa3 */ {0, "B",  B,  NONE, "action_copy", "Branch"},
/* 0xa4 */ {0, "B",  B,  NONE, "action_copy", "Branch"},
/* 0xa5 */ {0, "B",  B,  NONE, "action_copy", "Branch"},
/* 0xa6 */ {0, "B",  B,  NONE, "action_copy", "Branch"},
/* 0xa7 */ {0, "B",  B,  NONE, "action_copy", "Branch"},
/* 0xa8 */ {0, "B",  B,  NONE, "action_copy", "Branch"},
/* 0xa9 */ {0, "B",  B,  NONE, "action_copy", "Branch"},
/* 0xaa */ {0, "B",  B,  NONE, "action_copy", "Branch"},
/* 0xab */ {0, "B",  B,  NONE, "action_copy", "Branch"},
/* 0xac */ {0, "B",  B,  NONE, "action_copy", "Branch"},
/* 0xad */ {0, "B",  B,  NONE, "action_copy", "Branch"},
/* 0xae */ {0, "B",  B,  NONE, "action_copy", "Branch"},
/* 0xaf */ {0, "B",  B,  NONE, "action_copy", "Branch"},
/* 0xB0 */ {0, "BL", BL, NONE, "action_copy", "Branch and link"},
/* 0xB1 */ {0, "BL", BL, NONE, "action_copy", "Branch and link"},
/* 0xB2 */ {0, "BL", BL, NONE, "action_copy", "Branch and link"},
/* 0xB3 */ {0, "BL", BL, NONE, "action_copy", "Branch and link"},
/* 0xB4 */ {0, "BL", BL, NONE, "action_copy", "Branch and link"},
/* 0xB5 */ {0, "BL", BL, NONE, "action_copy", "Branch and link"},
/* 0xB6 */ {0, "BL", BL, NONE, "action_copy", "Branch and link"},
/* 0xB7 */ {0, "BL", BL, NONE, "action_copy", "Branch and link"},
/* 0xB8 */ {0, "BL", BL, NONE, "action_copy", "Branch and link"},
/* 0xB9 */ {0, "BL", BL, NONE, "action_copy", "Branch and link"},
/* 0xBA */ {0, "BL", BL, NONE, "action_copy", "Branch and link"},
/* 0xBB */ {0, "BL", BL, NONE, "action_copy", "Branch and link"},
/* 0xBC */ {0, "BL", BL, NONE, "action_copy", "Branch and link"},
/* 0xBD */ {0, "BL", BL, NONE, "action_copy", "Branch and link"},
/* 0xBE */ {0, "BL", BL, NONE, "action_copy", "Branch and link"},
/* 0xBF */ {0, "BL", BL, NONE, "action_copy", "Branch and link"},
/* 0xC0 */ {0, "STC ofm", STC, NONE, "action_copy", "Store coprocessor data to memory"},
/* 0xC1 */ {0, "LDC ofm", LDC, NONE, "action_copy", "Load coprocessor data from memory"},
/* 0xC2 */ {0, "STC prm", STC, NONE, "action_copy", "Store coprocessor data to memory"},
/* 0xC3 */ {0, "LDC prm", LDC, NONE, "action_copy", "Load coprocessor data from memory"},
/* 0xC4 */ {0, "STC ofm", STC, NONE, "action_copy", "Store coprocessor data to memory"},
/* 0xC5 */ {0, "LDC ofm", LDC, NONE, "action_copy", "Load coprocessor data from memory"},
/* 0xC6 */ {0, "STC prm", STC, NONE, "action_copy", "Store coprocessor data to memory"},
/* 0xC7 */ {0, "LDC prm", LDC, NONE, "action_copy", "Load coprocessor data from memory"},
/* 0xC8 */ {0, "STC ofp", STC, NONE, "action_copy", "Store coprocessor data to memory"},
/* 0xC9 */ {0, "LDC ofp", LDC, NONE, "action_copy", "Load coprocessor data from memory"},
/* 0xCA */ {0, "STC prp", STC, NONE, "action_copy", "Store coprocessor data to memory"},
/* 0xCB */ {0, "LDC prp", LDC, NONE, "action_copy", "Load coprocessor data from memory"},
/* 0xCC */ {0, "STC ofp", STC, NONE, "action_copy", "Store coprocessor data to memory"},
/* 0xCD */ {0, "LDC ofp", LDC, NONE, "action_copy", "Load coprocessor data from memory"},
/* 0xCE */ {0, "STC prp", STC, NONE, "action_copy", "Store coprocessor data to memory"},
/* 0xCF */ {0, "LDC prp", LDC, NONE, "action_copy", "Load coprocessor data from memory"},
/* 0xD0 */ {0, "STC unm", STC, NONE, "action_copy", "Store coprocessor data to memory"},
/* 0xD1 */ {0, "LDC unm", LDC, NONE, "action_copy", "Load coprocessor data from memory"},
/* 0xD2 */ {0, "STC ptm", STC, NONE, "action_copy", "Store coprocessor data to memory"},
/* 0xD3 */ {0, "LDC ptm", LDC, NONE, "action_copy", "Load coprocessor data from memory"},
/* 0xD4 */ {0, "STC unm", STC, NONE, "action_copy", "Store coprocessor data to memory"},
/* 0xD5 */ {0, "LDC unm", LDC, NONE, "action_copy", "Load coprocessor data from memory"},
/* 0xD6 */ {0, "STC ptm", STC, NONE, "action_copy", "Store coprocessor data to memory"},
/* 0xD7 */ {0, "LDC ptm", LDC, NONE, "action_copy", "Load coprocessor data from memory"},
/* 0xD8 */ {0, "STC unp", STC, NONE, "action_copy", "Store coprocessor data to memory"},
/* 0xD9 */ {0, "LDC unp", LDC, NONE, "action_copy", "Load coprocessor data from memory"},
/* 0xDA */ {0, "STC ptp", STC, NONE, "action_copy", "Store coprocessor data to memory"},
/* 0xDB */ {0, "LDC ptp", LDC, NONE, "action_copy", "Load coprocessor data from memory"},
/* 0xDC */ {0, "STC unp", STC, NONE, "action_copy", "Store coprocessor data to memory"},
/* 0xDD */ {0, "LDC unp", LDC, NONE, "action_copy", "Load coprocessor data from memory"},
/* 0xDE */ {0, "STC ptp", STC, NONE, "action_copy", "Store coprocessor data to memory"},
/* 0xDF */ {0, "LDC ptp", LDC, NONE, "action_copy", "Load coprocessor data from memory"}

/* TODO: 0xE0 - 0xEF: coprocessor data operations */
/* TODO: 0xF0 - 0xFF: software interrupts */
};

#endif  // ARM_OPCODE_MAP

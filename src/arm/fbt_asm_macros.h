/**
 * @file fbt_asm_macros.h
 * This header file contains all macros needed in arm/fbt_actions.c to
 * generate the machine code used in the ccfs
 *
 * Copyright (c) 2015 Felipe O. Carvalho
 * @author Felipe O. Carvalho <felipekde@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
 */
#ifndef ARM_FBT_ASM_MACROS_H
#define ARM_FBT_ASM_MACROS_H

#include "../fbt_debug.h"

#define DEBUG_GEN_CODE(code) PRINT_DEBUG("generated code: %p", *((code) - 1))

static void gen_ldr_imm32(Code **code, uint32_t Rt, uint32_t imm32) {
  PRINT_DEBUG_FUNCTION_START("gen_ldr_imm32(*code=%p, Rt=%p, imm32=%p",
                             *code, Rt, imm32);

  // ldr Rt, [Rn]: 0xe 0101 1001 <Rt> <Rn> 0x000
  *((*code)++) = 0xe59f00000 | (Rt << 12);  /* ldr Rt, [pc] */   DEBUG_GEN_CODE(*code);
  *((*code)++) = 0xea000000;                /* b <after_word> */ DEBUG_GEN_CODE(*code);
  *((*code)++) = imm32;                     /* .word <imm32> */  DEBUG_GEN_CODE(*code);
  // after_word:

  PRINT_DEBUG_FUNCTION_END(" ");
}
#define GEN_LDR_IMM32(code, Rt, imm32) gen_ldr_imm32(&code, Rt, imm32)

static void gen_b_abs(Code **code, Code *target_addr) {
  PRINT_DEBUG_FUNCTION_START("gen_b_abs(*code=%p, *target_addr=%p",
                             *code, target_addr);

  // ldr Rt, [Rn, #-<imm>]: 0xe 0101 0001 <Rt> <Rn> <imm12>
  *((*code)++) = 0xe51ff001;         /* ldr pc, [pc, #-4] */   DEBUG_GEN_CODE(*code);
  *((*code)++) = (Code)target_addr;  /* .word <target_addr> */ DEBUG_GEN_CODE(*code);

  PRINT_DEBUG_FUNCTION_END(" ");
}
#define GEN_B_ABS(code, target_addr) gen_b_abs((&code), target_addr)

#endif  /* ARM_FBT_ASM_MACROS_H */

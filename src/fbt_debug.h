/**
 * @file fbt_debug.h
 * This handles the debug output that can be customized in the Makefile
 *
 * IMPORTANT:
 * - The macro START_DEBUG and START_DUMP must be called before any
 *   call to PRINT_* or DUMP_* respectively, otherwise the program
 *   will fail.
 * - The macro STOP_DEBUG and STOP_DUMP clean up the data structure
 *   after calling one of these macros the corresponding debugging
 *   features must not be called anymore otherwise the program will
 *   abort.
 *
 * WARNING: concerns DEBUG_FUNCTION_{START,END} and DEBUG_PRINT_N
 * - Everything_ written on the same line after one of the above
 *   macros will be ignored!
 * - output is written to file (i.e. debug.txt)
 * - macros are thread safe
 *
 * Copyright (c) 2011 ETH Zurich
 * @author Mathias Payer <mathias.payer@nebelwelt.net>
 *
 * $Date: 2011-12-30 14:24:05 +0100 (Fri, 30 Dec 2011) $
 * $LastChangedDate: 2011-12-30 14:24:05 +0100 (Fri, 30 Dec 2011) $
 * $LastChangedBy: payerm $
 * $Revision: 1134 $
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
#ifndef FBT_DEBUG_H
#define FBT_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DEBUG

/**
 * The file names for the output
 */
#define DEBUG_FILE_NAME	"debug.txt"
#define CODE_DUMP_FILE_NAME "code_dump.txt"
#define JMP_TABLE_DUMP_FILE_NAME "jmpTable_dump.txt"

/* forward declare translate_t */
struct translate;

/* use debug */
void debug_start();
void debug_end();
void debug_print_function_start(char *str, ...);
void debug_print_function_end(char *str, ...);
/* print a debug string with indentation */
void debug_print(char *str, ...);
char* debug_memdump(unsigned char *addr, unsigned int n);

#define DEBUG_START() debug_start()
#define DEBUG_END()   debug_end()
#define PRINT_DEBUG(...) debug_print(__VA_ARGS__)
#define PRINT_DEBUG_FUNCTION_START(...) debug_print_function_start(__VA_ARGS__)
#define PRINT_DEBUG_FUNCTION_END(...) debug_print_function_end(__VA_ARGS__)
#define MEMDUMP(addr, n) debug_memdump(addr, n)

/* todo remove */
char* printnbytes(unsigned char *addr, unsigned int n);
#else
/* no debug */
#define DEBUG_START()
#define DEBUG_END()
#define PRINT_DEBUG(...)
#define PRINT_DEBUG_FUNCTION_START(...)
#define PRINT_DEBUG_FUNCTION_END(...)
#define MEMDUMP(...)
#endif

#ifdef __cplusplus
}
#endif

#if defined(__i386__)
# include "ia32/fbt_ia32_debug.h"
#elif defined(__arm__)
# include "arm/fbt_arm_debug.h"
#endif

#endif  /* FBT_DEBUG_H */

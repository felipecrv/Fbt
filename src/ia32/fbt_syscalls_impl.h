/**
 * @file fbt_syscalls_impl.h
 * This file implements type definitions for system calls for i386 and X86_64.
 *
 * Copyright (c) 2011 ETH Zurich
 *
 * @author Mathias Payer <mathias.payer@nebelwelt.net>
 *
 * $Date: 2012-01-12 16:45:01 +0100 (Thu, 12 Jan 2012) $
 * $LastChangedDate: 2012-01-12 16:45:01 +0100 (Thu, 12 Jan 2012) $
 * $LastChangedBy: kravinae $
 * $Revision: 1167 $
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
#ifndef FBT_SYSCALLS_H
#define FBT_SYSCALLS_H

#include <sys/syscall.h>

#if defined(__x86_64__)
#define __syscall_clobber "r11","rcx","memory"

#define _syscall1(name,arg1,__res)                                      \
    __asm__ volatile ("syscall;"                                        \
                      : "=a"(__res)                                     \
                      : "0"(SYS_##name),"D"((long)(arg1))               \
                      : __syscall_clobber );

#define _syscall2(name,arg1,arg2,__res)                                 \
    __asm__ volatile ("syscall;"                                        \
                      : "=a"(__res)                                     \
                      : "0"(SYS_##name),"D"((long)(arg1)),              \
                        "S"((long)(arg2))                               \
                      : __syscall_clobber );

#define _syscall3(name,arg1,arg2,arg3,__res)                            \
    __asm__ volatile ("syscall;"                                        \
                      : "=a"(__res)                                     \
                      : "0"(SYS_##name), "D"((long)(arg1)),             \
                        "S"((long)(arg2)), "d"((long)(arg3))            \
                      : __syscall_clobber );

#define _syscall6(name,arg1,arg2,arg3,arg4,arg5,arg6,__res)             \
    __asm__ volatile("movq %5,%%r10 ;"                                  \
                     "movq %6,%%r8 ;"                                   \
                     "movq %7,%%r9 ;"                                   \
                     "syscall ;"                                        \
                     : "=a"(__res)                                      \
                     : "0"(SYS_##name), "D"((long)(arg1)),              \
                        "S"((long)(arg2)), "d"((long)(arg3)),           \
                        "g"((long)(arg4)), "g"((long)(arg5)),           \
                        "g"((long)(arg6))                               \
                      : __syscall_clobber );

#define SYS_unused1 222
#define SYS_unused2 223
#define SYS_unused3 251
#define SYS_sys_setaltroot 285

#else

/* fast or slow system call? */
//#if defined(__i686__)
//#define ENTER_KERNEL "call *%%gs:0x10 ;"
//#else
#define ENTER_KERNEL "int $0x80 ;"
//#endif  /* __i686__ */

#define _syscall(name,__res)                                            \
  __asm__ volatile (ENTER_KERNEL                                        \
                    : "=a"(__res)                                       \
                    : "0"(SYS_##name)                                   \
                    : "memory");


#define _syscall1(name,arg1,__res)                                      \
  __asm__ volatile ("push %%ebx ;"                                      \
                    "movl %2,%%ebx ; "                                  \
                    ENTER_KERNEL                                        \
                    "pop %%ebx"                                         \
                    : "=a"(__res)                                       \
                    : "0"(SYS_##name), "ri"((long)(arg1))               \
                    : "memory");


#define _syscall2(name,arg1,arg2,__res)                                 \
  __asm__ volatile ("push %%ebx ; "                                     \
                    "movl %2,%%ebx ; "                                  \
                    ENTER_KERNEL                                        \
                    "pop %%ebx"                                         \
                    : "=a"(__res)                                       \
                    : "0"(SYS_##name), "ri"((long)(arg1)),              \
                      "c"((long)(arg2))                                 \
                    : "memory");

#define _syscall3(name,arg1,arg2,arg3,__res)                            \
  __asm__ volatile ("push %%ebx ;"                                      \
                    "movl %2,%%ebx ;"                                   \
                    ENTER_KERNEL                                        \
                    "pop %%ebx"                                         \
                    : "=a"(__res)                                       \
                    : "0"(SYS_##name), "ri"((long)(arg1)),              \
                      "c"((long)(arg2)), "d"((long)(arg3))              \
                    : "memory");

#define _syscall4(name,arg1,arg2,arg3,arg4,__res)                       \
  __asm__ volatile ("pushl %%ebx ;"                                     \
                    "movl %2,%%ebx ;"                                   \
                    "movl %1,%%eax ;"                                   \
                    ENTER_KERNEL                                        \
                    "pop %%ebx"                                         \
                    : "=a"(__res)                                       \
                    : "i"(SYS_##name), "ri"((long)(arg1)),              \
                      "c"((long)(arg2)), "d"((long)(arg3)),             \
                      "S"((long)(arg4))                                 \
                    : "memory");

#define _syscall5(name,arg1,arg2,arg3,arg4,arg5,__res)                  \
  __asm__ volatile ("pushl %%ebx ;"                                     \
                    "movl %2,%%ebx ;"                                   \
                    "movl %1,%%eax ;"                                   \
                    ENTER_KERNEL                                        \
                    "pop %%ebx"                                         \
                    : "=a"(__res)                                       \
                    : "i"(SYS_##name), "ri"((long)(arg1)),              \
                      "c"((long)(arg2)), "d"((long)(arg3)),             \
                      "S"((long)(arg4)), "D"((long)(arg5))              \
                    : "memory");

#define _syscall6(name,arg1,arg2,arg3,arg4,arg5,arg6,__res)             \
  __asm__ volatile("pushl %%ebx ;"                                      \
                   "pushl %2 ;"                                         \
                   "pushl %3 ;"                                         \
                   "pushl %4 ;"                                         \
                   "pushl %5 ;"                                         \
                   "pushl %6 ;"                                         \
                   "pushl %7 ;"                                         \
                   "movl %%esp, %%ebx ;"                                \
                   ENTER_KERNEL                                         \
                   "addl $24, %%esp ;"                                  \
                   "popl %%ebx"                                         \
                   : "=a"(__res)                                        \
                   : "0"(SYS_##name), "gi"((long)(arg6)),                \
                   "gi"((long)(arg5)), "gi"((long)(arg4)),                \
                     "gi"((long)(arg3)), "q"((long)(arg2)),              \
                     "gi"((long)(arg1))                                  \
                     : "memory")

#define SYSCALL_SUCCESS_OR_SUICIDE(__res, err) \
    if ((unsigned long)(__res) >= (unsigned long)(-(128 + 1))) {        \
      fbt_suicide(err);                                                 \
    }

#define SYSCALL_SUCCESS_OR_SUICIDE_STR(__res, errstr) \
    if ((unsigned long)(__res) >= (unsigned long)(-(128 + 1))) {        \
      fbt_suicide_str(errstr);                                          \
    }

#endif  /* i386+ mode */

/* file management and I/O, declare specific system calls using the
   ugliness included from fbt_syscalls.h */
#if defined(DEBUG)
/* one possible implementation of fbt_suicide is an exit system call with an
   exit number, but this will not work if the stack is corrupted, so we just use
   a hlt instruction that causes a low level fault and terminates the
   program. sys_exit terminates the program and never returns, that's why we
   don't need to worry about saving the ebx register or return value. */
#define fbt_suicide(exitnr) __asm__ volatile("movl %0, %%eax\n"         \
                                             "movl %1, %%ebx\n"         \
                                             "int $0x80"                \
                                             : /* no return value */    \
                                             : "i"(SYS_exit),           \
                                               "i"((long)(exitnr))      \
                                             : "memory")
#else  /* NOT DEBUG */
#define fbt_suicide(exitnr) __asm__ volatile("hlt")
#endif  /* NOT DEBUG */

/* Implementation for socket system calls (ID 102) */
#define socketcall(id,__res) \
    __asm__ volatile ("movl %%ebx, %%edx ;" \
                      "movl %%eax, %%ebx ;" \
                      "movl $102, %%eax ;" \
                      "movl %%esp, %%ecx ; " \
                      ENTER_KERNEL \
                      "movl %%edx, %%ebx ; " \
                      : "=a"(__res) \
                      : "a" ((long)(id)) \
                      );
#define fbt_socketcall2(id,a,b,res) \
    __asm__ volatile( \
        "pushl %1 ; " \
        "pushl %0 ; " \
        : \
        : "g"((long)(a)), \
          "g"((long)(b)) \
        : "memory" \
          ); \
   socketcall((id), (res)); \
   __asm__ volatile( \
        "addl $8, %esp ; " \
   );

#define fbt_socketcall3(id,a,b,c,res) \
    __asm__ volatile( \
        "pushl %2 ; " \
        "pushl %1 ; " \
        "pushl %0 ; " \
        : \
        : "g"((long)(a)), \
          "g"((long)(b)), \
          "g"((long)(c)) \
        : "memory" \
          ); \
   socketcall((id), (res)); \
   __asm__ volatile( \
        "addl $12, %esp ; " \
   );

#endif  /* FBT_SYSCALLS_H */

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

#if defined(__x86_64__)
/* 64b syscall numbers needed here */
#define SYS_exit     60
#define SYS_write     1
#define SYS_open      2
#define SYS_close     3
#define SYS_lseek     8
#define SYS_mmap      9
#define SYS_munmap   11
#define SYS_mprotect 10

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

#else  /* i386+ mode */

#define I386_NR_SYSCALLS 341  /* total # of system calls */

#define SYS_exit           1  /* ensure that we close BT */
#define SYS_fork           2
#define SYS_read           3
#define SYS_write          4
#define SYS_open           5
#define SYS_close          6
#define SYS_creat          8
#define SYS_execve        11  /* redirected to auth_execve */
#define SYS_lseek         19
#define SYS_getpid        20
#define SYS_ptrace        26  /* deny */
#define SYS_signal        48  /* installs a new signal handler (deprecated) */
#define SYS_sigaction     67  /* installs a new signal handler */
#define SYS_readlink      85
#define SYS_mmap          90  /* redirected to auth_mmap */
#define SYS_munmap        91  /* TODO */
#define SYS_fstat        108  /* old fstat syscall, used by fbt_dso.c */
#define SYS_stat64       195  /* use new fstat syscall */
#define SYS_fstat64      197  /* use new fstat syscall */
#define SYS_sigreturn    119  /* we should never see this syscall */
#define SYS_clone        120  /* initializes a new thread */
#define SYS_mprotect     125  /* redirect to auth_mprotect */
#define SYS_rt_sigreturn 173  /* we should never see this syscall */
#define SYS_rt_sigaction 174  /* install a new signal handler */
#define SYS_rt_sigprocmask 175 /* change the list of currently blocked signals */
#define SYS_getcwd       183  /* get current wd */
#define SYS_mmap2        192  /* redirected to auth_mmap */
#define SYS_unused1      222  /* deny */
#define SYS_unused2      223  /* deny */
#define SYS_gettid       224  /* get thread identification (Linux-specific) */
#define SYS_futex        240
#define SYS_set_thread_area 243 /* set_thread_area */
#define SYS_get_thread_area 244 /* get_thread_area */
#define SYS_unused3      251  /* deny */
#define SYS_exit_group   252  /* ensure that we close BT */
#define SYS_sys_setaltroot 285  /* deny */

#define SYS_openat       295
#define SYS_faccessat    307
#define SYS_access        33

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

#define fbt_clone2(flags, stack, res) _syscall2(clone, flags, stack, res)
#define fbt_read(fd, buf, count, res) _syscall3(read, fd, buf, count, res)
#define fbt_write(fd, buf, count, res) _syscall3(write, fd, buf, count, res)
#define fbt_open(pathname, flags, mode, res) \
  _syscall3(open, pathname, flags, mode, res)
#define fbt_openat(fd, pathname, flags, mode, res) \
  _syscall4(openat, fd, pathname, flags,  mode, res)
#define fbt_faccessat(fd, file, flags, mode, res) \
  _syscall4(faccessat, fd, file, flags, mode, res)
#define fbt_access(path, mode, res) _syscall2(access, path, mode, res)
#define fbt_close(fd, res) _syscall1(close, fd, res)
#define fbt_lseek(fd, offset, whence, res) \
  _syscall3(lseek, fd, offset, whence, res)
#define fbt_getpid(res) _syscall(getpid, res)
#define fbt_gettid(res) _syscall(gettid, res)
#define fbt_fstat64(fd, stat, res) _syscall2(fstat64, fd, stat, res)
#define fbt_stat64(path, stat, res) _syscall2(stat64, path, stat, res)
#define fbt_fstat(fd, stat, res) _syscall2(fstat, fd, stat, res)
#define fbt_mmap(addr, length, prot, flags, fd, offset, res) \
  _syscall6(mmap, addr, length, prot, flags, fd, offset, res)
#define fbt_munmap(addr, length, res) _syscall2(munmap, addr, length, res)
#define fbt_mprotect(addr, len, prot, res) \
  _syscall3(mprotect, addr, len, prot, res)
#define fbt_signal(sig, handler, res) _syscall2(signal, sig, handler, res)
#define fbt_sigaction(sig, act, oldact, res) \
  _syscall3(sigaction, sig, act, oldact, res)
#define fbt_clone(flags, stack, ptid, newtls, ctid, res) \
  _syscall5(clone, flags, stack, ptid, newtls, ctid, res)
#define fbt_rt_sigaction(sig, act, oldact, res) \
  _syscall3(rt_sigaction, sig, act, oldact, res)
#define fbt_getcwd(str, len, res) _syscall2(getcwd, str, len, res)
#define fbt_readlink(src, dest, len, res) \
  _syscall3(readlink, src, dest, len, res)
#define fbt_set_thread_area(uinfo, res) \
  _syscall1(set_thread_area, uinfo, res)

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
   socketcall(id, res); \
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
   socketcall(id, res); \
   __asm__ volatile( \
        "addl $12, %esp ; " \
   );


#define fbt_socket(domain,type,protocol,res) fbt_socketcall3(1, domain,type,protocol,res)
#define fbt_bind(sockfd, fbt_addr, addrlen, res) fbt_socketcall3(2, sockfd, fbt_addr, addrlen, res)
#define fbt_listen(a, b, res) fbt_socketcall2(4, a, b, res)
#define fbt_accept(a, b, c, res) fbt_socketcall3(5, a, b, c, res)

#endif  /* FBT_SYSCALLS_H */

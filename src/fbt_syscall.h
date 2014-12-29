/**
 * @file fbt_syscall.h
 * Handles the authorization of system calls.
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

#ifndef FBT_SYSCALL_H
#define FBT_SYSCALL_H

#if defined(AUTHORIZE_SYSCALLS)
/* forward declare this struct */
struct thread_local_data;

/** maximum amount of system calls that are supported. if the syscall number is
   higher then we abort the program */
#define MAX_SYSCALLS_TABLE 512
  
/**
 * Initialize the system call tables used to authorize system calls.
 * Every system call passes through the thread local authorization table.
 * @param tld pointer to thread local data.
 */
void fbt_init_syscalls(struct thread_local_data *tld);
#endif  /* AUTHORIZE_SYSCALLS */

#if defined(HANDLE_SIGNALS)

// TODO: move exports into other file 
#ifdef __cplusplus
extern "C" {
#endif

// TODO:
struct fbt_siginfo;
void internal_sighandler(int signal, struct fbt_siginfo *siginfo, void *ucontext);
void sighandler(int signal, struct fbt_siginfo *siginfo, void *ucontext);
void fbt_bootstrap_thread(struct thread_local_data *tld);

struct dl_phdr_info;

#ifdef __cplusplus
}
#endif

#endif /* HANDLE_SIGNALS */

#endif  /* FBT_SYSCALL_H */

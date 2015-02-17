#ifndef ARM_FBT_SYSCALLS_IMPL_H
#define ARM_FBT_SYSCALLS_IMPL_H

#include <errno.h>
#include <sys/syscall.h>

// Only the newer Thumb/ARM EABI calling convetions are supported
#if defined(__thumb__) || defined(__ARM_EABI__)

// Macros to set input registers for system calls

#define _syscall_set_reg(reg_name, value) \
  register long _##reg_name __asm__(#reg_name)=(long)(value)

#define _syscall_set_code(name) _syscall_set_reg(r7, SYS_##name)

#define _syscall_reg_list(...) "r"(_r7), __VA_ARGS__

// After setting all registers, call the kernel to perform the syscall
#define _syscall_enter_kernel(...)     \
  __asm__ __volatile__(                \
      "swi 0"                          \
      : "=r"(_r0)                      \
      : _syscall_reg_list(__VA_ARGS__) \
      : "memory")

#define _syscall_return(type, res) \
  if ((unsigned long)(res) >= 0xfffff001u) { \
    errno = -(res); \
    res = -1; \
  } \
  return (type)(res);

// syscall macros for every number of parameters.
// These should still be wrapped inside functions.

#define _syscall_asm(_asmname, res) \
  _syscall_set_code(name); \
  _syscall_enter_kernel(); \
  res = _r0;

#define _syscall1_asm(name, arg0, res) \
  _syscall_set_code(name); \
  _syscall_set_reg(r0, arg0); \
  _syscall_enter_kernel("r"(_r0)); \
  res = _r0;

#define _syscall2_asm(name, arg0, arg1, res) \
  _syscall_set_code(name); \
  _syscall_set_reg(r0, arg0); \
  _syscall_set_reg(r1, arg1); \
  _syscall_enter_kernel("r"(_r0), "r"(_r1)); \
  res = _r0;

#define _syscall3_asm(name, arg0, arg1, arg2, res) \
  _syscall_set_code(name); \
  _syscall_set_reg(r0, arg0); \
  _syscall_set_reg(r1, arg1); \
  _syscall_set_reg(r2, arg2); \
  _syscall_enter_kernel("r"(_r0), "r"(_r1), "r"(_r2)); \
  res = _r0;

#define _syscall4_asm(name, arg0, arg1, arg2, arg3, res) \
  _syscall_set_code(name); \
  _syscall_set_reg(r0, arg0); \
  _syscall_set_reg(r1, arg1); \
  _syscall_set_reg(r2, arg2); \
  _syscall_set_reg(r3, arg3); \
  _syscall_enter_kernel("r"(_r0), "r"(_r1), "r"(_r2), "r"(_r3)); \
  res = _r0;

#define _syscall5_asm(name, arg0, arg1, arg2, arg3, arg4, res) \
  _syscall_set_code(name); \
  _syscall_set_reg(r0, arg0); \
  _syscall_set_reg(r1, arg1); \
  _syscall_set_reg(r2, arg2); \
  _syscall_set_reg(r3, arg3); \
  _syscall_set_reg(r4, arg4); \
  _syscall_enter_kernel("r"(_r0), "r"(_r1), "r"(_r2), "r"(_r3), "r"(_r4)); \
  res = _r0;

#define _syscall6_asm(name, arg0, arg1, arg2, arg3, arg4, arg5, res) \
  _syscall_set_code(name); \
  _syscall_set_reg(r0, arg0); \
  _syscall_set_reg(r1, arg1); \
  _syscall_set_reg(r2, arg2); \
  _syscall_set_reg(r3, arg3); \
  _syscall_set_reg(r4, arg4); \
  _syscall_set_reg(r5, arg5); \
  _syscall_enter_kernel("r"(_r0), "r"(_r1), "r"(_r2), "r"(_r3), "r"(_r4), "r"(_r5)); \
  res = _r0;


// Macros for defining functions wrapping system calls

#define _syscall_fn(type, name) \
static type fbt_syscall_##name() { \
  _syscall(name, res); \
  _syscall_return(type, res); \
}

#define _syscall1_fn(type, name, type0, arg0) \
static type fbt_syscall_##name(type0 arg0) { \
  long res; \
  _syscall1_asm(name, arg0, res); \
  _syscall_return(type, res); \
}

#define _syscall2_fn(type, name, type0, arg0, type1, arg1) \
static type fbt_syscall_##name(type0 arg0, type1 arg1) { \
  long res; \
  _syscall2_asm(name, arg0, arg1, res); \
  _syscall_return(type, res); \
}

#define _syscall3_fn(type, name, type0, arg0, type1, arg1, type2, arg2) \
static type fbt_syscall_##name(type0 arg0, type1 arg1, type2 arg2) { \
  long res; \
  _syscall3_asm(name, arg0, arg1, arg2, res); \
  _syscall_return(type, res); \
}

#define _syscall4_fn(type, name, type0, arg0, type1, arg1, type2, arg2, type3, arg3) \
static type fbt_syscall_##name(type0 arg0, type1 arg1, type2 arg2, type3 arg3) { \
  long res; \
  _syscall4_asm(name, arg0, arg1, arg2, arg3, res); \
  _syscall_return(type, res); \
}

#define _syscall5_fn(type, name, type0, arg0, type1, arg1, type2, arg2, type3, arg3, type4, arg4) \
static type fbt_syscall_##name(type0 arg0, type1 arg1, type2 arg2, type3 arg3, type4 arg4) { \
  long res; \
  _syscall5_asm(name, arg0, arg1, arg2, arg3, arg4, res); \
  _syscall_return(type, res); \
}

#define _syscall6_fn(type, name, type0, arg0, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5) \
static type fbt_syscall_##name(type0 arg0, type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5) { \
  long res; \
  _syscall6_asm(name, arg0, arg1, arg2, arg3, arg4, arg5, res); \
  _syscall_return(type, res); \
}

// Declare and define system call wrapper functions

// long fbt_syscall_clone(unsigned long flags, void *child_stack,
//                        void *ptid, void *ctid,
//                        struct pt_regs *regs)
_syscall5_fn(long, clone, unsigned long, flags, void*, child_stack,
                          void *, ptid, void*, ctid,
                          void*, regs)

// long fbt_syscall_read(int fd, void *buf, size_t count)
_syscall3_fn(long, read, int, fd, void*, buf, unsigned long, count)

// long fbt_syscall_write(int fd, const char *buf, unsigned long count)
_syscall3_fn(long, write, int, fd, const char*, buf, unsigned long, count)

// int fbt_syscall_open(const char *pathname, int flags, mode_t mode)
_syscall3_fn(int, open, const char*, pathname, int, flags, int, mode)

// int fbt_syscall_close(int fd)
_syscall1_fn(int, close, int, fd)

// int fbt_syscall_futex(int *uaddr, int op, int val,
//                       const struct timespec *timeout, int *uaddr2, int val3);
_syscall6_fn(int, futex, int *, uaddr, int, op, int, val,
             long *, timeout, int *, uaddr2, int, val3)

#ifdef SYS_mmap
// void *fbt_syscall_mmap(void *addr, size_t length, int prot, int flags,
//                        int fd, off_t offset)
_syscall6_fn(void *, mmap, void *, addr, unsigned long, length, int, prot, int, flags,
             int, fd, long, offset)
#endif  // SYS_mmap

#ifdef SYS_mmap2
// void *fbt_syscall_mmap2(void *addr, size_t length, int prot, int flags,
//                        int fd, off_t pgoffset)
_syscall6_fn(void *, mmap2, void *, addr, unsigned long, length, int, prot, int, flags,
             int, fd, long, pgoffset)
#endif  // SYS_mmap2

// int fbt_syscall_munmap(void *addr, size_t length)
_syscall2_fn(int, munmap, void*, addr, unsigned long, length)

// int fbt_syscall_sigaction(int signum, const struct sigaction *act,
//                           struct sigaction *oldact)
_syscall3_fn(int, sigaction, int, signum, void *, act, void *, oldact)

// long fbt_syscall_rt_sigaction(int sig, const struct sigaction *act,
//                               struct sigaction *oact);
_syscall3_fn(long, rt_sigaction, int, sig, void *, act,
             void *, oact)

#ifdef SYS_signal
// sighandler_t fbt_syscall_signal(int signum, sighandler_t handler)
_syscall2_fn(void *, signal, int, signum, void *, handler)
#endif  // SYS_signal


// fbt_suicide() is used in syscall error handling code
#define fbt_suicide(exitnr) \
    do { \
      long res; \
      _syscall1_asm(exit, exitnr, res); \
    } while(0)

#ifdef DEBUG
# define SYSCALL_SUCCESS_OR_SUICIDE(res, err) \
    if (((long)res) == -1) { \
      int _errno = errno; \
      fllprintf(1, "sycall failed with errno: %d\n", _errno); \
      fbt_suicide(err); \
    }
# define SYSCALL_SUCCESS_OR_SUICIDE_STR(res, errstr) \
    if (((long)res) == -1) { \
      int _errno = errno; \
      fllprintf(1, "sycall failed with errno: %d\n", _errno); \
      fbt_suicide_str(errstr); \
    }
#else
# define SYSCALL_SUCCESS_OR_SUICIDE(res, err) \
    if (((long)res) == -1) { \
      fbt_suicide(err); \
    }
# define SYSCALL_SUCCESS_OR_SUICIDE_STR(res, errstr) \
    if (((long)res) == -1) { \
      fbt_suicide_str(errstr); \
    }
#endif // DEBUG


// Macros used to define the public interface in generic/fbt_syscalls_impl.h

#define _syscall(name, res) \
    res = fbt_syscall_##name()
#define _syscall1(name, arg0, res) \
    res = fbt_syscall_##name(arg0)
#define _syscall2(name, arg0, arg1, res) \
    res = fbt_syscall_##name(arg0, arg1)
#define _syscall3(name, arg0, arg1, arg2, res) \
    res = fbt_syscall_##name(arg0, arg1, arg2)
#define _syscall4(name, arg0, arg1, arg2, arg3, res) \
    res = fbt_syscall_##name(arg0, arg1, arg2, arg3)
#define _syscall5(name, arg0, arg1, arg2, arg3, arg4, res) \
    res = fbt_syscall_##name(arg0, arg1, arg2, arg3, arg4)
#define _syscall6(name, arg0, arg1, arg2, arg3, arg4, arg5, res) \
    res = fbt_syscall_##name(arg0, arg1, arg2, arg3, arg4, arg5)

#else
# error "syscalls only work in the ARM_EABI"
#endif

#endif  /* ARM_FBT_SYSCALLS_IMPL_H */

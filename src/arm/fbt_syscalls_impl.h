#ifndef ARM_FBT_SYSCALLS_IMPL_H
#define ARM_FBT_SYSCALLS_IMPL_H

//#include <features.h>
#include <errno.h>
//#include <sys/types.h>
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
  if((unsigned long)(res) >= (unsigned long)(-125)) { \
    (*__errno_location()) = -(res); \
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

#define _syscal6_asm(name, arg0, arg1, arg2, arg3, arg4, arg5, res) \
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
  _syscall4(name, arg0, arg1, arg2, arg3, res); \
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
  _syscall5_asm(name, arg0, arg1, arg2, arg3, arg4, arg5, res); \
  _syscall_return(type, res); \
}

// Declare and define system call wrapper functions

// long fbt_syscall_clone(unsigned long flags, void *child_stack,
//                        void *ptid, void *ctid,
//                        struct pt_regs *regs)
_syscall5_fn(long, clone, unsigned long, flags, void*, child_stack,
                          void *, ptid, void*, ctid,
                          void*, regs)

// long read(int fd, void *buf, unsigned long count)
_syscall3_fn(long, read, int, fd, void*, buf, unsigned long, count)

// long fbt_syscall_write(int fd, const char *buf, unsigned long count)
_syscall3_fn(long, write, int, fd, const char*, buf, unsigned long, count)

// int fbt_syscall_open(const char *pathname, int flags, mode_t mode)
_syscall3_fn(int, open, const char*, pathname, int, flags, char *, mode)


// fbt_suicide() is used in syscall error handling code
#define fbt_suicide(exitnr) \
    do { \
      long res; \
      _syscall1_asm(exit, exitnr, res); \
    } while(0)

#define SYSCALL_SUCCESS_OR_SUICIDE(res, err) \
    if ((res) < 0) { fbt_suicide(err); }
#define SYSCALL_SUCCESS_OR_SUICIDE_STR(res, errstr) \
    if ((res) < 0) { fbt_suicide_str(errstr); }


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

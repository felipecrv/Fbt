#ifndef GENERIC_FBT_SYSCALLS_IMPL
#define GENERIC_FBT_SYSCALLS_IMPL

#ifdef __i386__
# include "../ia32/fbt_syscalls_impl.h"
#else
# include "../arm/fbt_syscalls_impl.h"
#endif

// total number of system calls (size of the syscall table)
#ifndef NR_syscalls
# ifdef __NR_syscalls
#  define NR_syscalls __NR_syscalls
# else
#  if defined(__i386__)
#   define NR_syscalls 356
#  elif defined(__x86_64__)
#   define NR_syscalls 319
#  elif defined(__arm__)
#   define NR_syscalls 388
#  endif
# endif
#endif

#define fbt_read(fd, buf, count, res) _syscall3(read, (fd), (buf), (count), (res))
#define fbt_write(fd, buf, count, res) _syscall3(write, (fd), (buf), (count), (res))
#define fbt_open(pathname, flags, mode, res) \
  _syscall3(open, (pathname), (flags), (mode), (res))
#define fbt_openat(fd, pathname, flags, mode, res) \
  _syscall4(openat, (fd), (pathname), (flags),  (mode), (res))
#define fbt_faccessat(fd, file, flags, mode, res) \
  _syscall4(faccessat, (fd), (file), (flags), (mode), (res))
#define fbt_access(path, mode, res) _syscall2(access, (path), (mode), (res))
#define fbt_close(fd, res) _syscall1(close, (fd), (res))
#define fbt_lseek(fd, offset, whence, res) \
  _syscall3(lseek, (fd), (offset), (whence), (res))
#define fbt_getpid(res) _syscall(getpid, (res))
#define fbt_gettid(res) _syscall(gettid, (res))
#define fbt_fstat64(fd, stat, res) _syscall2(fstat64, (fd), (stat), (res))
#define fbt_stat64(path, stat, res) _syscall2(stat64, (path), (stat), (res))
#define fbt_fstat(fd, stat, res) _syscall2(fstat, (fd), (stat), (res))

#ifdef SYS_mmap
# define fbt_mmap(addr, length, prot, flags, fd, offset, res) \
   _syscall6(mmap, (addr), (length), (prot), (flags), (fd), (offset), (res))
#endif  // SYS_mmap

#ifdef SYS_mmap2
#define fbt_mmap2(addr, length, prot, flags, fd, pgoffset, res) \
   _syscall6(mmap2, (addr), (length), (prot), (flags), (fd), (pgoffset), (res))
#endif  // SYS_mmap2

// If there's only mmap2, we define fbt_mmap() using fbt_mmap2()
#if !defined(SYS_mmap) && defined(SYS_mmap2)
# define fbt_mmap(addr, length, prot, flags, fd, offset, res) \
   assert((offset) / 4096 == 0); \
   fbt_mmap2((addr), (length), (prot), (flags), (fd), (offset) / 4096, (res))
#endif

#define fbt_munmap(addr, length, res) _syscall2(munmap, (addr), (length), (res))
#define fbt_mprotect(addr, len, prot, res) \
  _syscall3(mprotect, (addr), (len), (prot), (res))
#define fbt_signal(sig, handler, res) _syscall2(signal, (sig), (handler), (res))
#define fbt_sigaction(sig, act, oldact, res) \
  _syscall3(sigaction, (sig), (act), (oldact), (res))
#define fbt_clone(flags, stack, ptid, newtls, ctid, res) \
  _syscall5(clone, (flags), (stack), (ptid), (newtls), (ctid), (res))
#define fbt_rt_sigaction(sig, act, oldact, res) \
  _syscall3(rt_sigaction, (sig), (act), (oldact), (res))
#define fbt_getcwd(str, len, res) _syscall2(getcwd, (str), (len), (res))
#define fbt_readlink(src, dest, len, res) \
  _syscall3(readlink, (src), (dest), (len), (res))
#define fbt_set_thread_area(uinfo, res) \
  _syscall1(set_thread_area, (uinfo), (res))

#ifdef __i386__

#define fbt_socket(domain, type, protocol, res) \
  fbt_socketcall3(1, (domain), (type), (protocol), (res))
#define fbt_bind(sockfd, fbt_addr, addrlen, res) \
  fbt_socketcall3(2, (sockfd), (fbt_addr), (addrlen), (res))
#define fbt_listen(a, b, res) \
  fbt_socketcall2(4, (a), (b), (res))
#define fbt_accept(a, b, c, res) \
  fbt_socketcall3(5, (a), (b), (c), (res))

#endif  // __i386__

#endif  /* GENERIC_FBT_SYSCALLS_IMPL */

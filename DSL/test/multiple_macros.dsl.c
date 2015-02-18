#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <sys/mman.h>
#include <sys/types.h>

typedef void (*void_func)(void);
typedef int (*int_func)(void);

typedef unsigned long ulong_t;

#ifdef __i386__
typedef char Code;
#elif defined(__arm__)
// Code is 4-byte aligned on ARM
typedef long Code;
#endif

void a() {
    printf("a()\n");
}

void b() {
    printf("b()\n");
}

int main(int argc, char *argv[]) {
    Code *target = mmap(0, 4096, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    Code *begin_target = target;
    void_func f = (void_func)begin_target;
    
    // Start a shell
#ifdef __i386__
    BEGIN_ASM(target)
        call_abs {&a}
        call_abs {&b}
        ret
    END_ASM()
#endif

#ifdef __arm__
    BEGIN_ASM(target)
        // exit
        mov r7, #1
        mov r0, #222
        swi 0
    END_ASM()

    for (; begin_target < target; begin_target++) {
      printf("code: 0x%08x\n", *begin_target);
    }
#endif

    f();
    
    munmap(begin_target, 4096);    

    return 0;
}

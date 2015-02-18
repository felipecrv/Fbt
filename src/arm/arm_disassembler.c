#include <stdbool.h>

#include "../fbt_disassemble.h"
#include "../fbt_actions.h"

int main(int argc, char *argv[]) {
  uint32_t stream[] = {
    /* 83b8: */ 0xe92d4008, // push {r3, lr}  // _init
    /* 83bc: */ 0xeb00002c, // bl 8474 <call_weak_fn>
    /* 83c0: */ 0xe8bd8008, // pop  {r3, pc}
    /* 83c4: */ 0xe52de004, // push {lr}    ; (str lr, [sp, #-4]!)  // .plt
    /* 83c8: */ 0xe59fe004, // ldr  lr, [pc, #4]  ; 83d4 <_init+0x1c>
    /* 83cc: */ 0xe08fe00e, // add  lr, pc, lr
    /* 83d0: */ 0xe5bef008, // ldr  pc, [lr, #8]!
    /* 83d4: */ 0x00008b64, // .word  0x00008b64
    /* 83d8: */ 0xe28fc600, // add  ip, pc, #0, 12
    /* 83dc: */ 0xe28cca08, // add  ip, ip, #8, 20  ; 0x8000
    /* 83e0: */ 0xe5bcfb64, // ldr  pc, [ip, #2916]!  ; 0xb64
    /* 83e4: */ 0xe28fc600, // add  ip, pc, #0, 12
    /* 83e8: */ 0xe28cca08, // add  ip, ip, #8, 20  ; 0x8000
    /* 83ec: */ 0xe5bcfb5c, // ldr  pc, [ip, #2908]!  ; 0xb5c
    /* 83f0: */ 0xe28fc600, // add  ip, pc, #0, 12
    /* 83f4: */ 0xe28cca08, // add  ip, ip, #8, 20  ; 0x8000
    /* 83f8: */ 0xe5bcfb54, // ldr  pc, [ip, #2900]!  ; 0xb54
    /* 83fc: */ 0xe28fc600, // add  ip, pc, #0, 12
    /* 8400: */ 0xe28cca08, // add  ip, ip, #8, 20  ; 0x8000
    /* 8404: */ 0xe5bcfb4c, // ldr  pc, [ip, #2892]!  ; 0xb4c
    /* 8408: */ 0xe28fc600, // add  ip, pc, #0, 12
    /* 840c: */ 0xe28cca08, // add  ip, ip, #8, 20  ; 0x8000
    /* 8410: */ 0xe5bcfb44, // ldr  pc, [ip, #2884]!  ; 0xb44
    /* 8414: */ 0xe28fc600, // add  ip, pc, #0, 12
    /* 8418: */ 0xe28cca08, // add  ip, ip, #8, 20  ; 0x8000
    /* 841c: */ 0xe5bcfb3c, // ldr  pc, [ip, #2876]!  ; 0xb3c
    /* 8420: */ 0xe28fc600, // add  ip, pc, #0, 12
    /* 8424: */ 0xe28cca08, // add  ip, ip, #8, 20  ; 0x8000
    /* 8428: */ 0xe5bcfb34, // ldr  pc, [ip, #2868]!  ; 0xb34
    /* 842c: */ 0xe28fc600, // add  ip, pc, #0, 12
    /* 8430: */ 0xe28cca08, // add  ip, ip, #8, 20  ; 0x8000
    /* 8434: */ 0xe5bcfb2c, // ldr  pc, [ip, #2860]!  ; 0xb2c
    /* 8438: */ 0xe3a0b000, // mov  fp, #0  // _start
    /* 843c: */ 0xe3a0e000, // mov  lr, #0
    /* 8440: */ 0xe49d1004, // pop  {r1}    ; (ldr r1, [sp], #4)
    /* 8444: */ 0xe1a0200d, // mov  r2, sp
    /* 8448: */ 0xe52d2004, // push {r2}    ; (str r2, [sp, #-4]!)
    /* 844c: */ 0xe52d0004, // push {r0}    ; (str r0, [sp, #-4]!)
    /* 8450: */ 0xe59fc010, // ldr  ip, [pc, #16] ; 8468 <_start+0x30>
    /* 8454: */ 0xe52dc004, // push {ip}    ; (str ip, [sp, #-4]!)
    /* 8458: */ 0xe59f000c, // ldr  r0, [pc, #12] ; 846c <_start+0x34>
    /* 845c: */ 0xe59f300c, // ldr  r3, [pc, #12] ; 8470 <_start+0x38>
    /* 8460: */ 0xebffffe8, // bl 8408 <_init+0x50>
    /* 8464: */ 0xebfffff0, // bl 842c <_init+0x74>
    /* 8468: */ 0x00008da8, // .word  0x00008da8
    /* 846c: */ 0x00008718, // .word  0x00008718
    /* 8470: */ 0x00008d48, // .word  0x00008d48
    /* 8474: */ 0xe59f3014, // ldr  r3, [pc, #20] ; 8490 <call_weak_fn+0x1c> // call_weak_fn
    /* 8478: */ 0xe59f2014, // ldr  r2, [pc, #20] ; 8494 <call_weak_fn+0x20>
    /* 847c: */ 0xe08f3003, // add  r3, pc, r3
    /* 8480: */ 0xe7932002, // ldr  r2, [r3, r2]
    /* 8484: */ 0xe3520000, // cmp  r2, #0
    /* 8488: */ 0x012fff1e, // bxeq lr
    /* 848c: */ 0xeaffffe0, // b  8414 <_init+0x5c>
    /* 8490: */ 0x00008ab4, // .word  0x00008ab4
    /* 8494: */ 0x0000002c, // .word  0x0000002c
    /* 8498: */ 0xe59f301c, // ldr  r3, [pc, #28] ; 84bc <deregister_tm_clones+0x24> // deregister_tm_clones
    /* 849c: */ 0xe59f001c, // ldr  r0, [pc, #28] ; 84c0 <deregister_tm_clones+0x28>
    /* 84a0: */ 0xe0603003, // rsb  r3, r0, r3
    /* 84a4: */ 0xe3530006, // cmp  r3, #6
    /* 84a8: */ 0x912fff1e, // bxls lr
    /* 84ac: */ 0xe59f3010, // ldr  r3, [pc, #16] ; 84c4 <deregister_tm_clones+0x2c>
    /* 84b0: */ 0xe3530000, // cmp  r3, #0
    /* 84b4: */ 0x012fff1e, // bxeq lr
    /* 84b8: */ 0xe12fff13, // bx r3
    /* 84bc: */ 0x00010f73, // .word  0x00010f73
    /* 84c0: */ 0x00010f70, // .word  0x00010f70
    /* 84c4: */ 0x00000000, // .word  0x00000000
    /* 84c8: */ 0xe59f1024, // ldr  r1, [pc, #36] ; 84f4 <register_tm_clones+0x2c> // register_tm_clones
    /* 84cc: */ 0xe59f0024, // ldr  r0, [pc, #36] ; 84f8 <register_tm_clones+0x30>
    /* 84d0: */ 0xe0601001, // rsb  r1, r0, r1
    /* 84d4: */ 0xe1a01141, // asr  r1, r1, #2
    /* 84d8: */ 0xe0811fa1, // add  r1, r1, r1, lsr #31
    /* 84dc: */ 0xe1b010c1, // asrs r1, r1, #1
    /* 84e0: */ 0x012fff1e, // bxeq lr
    /* 84e4: */ 0xe59f3010, // ldr  r3, [pc, #16] ; 84fc <register_tm_clones+0x34>
    /* 84e8: */ 0xe3530000, // cmp  r3, #0
    /* 84ec: */ 0x012fff1e, // bxeq lr
    /* 84f0: */ 0xe12fff13, // bx r3
    /* 84f4: */ 0x00010f70, // .word  0x00010f70
    /* 84f8: */ 0x00010f70, // .word  0x00010f70
    /* 84fc: */ 0x00000000, // .word  0x00000000
    /* 8500: */ 0xe92d4010, // push {r4, lr}  // __do_global_dtors_aux
    /* 8504: */ 0xe59f4018, // ldr  r4, [pc, #24] ; 8524 <__do_global_dtors_aux+0x24>
    /* 8508: */ 0xe5d43000, // ldrb r3, [r4]
    /* 850c: */ 0xe3530000, // cmp  r3, #0
    /* 8510: */ 0x18bd8010, // popne  {r4, pc}
    /* 8514: */ 0xebffffdf, // bl 8498 <deregister_tm_clones>
    /* 8518: */ 0xe3a03001, // mov  r3, #1
    /* 851c: */ 0xe5c43000, // strb r3, [r4]
    /* 8520: */ 0xe8bd8010, // pop  {r4, pc}
    /* 8524: */ 0x00010f70, // .word  0x00010f70
    /* 8528: */ 0xe92d4008, // push {r3, lr}  // frame_dummy
    /* 852c: */ 0xe59f0024, // ldr  r0, [pc, #36] ; 8558 <frame_dummy+0x30>
    /* 8530: */ 0xe5903000, // ldr  r3, [r0]
    /* 8534: */ 0xe3530000, // cmp  r3, #0
    /* 8538: */ 0x1a000001, // bne  8544 <frame_dummy+0x1c>
    /* 853c: */ 0xe8bd4008, // pop  {r3, lr}
    /* 8540: */ 0xeaffffe0, // b  84c8 <register_tm_clones>
    /* 8544: */ 0xe59f3010, // ldr  r3, [pc, #16] ; 855c <frame_dummy+0x34>
    /* 8548: */ 0xe3530000, // cmp  r3, #0
    /* 854c: */ 0x0afffffa, // beq  853c <frame_dummy+0x14>
    /* 8550: */ 0xe12fff33, // blx  r3
    /* 8554: */ 0xeafffff8, // b  853c <frame_dummy+0x14>
    /* 8558: */ 0x00010e44, // .word  0x00010e44
    /* 855c: */ 0x00000000, // .word  0x00000000
    /* 8560: */ 0xe92d4800, // push {fp, lr} // NewTreeNode
    /* 8564: */ 0xe28db004, // add  fp, sp, #4
    /* 8568: */ 0xe24dd018, // sub  sp, sp, #24
    /* 856c: */ 0xe50b0010, // str  r0, [fp, #-16]
    /* 8570: */ 0xe50b1014, // str  r1, [fp, #-20]
    /* 8574: */ 0xe50b2018, // str  r2, [fp, #-24]
    /* 8578: */ 0xe3a0000c, // mov  r0, #12
    /* 857c: */ 0xebffff9e, // bl 83fc <_init+0x44>
    /* 8580: */ 0xe1a03000, // mov  r3, r0
    /* 8584: */ 0xe50b3008, // str  r3, [fp, #-8]
    /* 8588: */ 0xe51b3008, // ldr  r3, [fp, #-8]
    /* 858c: */ 0xe51b2010, // ldr  r2, [fp, #-16]
    /* 8590: */ 0xe5832000, // str  r2, [r3]
    /* 8594: */ 0xe51b3008, // ldr  r3, [fp, #-8]
    /* 8598: */ 0xe51b2014, // ldr  r2, [fp, #-20]
    /* 859c: */ 0xe5832004, // str  r2, [r3, #4]
    /* 85a0: */ 0xe51b3008, // ldr  r3, [fp, #-8]
    /* 85a4: */ 0xe51b2018, // ldr  r2, [fp, #-24]
    /* 85a8: */ 0xe5832008, // str  r2, [r3, #8]
    /* 85ac: */ 0xe51b3008, // ldr  r3, [fp, #-8]
    /* 85b0: */ 0xe1a00003, // mov  r0, r3
    /* 85b4: */ 0xe24bd004, // sub  sp, fp, #4
    /* 85b8: */ 0xe8bd8800, // pop  {fp, pc}
    /* 85bc: */ 0xe92d4810, // push {r4, fp, lr} // ItemCheck
    /* 85c0: */ 0xe28db008, // add  fp, sp, #8
    /* 85c4: */ 0xe24dd00c, // sub  sp, sp, #12
    /* 85c8: */ 0xe50b0010, // str  r0, [fp, #-16]
    /* 85cc: */ 0xe51b3010, // ldr  r3, [fp, #-16]
    /* 85d0: */ 0xe5933000, // ldr  r3, [r3]
    /* 85d4: */ 0xe3530000, // cmp  r3, #0
    /* 85d8: */ 0x1a000002, // bne  85e8 <ItemCheck+0x2c>
    /* 85dc: */ 0xe51b3010, // ldr  r3, [fp, #-16]
    /* 85e0: */ 0xe5933008, // ldr  r3, [r3, #8]
    /* 85e4: */ 0xea00000d, // b  8620 <ItemCheck+0x64>
    /* 85e8: */ 0xe51b3010, // ldr  r3, [fp, #-16]
    /* 85ec: */ 0xe5934008, // ldr  r4, [r3, #8]
    /* 85f0: */ 0xe51b3010, // ldr  r3, [fp, #-16]
    /* 85f4: */ 0xe5933000, // ldr  r3, [r3]
    /* 85f8: */ 0xe1a00003, // mov  r0, r3
    /* 85fc: */ 0xebffffee, // bl 85bc <ItemCheck>
    /* 8600: */ 0xe1a03000, // mov  r3, r0
    /* 8604: */ 0xe0844003, // add  r4, r4, r3
    /* 8608: */ 0xe51b3010, // ldr  r3, [fp, #-16]
    /* 860c: */ 0xe5933004, // ldr  r3, [r3, #4]
    /* 8610: */ 0xe1a00003, // mov  r0, r3
    /* 8614: */ 0xebffffe8, // bl 85bc <ItemCheck>
    /* 8618: */ 0xe1a03000, // mov  r3, r0
    /* 861c: */ 0xe0633004, // rsb  r3, r3, r4
    /* 8620: */ 0xe1a00003, // mov  r0, r3
    /* 8624: */ 0xe24bd008, // sub  sp, fp, #8
    /* 8628: */ 0xe8bd8810, // pop  {r4, fp, pc}
    /* 862c: */ 0xe92d4810, // push {r4, fp, lr}  // BottomUpTree
    /* 8630: */ 0xe28db008, // add  fp, sp, #8
    /* 8634: */ 0xe24dd00c, // sub  sp, sp, #12
    /* 8638: */ 0xe50b0010, // str  r0, [fp, #-16]
    /* 863c: */ 0xe50b1014, // str  r1, [fp, #-20]
    /* 8640: */ 0xe51b3014, // ldr  r3, [fp, #-20]
    /* 8644: */ 0xe3530000, // cmp  r3, #0
    /* 8648: */ 0x0a000016, // beq  86a8 <BottomUpTree+0x7c>
    /* 864c: */ 0xe51b3010, // ldr  r3, [fp, #-16]
    /* 8650: */ 0xe1a03083, // lsl  r3, r3, #1
    /* 8654: */ 0xe2432001, // sub  r2, r3, #1
    /* 8658: */ 0xe51b3014, // ldr  r3, [fp, #-20]
    /* 865c: */ 0xe2433001, // sub  r3, r3, #1
    /* 8660: */ 0xe1a00002, // mov  r0, r2
    /* 8664: */ 0xe1a01003, // mov  r1, r3
    /* 8668: */ 0xebffffef, // bl 862c <BottomUpTree>
    /* 866c: */ 0xe1a04000, // mov  r4, r0
    /* 8670: */ 0xe51b3010, // ldr  r3, [fp, #-16]
    /* 8674: */ 0xe1a02083, // lsl  r2, r3, #1
    /* 8678: */ 0xe51b3014, // ldr  r3, [fp, #-20]
    /* 867c: */ 0xe2433001, // sub  r3, r3, #1
    /* 8680: */ 0xe1a00002, // mov  r0, r2
    /* 8684: */ 0xe1a01003, // mov  r1, r3
    /* 8688: */ 0xebffffe7, // bl 862c <BottomUpTree>
    /* 868c: */ 0xe1a03000, // mov  r3, r0
    /* 8690: */ 0xe1a00004, // mov  r0, r4
    /* 8694: */ 0xe1a01003, // mov  r1, r3
    /* 8698: */ 0xe51b2010, // ldr  r2, [fp, #-16]
    /* 869c: */ 0xebffffaf, // bl 8560 <NewTreeNode>
    /* 86a0: */ 0xe1a03000, // mov  r3, r0
    /* 86a4: */ 0xea000004, // b  86bc <BottomUpTree+0x90>
    /* 86a8: */ 0xe3a00000, // mov  r0, #0
    /* 86ac: */ 0xe3a01000, // mov  r1, #0
    /* 86b0: */ 0xe51b2010, // ldr  r2, [fp, #-16]
    /* 86b4: */ 0xebffffa9, // bl 8560 <NewTreeNode>
    /* 86b8: */ 0xe1a03000, // mov  r3, r0
    /* 86bc: */ 0xe1a00003, // mov  r0, r3
    /* 86c0: */ 0xe24bd008, // sub  sp, fp, #8
    /* 86c4: */ 0xe8bd8810, // pop  {r4, fp, pc}
    /* 86c8: */ 0xe92d4800, // push {fp, lr}  // DeleteTree
    /* 86cc: */ 0xe28db004, // add  fp, sp, #4
    /* 86d0: */ 0xe24dd008, // sub  sp, sp, #8
    /* 86d4: */ 0xe50b0008, // str  r0, [fp, #-8]
    /* 86d8: */ 0xe51b3008, // ldr  r3, [fp, #-8]
    /* 86dc: */ 0xe5933000, // ldr  r3, [r3]
    /* 86e0: */ 0xe3530000, // cmp  r3, #0
    /* 86e4: */ 0x0a000007, // beq  8708 <DeleteTree+0x40>
    /* 86e8: */ 0xe51b3008, // ldr  r3, [fp, #-8]
    /* 86ec: */ 0xe5933000, // ldr  r3, [r3]
    /* 86f0: */ 0xe1a00003, // mov  r0, r3
    /* 86f4: */ 0xebfffff3, // bl 86c8 <DeleteTree>
    /* 86f8: */ 0xe51b3008, // ldr  r3, [fp, #-8]
    /* 86fc: */ 0xe5933004, // ldr  r3, [r3, #4]
    /* 8700: */ 0xe1a00003, // mov  r0, r3
    /* 8704: */ 0xebffffef, // bl 86c8 <DeleteTree>
    /* 8708: */ 0xe51b0008, // ldr  r0, [fp, #-8]
    /* 870c: */ 0xebffff34, // bl 83e4 <_init+0x2c>
    /* 8710: */ 0xe24bd004, // sub  sp, fp, #4
    /* 8714: */ 0xe8bd8800, // pop  {fp, pc}
    /* 8718: */ 0xe92d4810, // push {r4, fp, lr}  // main
    /* 871c: */ 0xe28db008, // add  fp, sp, #8
    /* 8720: */ 0xe24dd03c, // sub  sp, sp, #60 ; 0x3c
    /* 8724: */ 0xe50b0040, // str  r0, [fp, #-64]  ; 0x40
    /* 8728: */ 0xe50b1044, // str  r1, [fp, #-68]  ; 0x44
    /* 872c: */ 0xe51b3044, // ldr  r3, [fp, #-68]  ; 0x44
    /* 8730: */ 0xe2833004, // add  r3, r3, #4
    /* 8734: */ 0xe5933000, // ldr  r3, [r3]
    /* 8738: */ 0xe1a00003, // mov  r0, r3
    /* 873c: */ 0xebffff37, // bl 8420 <_init+0x68>
    /* 8740: */ 0xe1a03000, // mov  r3, r0
    /* 8744: */ 0xe50b3020, // str  r3, [fp, #-32]
    /* 8748: */ 0xe3a03004, // mov  r3, #4
    /* 874c: */ 0xe50b3024, // str  r3, [fp, #-36]  ; 0x24
    /* 8750: */ 0xe51b3024, // ldr  r3, [fp, #-36]  ; 0x24
    /* 8754: */ 0xe2832002, // add  r2, r3, #2
    /* 8758: */ 0xe51b3020, // ldr  r3, [fp, #-32]
    /* 875c: */ 0xe1520003, // cmp  r2, r3
    /* 8760: */ 0x9a000003, // bls  8774 <main+0x5c>
    /* 8764: */ 0xe51b3024, // ldr  r3, [fp, #-36]  ; 0x24
    /* 8768: */ 0xe2833002, // add  r3, r3, #2
    /* 876c: */ 0xe50b3014, // str  r3, [fp, #-20]
    /* 8770: */ 0xea000001, // b  877c <main+0x64>
    /* 8774: */ 0xe51b3020, // ldr  r3, [fp, #-32]
    /* 8778: */ 0xe50b3014, // str  r3, [fp, #-20]
    /* 877c: */ 0xe51b3014, // ldr  r3, [fp, #-20]
    /* 8780: */ 0xe2833001, // add  r3, r3, #1
    /* 8784: */ 0xe50b3028, // str  r3, [fp, #-40]  ; 0x28
    /* 8788: */ 0xe3a00000, // mov  r0, #0
    /* 878c: */ 0xe51b1028, // ldr  r1, [fp, #-40]  ; 0x28
    /* 8790: */ 0xebffffa5, // bl 862c <BottomUpTree>
    /* 8794: */ 0xe50b002c, // str  r0, [fp, #-44]  ; 0x2c
    /* 8798: */ 0xe51b002c, // ldr  r0, [fp, #-44]  ; 0x2c
    /* 879c: */ 0xebffff86, // bl 85bc <ItemCheck>
    /* 87a0: */ 0xe1a03000, // mov  r3, r0
    /* 87a4: */ 0xe59f017c, // ldr  r0, [pc, #380]  ; 8928 <main+0x210>
    /* 87a8: */ 0xe51b1028, // ldr  r1, [fp, #-40]  ; 0x28
    /* 87ac: */ 0xe1a02003, // mov  r2, r3
    /* 87b0: */ 0xebffff08, // bl 83d8 <_init+0x20>
    /* 87b4: */ 0xe51b002c, // ldr  r0, [fp, #-44]  ; 0x2c
    /* 87b8: */ 0xebffffc2, // bl 86c8 <DeleteTree>
    /* 87bc: */ 0xe3a00000, // mov  r0, #0
    /* 87c0: */ 0xe51b1014, // ldr  r1, [fp, #-20]
    /* 87c4: */ 0xebffff98, // bl 862c <BottomUpTree>
    /* 87c8: */ 0xe50b0030, // str  r0, [fp, #-48]  ; 0x30
    /* 87cc: */ 0xe51b3024, // ldr  r3, [fp, #-36]  ; 0x24
    /* 87d0: */ 0xe50b3010, // str  r3, [fp, #-16]
    /* 87d4: */ 0xea000044, // b  88ec <main+0x1d4>
    /* 87d8: */ 0xe51b2014, // ldr  r2, [fp, #-20]
    /* 87dc: */ 0xe51b3010, // ldr  r3, [fp, #-16]
    /* 87e0: */ 0xe0632002, // rsb  r2, r3, r2
    /* 87e4: */ 0xe51b3024, // ldr  r3, [fp, #-36]  ; 0x24
    /* 87e8: */ 0xe0823003, // add  r3, r2, r3
    /* 87ec: */ 0xe1a00003, // mov  r0, r3
    /* 87f0: */ 0xeb0000fd, // bl 8bec <__aeabi_ui2d>
    /* 87f4: */ 0xe1a03000, // mov  r3, r0
    /* 87f8: */ 0xe1a04001, // mov  r4, r1
    /* 87fc: */ 0xe3a00000, // mov  r0, #0
    /* 8800: */ 0xe3a01101, // mov  r1, #1073741824 ; 0x40000000
    /* 8804: */ 0xe1a02003, // mov  r2, r3
    /* 8808: */ 0xe1a03004, // mov  r3, r4
    /* 880c: */ 0xebfffef7, // bl 83f0 <_init+0x38>
    /* 8810: */ 0xe1a03000, // mov  r3, r0
    /* 8814: */ 0xe1a04001, // mov  r4, r1
    /* 8818: */ 0xe1a00003, // mov  r0, r3
    /* 881c: */ 0xe1a01004, // mov  r1, r4
    /* 8820: */ 0xeb000131, // bl 8cec <__aeabi_d2iz>
    /* 8824: */ 0xe1a03000, // mov  r3, r0
    /* 8828: */ 0xe50b3034, // str  r3, [fp, #-52]  ; 0x34
    /* 882c: */ 0xe3a03000, // mov  r3, #0
    /* 8830: */ 0xe50b301c, // str  r3, [fp, #-28]
    /* 8834: */ 0xe3a03001, // mov  r3, #1
    /* 8838: */ 0xe50b3018, // str  r3, [fp, #-24]
    /* 883c: */ 0xea00001c, // b  88b4 <main+0x19c>
    /* 8840: */ 0xe51b0018, // ldr  r0, [fp, #-24]
    /* 8844: */ 0xe51b1010, // ldr  r1, [fp, #-16]
    /* 8848: */ 0xebffff77, // bl 862c <BottomUpTree>
    /* 884c: */ 0xe50b0038, // str  r0, [fp, #-56]  ; 0x38
    /* 8850: */ 0xe51b0038, // ldr  r0, [fp, #-56]  ; 0x38
    /* 8854: */ 0xebffff58, // bl 85bc <ItemCheck>
    /* 8858: */ 0xe1a02000, // mov  r2, r0
    /* 885c: */ 0xe51b301c, // ldr  r3, [fp, #-28]
    /* 8860: */ 0xe0833002, // add  r3, r3, r2
    /* 8864: */ 0xe50b301c, // str  r3, [fp, #-28]
    /* 8868: */ 0xe51b0038, // ldr  r0, [fp, #-56]  ; 0x38
    /* 886c: */ 0xebffff95, // bl 86c8 <DeleteTree>
    /* 8870: */ 0xe51b3018, // ldr  r3, [fp, #-24]
    /* 8874: */ 0xe2633000, // rsb  r3, r3, #0
    /* 8878: */ 0xe1a00003, // mov  r0, r3
    /* 887c: */ 0xe51b1010, // ldr  r1, [fp, #-16]
    /* 8880: */ 0xebffff69, // bl 862c <BottomUpTree>
    /* 8884: */ 0xe50b0038, // str  r0, [fp, #-56]  ; 0x38
    /* 8888: */ 0xe51b0038, // ldr  r0, [fp, #-56]  ; 0x38
    /* 888c: */ 0xebffff4a, // bl 85bc <ItemCheck>
    /* 8890: */ 0xe1a02000, // mov  r2, r0
    /* 8894: */ 0xe51b301c, // ldr  r3, [fp, #-28]
    /* 8898: */ 0xe0833002, // add  r3, r3, r2
    /* 889c: */ 0xe50b301c, // str  r3, [fp, #-28]
    /* 88a0: */ 0xe51b0038, // ldr  r0, [fp, #-56]  ; 0x38
    /* 88a4: */ 0xebffff87, // bl 86c8 <DeleteTree>
    /* 88a8: */ 0xe51b3018, // ldr  r3, [fp, #-24]
    /* 88ac: */ 0xe2833001, // add  r3, r3, #1
    /* 88b0: */ 0xe50b3018, // str  r3, [fp, #-24]
    /* 88b4: */ 0xe51b2018, // ldr  r2, [fp, #-24]
    /* 88b8: */ 0xe51b3034, // ldr  r3, [fp, #-52]  ; 0x34
    /* 88bc: */ 0xe1520003, // cmp  r2, r3
    /* 88c0: */ 0xdaffffde, // ble  8840 <main+0x128>
    /* 88c4: */ 0xe51b3034, // ldr  r3, [fp, #-52]  ; 0x34
    /* 88c8: */ 0xe1a03083, // lsl  r3, r3, #1
    /* 88cc: */ 0xe59f0058, // ldr  r0, [pc, #88] ; 892c <main+0x214>
    /* 88d0: */ 0xe1a01003, // mov  r1, r3
    /* 88d4: */ 0xe51b2010, // ldr  r2, [fp, #-16]
    /* 88d8: */ 0xe51b301c, // ldr  r3, [fp, #-28]
    /* 88dc: */ 0xebfffebd, // bl 83d8 <_init+0x20>
    /* 88e0: */ 0xe51b3010, // ldr  r3, [fp, #-16]
    /* 88e4: */ 0xe2833002, // add  r3, r3, #2
    /* 88e8: */ 0xe50b3010, // str  r3, [fp, #-16]
    /* 88ec: */ 0xe51b2010, // ldr  r2, [fp, #-16]
    /* 88f0: */ 0xe51b3014, // ldr  r3, [fp, #-20]
    /* 88f4: */ 0xe1520003, // cmp  r2, r3
    /* 88f8: */ 0x9affffb6, // bls  87d8 <main+0xc0>
    /* 88fc: */ 0xe51b0030, // ldr  r0, [fp, #-48]  ; 0x30
    /* 8900: */ 0xebffff2d, // bl 85bc <ItemCheck>
    /* 8904: */ 0xe1a03000, // mov  r3, r0
    /* 8908: */ 0xe59f0020, // ldr  r0, [pc, #32] ; 8930 <main+0x218>
    /* 890c: */ 0xe51b1014, // ldr  r1, [fp, #-20]
    /* 8910: */ 0xe1a02003, // mov  r2, r3
    /* 8914: */ 0xebfffeaf, // bl 83d8 <_init+0x20>
    /* 8918: */ 0xe3a03000, // mov  r3, #0
    /* 891c: */ 0xe1a00003, // mov  r0, r3
    /* 8920: */ 0xe24bd008, // sub  sp, fp, #8
    /* 8924: */ 0xe8bd8810, // pop  {r4, fp, pc}
    /* 8928: */ 0x00008db8, // .word  0x00008db8
    /* 892c: */ 0x00008de0, // .word  0x00008de0
    /* 8930: */ 0x00008e04, // .word  0x00008e04
    /* 8934: */ 0xe2211102, // eor  r1, r1, #-2147483648  ; 0x80000000  // __aeabi_drsub
    /* 8938: */ 0xea000000, // b  8940 <__adddf3>
    /* 893c: */ 0xe2233102, // eor  r3, r3, #-2147483648  ; 0x80000000  // __aeabi_dsub
    /* 8940: */ 0xe92d4030, // push {r4, r5, lr}  // __adddf3
    /* 8944: */ 0xe1a04081, // lsl  r4, r1, #1
    /* 8948: */ 0xe1a05083, // lsl  r5, r3, #1
    /* 894c: */ 0xe1340005, // teq  r4, r5
    /* 8950: */ 0x01300002, // teqeq  r0, r2
    /* 8954: */ 0x1194c000, // orrsne ip, r4, r0
    /* 8958: */ 0x1195c002, // orrsne ip, r5, r2
    /* 895c: */ 0x11f0cac4, // mvnsne ip, r4, asr #21
    /* 8960: */ 0x11f0cac5, // mvnsne ip, r5, asr #21
    /* 8964: */ 0x0a000079, // beq  8b50 <__adddf3+0x210>
    /* 8968: */ 0xe1a04aa4, // lsr  r4, r4, #21
    /* 896c: */ 0xe0745aa5, // rsbs r5, r4, r5, lsr #21
    /* 8970: */ 0xb2655000, // rsblt  r5, r5, #0
    /* 8974: */ 0xda000006, // ble  8994 <__adddf3+0x54>
    /* 8978: */ 0xe0844005, // add  r4, r4, r5
    /* 897c: */ 0xe0202002, // eor  r2, r0, r2
    /* 8980: */ 0xe0213003, // eor  r3, r1, r3
    /* 8984: */ 0xe0220000, // eor  r0, r2, r0
    /* 8988: */ 0xe0231001, // eor  r1, r3, r1
    /* 898c: */ 0xe0202002, // eor  r2, r0, r2
    /* 8990: */ 0xe0213003, // eor  r3, r1, r3
    /* 8994: */ 0xe3550036, // cmp  r5, #54 ; 0x36
    /* 8998: */ 0x88bd8030, // pophi  {r4, r5, pc}
    /* 899c: */ 0xe3110102, // tst  r1, #-2147483648  ; 0x80000000
    /* 89a0: */ 0xe1a01601, // lsl  r1, r1, #12
    /* 89a4: */ 0xe3a0c601, // mov  ip, #1048576  ; 0x100000
    /* 89a8: */ 0xe18c1621, // orr  r1, ip, r1, lsr #12
    /* 89ac: */ 0x0a000001, // beq  89b8 <__adddf3+0x78>
    /* 89b0: */ 0xe2700000, // rsbs r0, r0, #0
    /* 89b4: */ 0xe2e11000, // rsc  r1, r1, #0
    /* 89b8: */ 0xe3130102, // tst  r3, #-2147483648  ; 0x80000000
    /* 89bc: */ 0xe1a03603, // lsl  r3, r3, #12
    /* 89c0: */ 0xe18c3623, // orr  r3, ip, r3, lsr #12
    /* 89c4: */ 0x0a000001, // beq  89d0 <__adddf3+0x90>
    /* 89c8: */ 0xe2722000, // rsbs r2, r2, #0
    /* 89cc: */ 0xe2e33000, // rsc  r3, r3, #0
    /* 89d0: */ 0xe1340005, // teq  r4, r5
    /* 89d4: */ 0x0a000057, // beq  8b38 <__adddf3+0x1f8>
    /* 89d8: */ 0xe2444001, // sub  r4, r4, #1
    /* 89dc: */ 0xe275e020, // rsbs lr, r5, #32
    /* 89e0: */ 0xba000005, // blt  89fc <__adddf3+0xbc>
    /* 89e4: */ 0xe1a0ce12, // lsl  ip, r2, lr
    /* 89e8: */ 0xe0900532, // adds r0, r0, r2, lsr r5
    /* 89ec: */ 0xe2a11000, // adc  r1, r1, #0
    /* 89f0: */ 0xe0900e13, // adds r0, r0, r3, lsl lr
    /* 89f4: */ 0xe0b11553, // adcs r1, r1, r3, asr r5
    /* 89f8: */ 0xea000006, // b  8a18 <__adddf3+0xd8>
    /* 89fc: */ 0xe2455020, // sub  r5, r5, #32
    /* 8a00: */ 0xe28ee020, // add  lr, lr, #32
    /* 8a04: */ 0xe3520001, // cmp  r2, #1
    /* 8a08: */ 0xe1a0ce13, // lsl  ip, r3, lr
    /* 8a0c: */ 0x238cc002, // orrcs  ip, ip, #2
    /* 8a10: */ 0xe0900553, // adds r0, r0, r3, asr r5
    /* 8a14: */ 0xe0b11fc3, // adcs r1, r1, r3, asr #31
    /* 8a18: */ 0xe2015102, // and  r5, r1, #-2147483648  ; 0x80000000
    /* 8a1c: */ 0x5a000002, // bpl  8a2c <__adddf3+0xec>
    /* 8a20: */ 0xe27cc000, // rsbs ip, ip, #0
    /* 8a24: */ 0xe2f00000, // rscs r0, r0, #0
    /* 8a28: */ 0xe2e11000, // rsc  r1, r1, #0
    /* 8a2c: */ 0xe3510601, // cmp  r1, #1048576  ; 0x100000
    /* 8a30: */ 0x3a00000e, // bcc  8a70 <__adddf3+0x130>
    /* 8a34: */ 0xe3510602, // cmp  r1, #2097152  ; 0x200000
    /* 8a38: */ 0x3a000006, // bcc  8a58 <__adddf3+0x118>
    /* 8a3c: */ 0xe1b010a1, // lsrs r1, r1, #1
    /* 8a40: */ 0xe1b00060, // rrxs r0, r0
    /* 8a44: */ 0xe1a0c06c, // rrx  ip, ip
    /* 8a48: */ 0xe2844001, // add  r4, r4, #1
    /* 8a4c: */ 0xe1a02a84, // lsl  r2, r4, #21
    /* 8a50: */ 0xe3720501, // cmn  r2, #4194304  ; 0x400000
    /* 8a54: */ 0x2a000055, // bcs  8bb0 <__adddf3+0x270>
    /* 8a58: */ 0xe35c0102, // cmp  ip, #-2147483648  ; 0x80000000
    /* 8a5c: */ 0x01b0c0a0, // lsrseq ip, r0, #1
    /* 8a60: */ 0xe2b00000, // adcs r0, r0, #0
    /* 8a64: */ 0xe0a11a04, // adc  r1, r1, r4, lsl #20
    /* 8a68: */ 0xe1811005, // orr  r1, r1, r5
    /* 8a6c: */ 0xe8bd8030, // pop  {r4, r5, pc}
    /* 8a70: */ 0xe1b0c08c, // lsls ip, ip, #1
    /* 8a74: */ 0xe0b00000, // adcs r0, r0, r0
    /* 8a78: */ 0xe0a11001, // adc  r1, r1, r1
    /* 8a7c: */ 0xe3110601, // tst  r1, #1048576  ; 0x100000
    /* 8a80: */ 0xe2444001, // sub  r4, r4, #1
    /* 8a84: */ 0x1afffff3, // bne  8a58 <__adddf3+0x118>
    /* 8a88: */ 0xe3310000, // teq  r1, #0
    /* 8a8c: */ 0x01a01000, // moveq  r1, r0
    /* 8a90: */ 0x03a00000, // moveq  r0, #0
    /* 8a94: */ 0xe16f3f11, // clz  r3, r1
    /* 8a98: */ 0x02833020, // addeq  r3, r3, #32
    /* 8a9c: */ 0xe243300b, // sub  r3, r3, #11
    /* 8aa0: */ 0xe2532020, // subs r2, r3, #32
    /* 8aa4: */ 0xaa000007, // bge  8ac8 <__adddf3+0x188>
    /* 8aa8: */ 0xe292200c, // adds r2, r2, #12
    /* 8aac: */ 0xda000004, // ble  8ac4 <__adddf3+0x184>
    /* 8ab0: */ 0xe282c014, // add  ip, r2, #20
    /* 8ab4: */ 0xe262200c, // rsb  r2, r2, #12
    /* 8ab8: */ 0xe1a00c11, // lsl  r0, r1, ip
    /* 8abc: */ 0xe1a01231, // lsr  r1, r1, r2
    /* 8ac0: */ 0xea000004, // b  8ad8 <__adddf3+0x198>
    /* 8ac4: */ 0xe2822014, // add  r2, r2, #20
    /* 8ac8: */ 0xd262c020, // rsble  ip, r2, #32
    /* 8acc: */ 0xe1a01211, // lsl  r1, r1, r2
    /* 8ad0: */ 0xd1811c30, // orrle  r1, r1, r0, lsr ip
    /* 8ad4: */ 0xd1a00210, // lslle  r0, r0, r2
    /* 8ad8: */ 0xe0544003, // subs r4, r4, r3
    /* 8adc: */ 0xa0811a04, // addge  r1, r1, r4, lsl #20
    /* 8ae0: */ 0xa1811005, // orrge  r1, r1, r5
    /* 8ae4: */ 0xa8bd8030, // popge  {r4, r5, pc}
    /* 8ae8: */ 0xe1e04004, // mvn  r4, r4
    /* 8aec: */ 0xe254401f, // subs r4, r4, #31
    /* 8af0: */ 0xaa00000d, // bge  8b2c <__adddf3+0x1ec>
    /* 8af4: */ 0xe294400c, // adds r4, r4, #12
    /* 8af8: */ 0xca000005, // bgt  8b14 <__adddf3+0x1d4>
    /* 8afc: */ 0xe2844014, // add  r4, r4, #20
    /* 8b00: */ 0xe2642020, // rsb  r2, r4, #32
    /* 8b04: */ 0xe1a00430, // lsr  r0, r0, r4
    /* 8b08: */ 0xe1800211, // orr  r0, r0, r1, lsl r2
    /* 8b0c: */ 0xe1851431, // orr  r1, r5, r1, lsr r4
    /* 8b10: */ 0xe8bd8030, // pop  {r4, r5, pc}
    /* 8b14: */ 0xe264400c, // rsb  r4, r4, #12
    /* 8b18: */ 0xe2642020, // rsb  r2, r4, #32
    /* 8b1c: */ 0xe1a00230, // lsr  r0, r0, r2
    /* 8b20: */ 0xe1800411, // orr  r0, r0, r1, lsl r4
    /* 8b24: */ 0xe1a01005, // mov  r1, r5
    /* 8b28: */ 0xe8bd8030, // pop  {r4, r5, pc}
    /* 8b2c: */ 0xe1a00431, // lsr  r0, r1, r4
    /* 8b30: */ 0xe1a01005, // mov  r1, r5
    /* 8b34: */ 0xe8bd8030, // pop  {r4, r5, pc}
    /* 8b38: */ 0xe3340000, // teq  r4, #0
    /* 8b3c: */ 0xe2233601, // eor  r3, r3, #1048576  ; 0x100000
    /* 8b40: */ 0x02211601, // eoreq  r1, r1, #1048576  ; 0x100000
    /* 8b44: */ 0x02844001, // addeq  r4, r4, #1
    /* 8b48: */ 0x12455001, // subne  r5, r5, #1
    /* 8b4c: */ 0xeaffffa1, // b  89d8 <__adddf3+0x98>
    /* 8b50: */ 0xe1f0cac4, // mvns ip, r4, asr #21
    /* 8b54: */ 0x11f0cac5, // mvnsne ip, r5, asr #21
    /* 8b58: */ 0x0a000018, // beq  8bc0 <__adddf3+0x280>
    /* 8b5c: */ 0xe1340005, // teq  r4, r5
    /* 8b60: */ 0x01300002, // teqeq  r0, r2
    /* 8b64: */ 0x0a000003, // beq  8b78 <__adddf3+0x238>
    /* 8b68: */ 0xe194c000, // orrs ip, r4, r0
    /* 8b6c: */ 0x01a01003, // moveq  r1, r3
    /* 8b70: */ 0x01a00002, // moveq  r0, r2
    /* 8b74: */ 0xe8bd8030, // pop  {r4, r5, pc}
    /* 8b78: */ 0xe1310003, // teq  r1, r3
    /* 8b7c: */ 0x13a01000, // movne  r1, #0
    /* 8b80: */ 0x13a00000, // movne  r0, #0
    /* 8b84: */ 0x18bd8030, // popne  {r4, r5, pc}
    /* 8b88: */ 0xe1b0caa4, // lsrs ip, r4, #21
    /* 8b8c: */ 0x1a000003, // bne  8ba0 <__adddf3+0x260>
    /* 8b90: */ 0xe1b00080, // lsls r0, r0, #1
    /* 8b94: */ 0xe0b11001, // adcs r1, r1, r1
    /* 8b98: */ 0x23811102, // orrcs  r1, r1, #-2147483648  ; 0x80000000
    /* 8b9c: */ 0xe8bd8030, // pop  {r4, r5, pc}
    /* 8ba0: */ 0xe2944501, // adds r4, r4, #4194304  ; 0x400000
    /* 8ba4: */ 0x32811601, // addcc  r1, r1, #1048576  ; 0x100000
    /* 8ba8: */ 0x38bd8030, // popcc  {r4, r5, pc}
    /* 8bac: */ 0xe2015102, // and  r5, r1, #-2147483648  ; 0x80000000
    /* 8bb0: */ 0xe385147f, // orr  r1, r5, #2130706432 ; 0x7f000000
    /* 8bb4: */ 0xe381160f, // orr  r1, r1, #15728640 ; 0xf00000
    /* 8bb8: */ 0xe3a00000, // mov  r0, #0
    /* 8bbc: */ 0xe8bd8030, // pop  {r4, r5, pc}
    /* 8bc0: */ 0xe1f0cac4, // mvns ip, r4, asr #21
    /* 8bc4: */ 0x11a01003, // movne  r1, r3
    /* 8bc8: */ 0x11a00002, // movne  r0, r2
    /* 8bcc: */ 0x01f0cac5, // mvnseq ip, r5, asr #21
    /* 8bd0: */ 0x11a03001, // movne  r3, r1
    /* 8bd4: */ 0x11a02000, // movne  r2, r0
    /* 8bd8: */ 0xe1904601, // orrs r4, r0, r1, lsl #12
    /* 8bdc: */ 0x01925603, // orrseq r5, r2, r3, lsl #12
    /* 8be0: */ 0x01310003, // teqeq  r1, r3
    /* 8be4: */ 0x13811702, // orrne  r1, r1, #524288 ; 0x80000
    /* 8be8: */ 0xe8bd8030, // pop  {r4, r5, pc}
    /* 8bec: */ 0xe3300000, // teq  r0, #0  // __aeabi_ui2d
    /* 8bf0: */ 0x03a01000, // moveq  r1, #0
    /* 8bf4: */ 0x012fff1e, // bxeq lr
    /* 8bf8: */ 0xe92d4030, // push {r4, r5, lr}
    /* 8bfc: */ 0xe3a04b01, // mov  r4, #1024 ; 0x400
    /* 8c00: */ 0xe2844032, // add  r4, r4, #50 ; 0x32
    /* 8c04: */ 0xe3a05000, // mov  r5, #0
    /* 8c08: */ 0xe3a01000, // mov  r1, #0
    /* 8c0c: */ 0xeaffff9d, // b  8a88 <__adddf3+0x148>
    /* 8c10: */ 0xe3300000, // teq  r0, #0  // __aeabi_i2d
    /* 8c14: */ 0x03a01000, // moveq  r1, #0
    /* 8c18: */ 0x012fff1e, // bxeq lr
    /* 8c1c: */ 0xe92d4030, // push {r4, r5, lr}
    /* 8c20: */ 0xe3a04b01, // mov  r4, #1024 ; 0x400
    /* 8c24: */ 0xe2844032, // add  r4, r4, #50 ; 0x32
    /* 8c28: */ 0xe2105102, // ands r5, r0, #-2147483648  ; 0x80000000
    /* 8c2c: */ 0x42600000, // rsbmi  r0, r0, #0
    /* 8c30: */ 0xe3a01000, // mov  r1, #0
    /* 8c34: */ 0xeaffff93, // b  8a88 <__adddf3+0x148>
    /* 8c38: */ 0xe1b02080, // lsls r2, r0, #1  // __aeabi_f2d
    /* 8c3c: */ 0xe1a011c2, // asr  r1, r2, #3
    /* 8c40: */ 0xe1a01061, // rrx  r1, r1
    /* 8c44: */ 0xe1a00e02, // lsl  r0, r2, #28
    /* 8c48: */ 0x121234ff, // andsne r3, r2, #-16777216  ; 0xff000000
    /* 8c4c: */ 0x133304ff, // teqne  r3, #-16777216  ; 0xff000000
    /* 8c50: */ 0x1221130e, // eorne  r1, r1, #939524096  ; 0x38000000
    /* 8c54: */ 0x112fff1e, // bxne lr
    /* 8c58: */ 0xe3320000, // teq  r2, #0
    /* 8c5c: */ 0x133304ff, // teqne  r3, #-16777216  ; 0xff000000
    /* 8c60: */ 0x012fff1e, // bxeq lr
    /* 8c64: */ 0xe92d4030, // push {r4, r5, lr}
    /* 8c68: */ 0xe3a04d0e, // mov  r4, #896  ; 0x380
    /* 8c6c: */ 0xe2015102, // and  r5, r1, #-2147483648  ; 0x80000000
    /* 8c70: */ 0xe3c11102, // bic  r1, r1, #-2147483648  ; 0x80000000
    /* 8c74: */ 0xeaffff83, // b  8a88 <__adddf3+0x148>
    /* 8c78: */ 0xe1902001, // orrs r2, r0, r1  // __aeabi_ul2d
    /* 8c7c: */ 0x012fff1e, // bxeq lr
    /* 8c80: */ 0xe92d4030, // push {r4, r5, lr}
    /* 8c84: */ 0xe3a05000, // mov  r5, #0
    /* 8c88: */ 0xea000006, // b  8ca8 <__aeabi_l2d+0x1c>
    /* 8c8c: */ 0xe1902001, // orrs r2, r0, r1  // __aeabi_l2d
    /* 8c90: */ 0x012fff1e, // bxeq lr
    /* 8c94: */ 0xe92d4030, // push {r4, r5, lr}
    /* 8c98: */ 0xe2115102, // ands r5, r1, #-2147483648  ; 0x80000000
    /* 8c9c: */ 0x5a000001, // bpl  8ca8 <__aeabi_l2d+0x1c>
    /* 8ca0: */ 0xe2700000, // rsbs r0, r0, #0
    /* 8ca4: */ 0xe2e11000, // rsc  r1, r1, #0
    /* 8ca8: */ 0xe3a04b01, // mov  r4, #1024 ; 0x400
    /* 8cac: */ 0xe2844032, // add  r4, r4, #50 ; 0x32
    /* 8cb0: */ 0xe1b0cb21, // lsrs ip, r1, #22
    /* 8cb4: */ 0x0affff5c, // beq  8a2c <__adddf3+0xec>
    /* 8cb8: */ 0xe3a02003, // mov  r2, #3
    /* 8cbc: */ 0xe1b0c1ac, // lsrs ip, ip, #3
    /* 8cc0: */ 0x12822003, // addne  r2, r2, #3
    /* 8cc4: */ 0xe1b0c1ac, // lsrs ip, ip, #3
    /* 8cc8: */ 0x12822003, // addne  r2, r2, #3
    /* 8ccc: */ 0xe08221ac, // add  r2, r2, ip, lsr #3
    /* 8cd0: */ 0xe2623020, // rsb  r3, r2, #32
    /* 8cd4: */ 0xe1a0c310, // lsl  ip, r0, r3
    /* 8cd8: */ 0xe1a00230, // lsr  r0, r0, r2
    /* 8cdc: */ 0xe1800311, // orr  r0, r0, r1, lsl r3
    /* 8ce0: */ 0xe1a01231, // lsr  r1, r1, r2
    /* 8ce4: */ 0xe0844002, // add  r4, r4, r2
    /* 8ce8: */ 0xeaffff4f, // b  8a2c <__adddf3+0xec>
    /* 8cec: */ 0xe1a02081, // lsl  r2, r1, #1  // __aeabi_d2iz
    /* 8cf0: */ 0xe2922602, // adds r2, r2, #2097152  ; 0x200000
    /* 8cf4: */ 0x2a00000c, // bcs  8d2c <__aeabi_d2iz+0x40>
    /* 8cf8: */ 0x5a000009, // bpl  8d24 <__aeabi_d2iz+0x38>
    /* 8cfc: */ 0xe3e03e3e, // mvn  r3, #992  ; 0x3e0
    /* 8d00: */ 0xe0532ac2, // subs r2, r3, r2, asr #21
    /* 8d04: */ 0x9a00000a, // bls  8d34 <__aeabi_d2iz+0x48>
    /* 8d08: */ 0xe1a03581, // lsl  r3, r1, #11
    /* 8d0c: */ 0xe3833102, // orr  r3, r3, #-2147483648  ; 0x80000000
    /* 8d10: */ 0xe1833aa0, // orr  r3, r3, r0, lsr #21
    /* 8d14: */ 0xe3110102, // tst  r1, #-2147483648  ; 0x80000000
    /* 8d18: */ 0xe1a00233, // lsr  r0, r3, r2
    /* 8d1c: */ 0x12600000, // rsbne  r0, r0, #0
    /* 8d20: */ 0xe12fff1e, // bx lr
    /* 8d24: */ 0xe3a00000, // mov  r0, #0
    /* 8d28: */ 0xe12fff1e, // bx lr
    /* 8d2c: */ 0xe1900601, // orrs r0, r0, r1, lsl #12
    /* 8d30: */ 0x1a000002, // bne  8d40 <__aeabi_d2iz+0x54>
    /* 8d34: */ 0xe2110102, // ands r0, r1, #-2147483648  ; 0x80000000
    /* 8d38: */ 0x03e00102, // mvneq  r0, #-2147483648  ; 0x80000000
    /* 8d3c: */ 0xe12fff1e, // bx lr
    /* 8d40: */ 0xe3a00000, // mov  r0, #0
    /* 8d44: */ 0xe12fff1e, // bx lr
    /* 8d48: */ 0xe92d43f8, // push {r3, r4, r5, r6, r7, r8, r9, lr}  // __libc_csu_init
    /* 8d4c: */ 0xe59f604c, // ldr  r6, [pc, #76] ; 8da0 <__libc_csu_init+0x58>
    /* 8d50: */ 0xe59f504c, // ldr  r5, [pc, #76] ; 8da4 <__libc_csu_init+0x5c>
    /* 8d54: */ 0xe08f6006, // add  r6, pc, r6
    /* 8d58: */ 0xe08f5005, // add  r5, pc, r5
    /* 8d5c: */ 0xe0656006, // rsb  r6, r5, r6
    /* 8d60: */ 0xe1a07000, // mov  r7, r0
    /* 8d64: */ 0xe1a08001, // mov  r8, r1
    /* 8d68: */ 0xe1a09002, // mov  r9, r2
    /* 8d6c: */ 0xebfffd91, // bl 83b8 <_init>
    /* 8d70: */ 0xe1b06146, // asrs r6, r6, #2
    /* 8d74: */ 0x08bd83f8, // popeq  {r3, r4, r5, r6, r7, r8, r9, pc}
    /* 8d78: */ 0xe3a04000, // mov  r4, #0
    /* 8d7c: */ 0xe2844001, // add  r4, r4, #1
    /* 8d80: */ 0xe4953004, // ldr  r3, [r5], #4
    /* 8d84: */ 0xe1a00007, // mov  r0, r7
    /* 8d88: */ 0xe1a01008, // mov  r1, r8
    /* 8d8c: */ 0xe1a02009, // mov  r2, r9
    /* 8d90: */ 0xe12fff33, // blx  r3
    /* 8d94: */ 0xe1540006, // cmp  r4, r6
    /* 8d98: */ 0x1afffff7, // bne  8d7c <__libc_csu_init+0x34>
    /* 8d9c: */ 0xe8bd83f8, // pop  {r3, r4, r5, r6, r7, r8, r9, pc}
    /* 8da0: */ 0x000080e4, // .word  0x000080e4
    /* 8da4: */ 0x000080dc, // .word  0x000080dc
    /* 8da8: */ 0xe12fff1e, // bx lr  // __libc_csu_fini
    /* 8dac: */ 0xe92d4008, // push {r3, lr}  // _fini
    /* 8db0: */ 0xe8bd8008, // pop  {r3, pc}
  };

  uint32_t size = sizeof(stream) / sizeof(stream[0]);
  bool with_sugar = (argc > 1 && strcmp(argv[1], "--sugar") == 0);
  fbt_disassemble_to_text(stream, size, 0x83b8, 1, with_sugar);

  return 0;
}

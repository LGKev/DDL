   1              		.cpu cortex-m0
   2              		.eabi_attribute 20, 1
   3              		.eabi_attribute 21, 1
   4              		.eabi_attribute 23, 3
   5              		.eabi_attribute 24, 1
   6              		.eabi_attribute 25, 1
   7              		.eabi_attribute 26, 1
   8              		.eabi_attribute 30, 6
   9              		.eabi_attribute 34, 0
  10              		.eabi_attribute 18, 4
  11              		.file	"main.c"
  12              		.text
  13              	.Ltext0:
  14              		.cfi_sections	.debug_frame
  15              		.section	.text.sum,"ax",%progbits
  16              		.align	1
  17              		.global	sum
  18              		.syntax unified
  19              		.code	16
  20              		.thumb_func
  21              		.fpu softvfp
  23              	sum:
  24              	.LFB0:
  25              		.file 1 "../src/main.c"
   1:../src/main.c **** extern int asm_sum(int x, int y);
   2:../src/main.c **** 
   3:../src/main.c **** int sum(int x, int y) {
  26              		.loc 1 3 0
  27              		.cfi_startproc
  28              		@ args = 0, pretend = 0, frame = 8
  29              		@ frame_needed = 1, uses_anonymous_args = 0
  30 0000 80B5     		push	{r7, lr}
  31              		.cfi_def_cfa_offset 8
  32              		.cfi_offset 7, -8
  33              		.cfi_offset 14, -4
  34 0002 82B0     		sub	sp, sp, #8
  35              		.cfi_def_cfa_offset 16
  36 0004 00AF     		add	r7, sp, #0
  37              		.cfi_def_cfa_register 7
  38 0006 7860     		str	r0, [r7, #4]
  39 0008 3960     		str	r1, [r7]
   4:../src/main.c **** 	return x + y;
  40              		.loc 1 4 0
  41 000a 7A68     		ldr	r2, [r7, #4]
  42 000c 3B68     		ldr	r3, [r7]
  43 000e D318     		adds	r3, r2, r3
   5:../src/main.c **** }
  44              		.loc 1 5 0
  45 0010 1800     		movs	r0, r3
  46 0012 BD46     		mov	sp, r7
  47 0014 02B0     		add	sp, sp, #8
  48              		@ sp needed
  49 0016 80BD     		pop	{r7, pc}
  50              		.cfi_endproc
  51              	.LFE0:
  53              		.section	.text.main,"ax",%progbits
  54              		.align	1
  55              		.global	main
  56              		.syntax unified
  57              		.code	16
  58              		.thumb_func
  59              		.fpu softvfp
  61              	main:
  62              	.LFB1:
   6:../src/main.c **** 
   7:../src/main.c **** int main(void) {
  63              		.loc 1 7 0
  64              		.cfi_startproc
  65              		@ args = 0, pretend = 0, frame = 8
  66              		@ frame_needed = 1, uses_anonymous_args = 0
  67 0000 80B5     		push	{r7, lr}
  68              		.cfi_def_cfa_offset 8
  69              		.cfi_offset 7, -8
  70              		.cfi_offset 14, -4
  71 0002 82B0     		sub	sp, sp, #8
  72              		.cfi_def_cfa_offset 16
  73 0004 00AF     		add	r7, sp, #0
  74              		.cfi_def_cfa_register 7
   8:../src/main.c **** 
   9:../src/main.c **** 	int i, j;
  10:../src/main.c **** 
  11:../src/main.c **** 	i = sum(1, 2);
  75              		.loc 1 11 0
  76 0006 0221     		movs	r1, #2
  77 0008 0120     		movs	r0, #1
  78 000a FFF7FEFF 		bl	sum
  79 000e 0300     		movs	r3, r0
  80 0010 7B60     		str	r3, [r7, #4]
  12:../src/main.c **** 	j = asm_sum(5, 6);
  81              		.loc 1 12 0
  82 0012 0621     		movs	r1, #6
  83 0014 0520     		movs	r0, #5
  84 0016 FFF7FEFF 		bl	asm_sum
  85 001a 0300     		movs	r3, r0
  86 001c 3B60     		str	r3, [r7]
  87              	.L4:
  13:../src/main.c **** 
  14:../src/main.c **** 	// Enter an infinite loop, just incrementing a counter
  15:../src/main.c **** 	volatile static int loop = 0;
  16:../src/main.c **** 	while (1) {
  17:../src/main.c **** 		loop++;
  88              		.loc 1 17 0 discriminator 1
  89 001e 034B     		ldr	r3, .L5
  90 0020 1B68     		ldr	r3, [r3]
  91 0022 5A1C     		adds	r2, r3, #1
  92 0024 014B     		ldr	r3, .L5
  93 0026 1A60     		str	r2, [r3]
  94 0028 F9E7     		b	.L4
  95              	.L6:
  96 002a C046     		.align	2
  97              	.L5:
  98 002c 00000000 		.word	loop.3630
  99              		.cfi_endproc
 100              	.LFE1:
 102              		.bss
 103              		.align	2
 104              	loop.3630:
 105 0000 00000000 		.space	4
 107              		.text
 108              	.Letext0:
DEFINED SYMBOLS
                            *ABS*:0000000000000000 main.c
     /tmp/ccV5GyPm.s:16     .text.sum:0000000000000000 $t
     /tmp/ccV5GyPm.s:23     .text.sum:0000000000000000 sum
     /tmp/ccV5GyPm.s:54     .text.main:0000000000000000 $t
     /tmp/ccV5GyPm.s:61     .text.main:0000000000000000 main
     /tmp/ccV5GyPm.s:98     .text.main:000000000000002c $d
     /tmp/ccV5GyPm.s:104    .bss:0000000000000000 loop.3630
     /tmp/ccV5GyPm.s:103    .bss:0000000000000000 $d
                           .group:0000000000000000 wm4.0.a91a75295d12acab8a45dbf128a8bd68

UNDEFINED SYMBOLS
asm_sum

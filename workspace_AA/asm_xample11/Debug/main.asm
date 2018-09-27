   1              		.syntax unified
   2              		.cpu cortex-m0
   3              		.fpu softvfp
   4              		.eabi_attribute 20, 1
   5              		.eabi_attribute 21, 1
   6              		.eabi_attribute 23, 3
   7              		.eabi_attribute 24, 1
   8              		.eabi_attribute 25, 1
   9              		.eabi_attribute 26, 1
  10              		.eabi_attribute 30, 6
  11              		.eabi_attribute 34, 0
  12              		.eabi_attribute 18, 4
  13              		.thumb
  14              		.syntax unified
  15              		.file	"main.c"
  16              		.text
  17              	.Ltext0:
  18              		.cfi_sections	.debug_frame
  19              		.section	.text.sum,"ax",%progbits
  20              		.align	2
  21              		.global	sum
  22              		.code	16
  23              		.thumb_func
  25              	sum:
  26              	.LFB0:
  27              		.file 1 "../src/main.c"
   1:../src/main.c **** extern int asm_sum(int x, int y);
   2:../src/main.c **** 
   3:../src/main.c **** int sum(int x, int y) {
  28              		.loc 1 3 0
  29              		.cfi_startproc
  30              		@ args = 0, pretend = 0, frame = 8
  31              		@ frame_needed = 1, uses_anonymous_args = 0
  32 0000 80B5     		push	{r7, lr}
  33              		.cfi_def_cfa_offset 8
  34              		.cfi_offset 7, -8
  35              		.cfi_offset 14, -4
  36 0002 82B0     		sub	sp, sp, #8
  37              		.cfi_def_cfa_offset 16
  38 0004 00AF     		add	r7, sp, #0
  39              		.cfi_def_cfa_register 7
  40 0006 7860     		str	r0, [r7, #4]
  41 0008 3960     		str	r1, [r7]
   4:../src/main.c **** 	return x + y;
  42              		.loc 1 4 0
  43 000a 7A68     		ldr	r2, [r7, #4]
  44 000c 3B68     		ldr	r3, [r7]
  45 000e D318     		adds	r3, r2, r3
   5:../src/main.c **** }
  46              		.loc 1 5 0
  47 0010 1800     		movs	r0, r3
  48 0012 BD46     		mov	sp, r7
  49 0014 02B0     		add	sp, sp, #8
  50              		@ sp needed
  51 0016 80BD     		pop	{r7, pc}
  52              		.cfi_endproc
  53              	.LFE0:
  55              		.section	.text.main,"ax",%progbits
  56              		.align	2
  57              		.global	main
  58              		.code	16
  59              		.thumb_func
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
  18:../src/main.c **** 	}
  94              		.loc 1 18 0 discriminator 1
  95 0028 F9E7     		b	.L4
  96              	.L6:
  97 002a C046     		.align	2
  98              	.L5:
  99 002c 00000000 		.word	loop.3695
 100              		.cfi_endproc
 101              	.LFE1:
 103              		.bss
 104              		.align	2
 105              	loop.3695:
 106 0000 00000000 		.space	4
 107              		.text
 108              	.Letext0:
DEFINED SYMBOLS
                            *ABS*:00000000 main.c
C:\Users\dell\AppData\Local\Temp\ccfj8FXB.s:20     .text.sum:00000000 $t
C:\Users\dell\AppData\Local\Temp\ccfj8FXB.s:25     .text.sum:00000000 sum
C:\Users\dell\AppData\Local\Temp\ccfj8FXB.s:56     .text.main:00000000 $t
C:\Users\dell\AppData\Local\Temp\ccfj8FXB.s:61     .text.main:00000000 main
C:\Users\dell\AppData\Local\Temp\ccfj8FXB.s:99     .text.main:0000002c $d
C:\Users\dell\AppData\Local\Temp\ccfj8FXB.s:105    .bss:00000000 loop.3695
C:\Users\dell\AppData\Local\Temp\ccfj8FXB.s:104    .bss:00000000 $d
                     .debug_frame:00000010 $d
                           .group:00000000 wm4.0.935e200dcf4f236f804f4066baa4d700

UNDEFINED SYMBOLS
asm_sum

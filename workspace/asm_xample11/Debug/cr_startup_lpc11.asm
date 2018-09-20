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
  15              		.file	"cr_startup_lpc11.c"
  16              		.text
  17              	.Ltext0:
  18              		.cfi_sections	.debug_frame
  19              		.global	g_pfnVectors
  20              		.section	.isr_vector,"a",%progbits
  21              		.align	2
  24              	g_pfnVectors:
  25 0000 00000000 		.word	_vStackTop
  26 0004 00000000 		.word	ResetISR
  27 0008 00000000 		.word	NMI_Handler
  28 000c 00000000 		.word	HardFault_Handler
  29 0010 00000000 		.word	0
  30 0014 00000000 		.word	0
  31 0018 00000000 		.word	0
  32 001c 00000000 		.word	0
  33 0020 00000000 		.word	0
  34 0024 00000000 		.word	0
  35 0028 00000000 		.word	0
  36 002c 00000000 		.word	SVCall_Handler
  37 0030 00000000 		.word	0
  38 0034 00000000 		.word	0
  39 0038 00000000 		.word	PendSV_Handler
  40 003c 00000000 		.word	SysTick_Handler
  41 0040 00000000 		.word	WAKEUP_IRQHandler
  42 0044 00000000 		.word	WAKEUP_IRQHandler
  43 0048 00000000 		.word	WAKEUP_IRQHandler
  44 004c 00000000 		.word	WAKEUP_IRQHandler
  45 0050 00000000 		.word	WAKEUP_IRQHandler
  46 0054 00000000 		.word	WAKEUP_IRQHandler
  47 0058 00000000 		.word	WAKEUP_IRQHandler
  48 005c 00000000 		.word	WAKEUP_IRQHandler
  49 0060 00000000 		.word	WAKEUP_IRQHandler
  50 0064 00000000 		.word	WAKEUP_IRQHandler
  51 0068 00000000 		.word	WAKEUP_IRQHandler
  52 006c 00000000 		.word	WAKEUP_IRQHandler
  53 0070 00000000 		.word	WAKEUP_IRQHandler
  54 0074 00000000 		.word	WAKEUP_IRQHandler
  55 0078 00000000 		.word	WAKEUP_IRQHandler
  56 007c 00000000 		.word	I2C_IRQHandler
  57 0080 00000000 		.word	TIMER16_0_IRQHandler
  58 0084 00000000 		.word	TIMER16_1_IRQHandler
  59 0088 00000000 		.word	TIMER32_0_IRQHandler
  60 008c 00000000 		.word	TIMER32_1_IRQHandler
  61 0090 00000000 		.word	SSP_IRQHandler
  62 0094 00000000 		.word	UART_IRQHandler
  63 0098 00000000 		.word	USB_IRQHandler
  64 009c 00000000 		.word	USB_FIQHandler
  65 00a0 00000000 		.word	ADC_IRQHandler
  66 00a4 00000000 		.word	WDT_IRQHandler
  67 00a8 00000000 		.word	BOD_IRQHandler
  68 00ac 00000000 		.word	FMC_IRQHandler
  69 00b0 00000000 		.word	PIOINT3_IRQHandler
  70 00b4 00000000 		.word	PIOINT2_IRQHandler
  71 00b8 00000000 		.word	PIOINT1_IRQHandler
  72 00bc 00000000 		.word	PIOINT0_IRQHandler
  73              		.section	.text.Reset_Handler,"ax",%progbits
  74              		.align	2
  75              		.global	Reset_Handler
  76              		.code	16
  77              		.thumb_func
  79              	Reset_Handler:
  80              	.LFB0:
  81              		.file 1 "../src/cr_startup_lpc11.c"
   1:../src/cr_startup_lpc11.c **** //*****************************************************************************
   2:../src/cr_startup_lpc11.c **** //   +--+       
   3:../src/cr_startup_lpc11.c **** //   | ++----+   
   4:../src/cr_startup_lpc11.c **** //   +-++    |  
   5:../src/cr_startup_lpc11.c **** //     |     |  
   6:../src/cr_startup_lpc11.c **** //   +-+--+  |   
   7:../src/cr_startup_lpc11.c **** //   | +--+--+  
   8:../src/cr_startup_lpc11.c **** //   +----+    Copyright (c) 2009 Code Red Technologies Ltd. 
   9:../src/cr_startup_lpc11.c **** //
  10:../src/cr_startup_lpc11.c **** // Microcontroller Startup code for use with Red Suite
  11:../src/cr_startup_lpc11.c **** //
  12:../src/cr_startup_lpc11.c **** // Software License Agreement
  13:../src/cr_startup_lpc11.c **** // 
  14:../src/cr_startup_lpc11.c **** // The software is owned by Code Red Technologies and/or its suppliers, and is 
  15:../src/cr_startup_lpc11.c **** // protected under applicable copyright laws.  All rights are reserved.  Any 
  16:../src/cr_startup_lpc11.c **** // use in violation of the foregoing restrictions may subject the user to criminal 
  17:../src/cr_startup_lpc11.c **** // sanctions under applicable laws, as well as to civil liability for the breach 
  18:../src/cr_startup_lpc11.c **** // of the terms and conditions of this license.
  19:../src/cr_startup_lpc11.c **** // 
  20:../src/cr_startup_lpc11.c **** // THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
  21:../src/cr_startup_lpc11.c **** // OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
  22:../src/cr_startup_lpc11.c **** // MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
  23:../src/cr_startup_lpc11.c **** // USE OF THIS SOFTWARE FOR COMMERCIAL DEVELOPMENT AND/OR EDUCATION IS SUBJECT
  24:../src/cr_startup_lpc11.c **** // TO A CURRENT END USER LICENSE AGREEMENT (COMMERCIAL OR EDUCATIONAL) WITH
  25:../src/cr_startup_lpc11.c **** // CODE RED TECHNOLOGIES LTD. 
  26:../src/cr_startup_lpc11.c **** //
  27:../src/cr_startup_lpc11.c **** //*****************************************************************************
  28:../src/cr_startup_lpc11.c **** #define WEAK __attribute__ ((weak))
  29:../src/cr_startup_lpc11.c **** #define ALIAS(f) __attribute__ ((weak, alias (#f)))
  30:../src/cr_startup_lpc11.c **** 
  31:../src/cr_startup_lpc11.c **** // Code Red - if CMSIS is being used, then SystemInit() routine
  32:../src/cr_startup_lpc11.c **** // will be called by startup code rather than in application's main()
  33:../src/cr_startup_lpc11.c **** #ifdef __USE_CMSIS
  34:../src/cr_startup_lpc11.c **** #include "system_LPC11xx.h"
  35:../src/cr_startup_lpc11.c **** #endif
  36:../src/cr_startup_lpc11.c **** 
  37:../src/cr_startup_lpc11.c **** //*****************************************************************************
  38:../src/cr_startup_lpc11.c **** //
  39:../src/cr_startup_lpc11.c **** // Forward declaration of the default handlers. These are aliased.
  40:../src/cr_startup_lpc11.c **** // When the application defines a handler (with the same name), this will 
  41:../src/cr_startup_lpc11.c **** // automatically take precedence over these weak definitions
  42:../src/cr_startup_lpc11.c **** //
  43:../src/cr_startup_lpc11.c **** //*****************************************************************************
  44:../src/cr_startup_lpc11.c ****      void Reset_Handler(void);
  45:../src/cr_startup_lpc11.c ****      void ResetISR(void) ALIAS(Reset_Handler);
  46:../src/cr_startup_lpc11.c **** WEAK void NMI_Handler(void);
  47:../src/cr_startup_lpc11.c **** WEAK void HardFault_Handler(void);
  48:../src/cr_startup_lpc11.c **** WEAK void SVCall_Handler(void);
  49:../src/cr_startup_lpc11.c **** WEAK void PendSV_Handler(void);
  50:../src/cr_startup_lpc11.c **** WEAK void SysTick_Handler(void);
  51:../src/cr_startup_lpc11.c **** 
  52:../src/cr_startup_lpc11.c **** //*****************************************************************************
  53:../src/cr_startup_lpc11.c **** //
  54:../src/cr_startup_lpc11.c **** // Forward declaration of the specific IRQ handlers. These are aliased
  55:../src/cr_startup_lpc11.c **** // to the IntDefaultHandler, which is a 'forever' loop. When the application
  56:../src/cr_startup_lpc11.c **** // defines a handler (with the same name), this will automatically take
  57:../src/cr_startup_lpc11.c **** // precedence over these weak definitions
  58:../src/cr_startup_lpc11.c **** //
  59:../src/cr_startup_lpc11.c **** //*****************************************************************************
  60:../src/cr_startup_lpc11.c **** 
  61:../src/cr_startup_lpc11.c **** void I2C_IRQHandler (void) ALIAS(IntDefaultHandler);
  62:../src/cr_startup_lpc11.c **** void TIMER16_0_IRQHandler (void) ALIAS(IntDefaultHandler);
  63:../src/cr_startup_lpc11.c **** void TIMER16_1_IRQHandler (void) ALIAS(IntDefaultHandler);
  64:../src/cr_startup_lpc11.c **** void TIMER32_0_IRQHandler (void) ALIAS(IntDefaultHandler);
  65:../src/cr_startup_lpc11.c **** void TIMER32_1_IRQHandler (void) ALIAS(IntDefaultHandler);
  66:../src/cr_startup_lpc11.c **** void SSP_IRQHandler (void) ALIAS(IntDefaultHandler);
  67:../src/cr_startup_lpc11.c **** void UART_IRQHandler (void) ALIAS(IntDefaultHandler);
  68:../src/cr_startup_lpc11.c **** void USB_IRQHandler (void) ALIAS(IntDefaultHandler);
  69:../src/cr_startup_lpc11.c **** void USB_FIQHandler (void) ALIAS(IntDefaultHandler);
  70:../src/cr_startup_lpc11.c **** void ADC_IRQHandler (void) ALIAS(IntDefaultHandler);
  71:../src/cr_startup_lpc11.c **** void WDT_IRQHandler (void) ALIAS(IntDefaultHandler);
  72:../src/cr_startup_lpc11.c **** void BOD_IRQHandler (void) ALIAS(IntDefaultHandler);
  73:../src/cr_startup_lpc11.c **** void FMC_IRQHandler (void) ALIAS(IntDefaultHandler);
  74:../src/cr_startup_lpc11.c **** void PIOINT3_IRQHandler (void) ALIAS(IntDefaultHandler);
  75:../src/cr_startup_lpc11.c **** void PIOINT2_IRQHandler (void) ALIAS(IntDefaultHandler);
  76:../src/cr_startup_lpc11.c **** void PIOINT1_IRQHandler (void) ALIAS(IntDefaultHandler);
  77:../src/cr_startup_lpc11.c **** void PIOINT0_IRQHandler (void) ALIAS(IntDefaultHandler);
  78:../src/cr_startup_lpc11.c **** void WAKEUP_IRQHandler  (void) ALIAS(IntDefaultHandler);
  79:../src/cr_startup_lpc11.c **** 
  80:../src/cr_startup_lpc11.c **** //*****************************************************************************
  81:../src/cr_startup_lpc11.c **** //
  82:../src/cr_startup_lpc11.c **** // The entry point for the application.
  83:../src/cr_startup_lpc11.c **** // __main() is the entry point for redlib based applications
  84:../src/cr_startup_lpc11.c **** // main() is the entry point for newlib based applications
  85:../src/cr_startup_lpc11.c **** //
  86:../src/cr_startup_lpc11.c **** //*****************************************************************************
  87:../src/cr_startup_lpc11.c **** extern WEAK void __main(void);
  88:../src/cr_startup_lpc11.c **** extern WEAK void main(void);
  89:../src/cr_startup_lpc11.c **** //*****************************************************************************
  90:../src/cr_startup_lpc11.c **** //
  91:../src/cr_startup_lpc11.c **** // External declaration for the pointer to the stack top from the Linker Script
  92:../src/cr_startup_lpc11.c **** //
  93:../src/cr_startup_lpc11.c **** //*****************************************************************************
  94:../src/cr_startup_lpc11.c **** extern void _vStackTop;
  95:../src/cr_startup_lpc11.c **** 
  96:../src/cr_startup_lpc11.c **** //*****************************************************************************
  97:../src/cr_startup_lpc11.c **** //
  98:../src/cr_startup_lpc11.c **** // The vector table.  Note that the proper constructs must be placed on this to
  99:../src/cr_startup_lpc11.c **** // ensure that it ends up at physical address 0x0000.0000.
 100:../src/cr_startup_lpc11.c **** //
 101:../src/cr_startup_lpc11.c **** //*****************************************************************************
 102:../src/cr_startup_lpc11.c **** __attribute__ ((section(".isr_vector")))
 103:../src/cr_startup_lpc11.c **** void (* const g_pfnVectors[])(void) =
 104:../src/cr_startup_lpc11.c **** {
 105:../src/cr_startup_lpc11.c ****     (void *)&_vStackTop,		    		// The initial stack pointer
 106:../src/cr_startup_lpc11.c ****     ResetISR,                               // The reset handler
 107:../src/cr_startup_lpc11.c ****     NMI_Handler,                            // The NMI handler
 108:../src/cr_startup_lpc11.c ****     HardFault_Handler,                      // The hard fault handler
 109:../src/cr_startup_lpc11.c ****     0,                      				// Reserved
 110:../src/cr_startup_lpc11.c ****     0,                      				// Reserved
 111:../src/cr_startup_lpc11.c ****     0,                      				// Reserved
 112:../src/cr_startup_lpc11.c ****     0,                                      // Reserved
 113:../src/cr_startup_lpc11.c ****     0,                                      // Reserved
 114:../src/cr_startup_lpc11.c ****     0,                                      // Reserved
 115:../src/cr_startup_lpc11.c ****     0,                                      // Reserved
 116:../src/cr_startup_lpc11.c ****     SVCall_Handler,                      	// SVCall handler
 117:../src/cr_startup_lpc11.c ****     0,                      				// Reserved
 118:../src/cr_startup_lpc11.c ****     0,                                      // Reserved
 119:../src/cr_startup_lpc11.c ****     PendSV_Handler,                      	// The PendSV handler
 120:../src/cr_startup_lpc11.c ****     SysTick_Handler,                      	// The SysTick handler
 121:../src/cr_startup_lpc11.c **** 
 122:../src/cr_startup_lpc11.c ****     // Wakeup sources (15 ea.) for the I/O pins:
 123:../src/cr_startup_lpc11.c ****     //   PIO0 (0:11)
 124:../src/cr_startup_lpc11.c ****     //   PIO1 (0:2)
 125:../src/cr_startup_lpc11.c ****     WAKEUP_IRQHandler,                      // PIO0_0  Wakeup
 126:../src/cr_startup_lpc11.c ****     WAKEUP_IRQHandler,                      // PIO0_1  Wakeup
 127:../src/cr_startup_lpc11.c ****     WAKEUP_IRQHandler,                      // PIO0_2  Wakeup
 128:../src/cr_startup_lpc11.c ****     WAKEUP_IRQHandler,                      // PIO0_3  Wakeup
 129:../src/cr_startup_lpc11.c ****     WAKEUP_IRQHandler,                      // PIO0_4  Wakeup
 130:../src/cr_startup_lpc11.c ****     WAKEUP_IRQHandler,                      // PIO0_5  Wakeup
 131:../src/cr_startup_lpc11.c ****     WAKEUP_IRQHandler,                      // PIO0_6  Wakeup
 132:../src/cr_startup_lpc11.c ****     WAKEUP_IRQHandler,                      // PIO0_7  Wakeup
 133:../src/cr_startup_lpc11.c ****     WAKEUP_IRQHandler,                      // PIO0_8  Wakeup
 134:../src/cr_startup_lpc11.c ****     WAKEUP_IRQHandler,                      // PIO0_9  Wakeup
 135:../src/cr_startup_lpc11.c ****     WAKEUP_IRQHandler,                      // PIO0_10 Wakeup
 136:../src/cr_startup_lpc11.c ****     WAKEUP_IRQHandler,                      // PIO0_11 Wakeup
 137:../src/cr_startup_lpc11.c ****     WAKEUP_IRQHandler,                      // PIO1_0  Wakeup
 138:../src/cr_startup_lpc11.c ****     WAKEUP_IRQHandler,                      // PIO1_1  Wakeup
 139:../src/cr_startup_lpc11.c ****     WAKEUP_IRQHandler,                      // PIO1_2  Wakeup
 140:../src/cr_startup_lpc11.c ****     
 141:../src/cr_startup_lpc11.c ****     I2C_IRQHandler,                      	// I2C0
 142:../src/cr_startup_lpc11.c ****     TIMER16_0_IRQHandler,                   // CT16B0 (16-bit Timer 0)
 143:../src/cr_startup_lpc11.c ****     TIMER16_1_IRQHandler,                   // CT16B1 (16-bit Timer 1)
 144:../src/cr_startup_lpc11.c ****     TIMER32_0_IRQHandler,                   // CT32B0 (32-bit Timer 0)
 145:../src/cr_startup_lpc11.c ****     TIMER32_1_IRQHandler,                   // CT32B1 (32-bit Timer 1)
 146:../src/cr_startup_lpc11.c ****     SSP_IRQHandler,                      	// SSP0
 147:../src/cr_startup_lpc11.c ****     UART_IRQHandler,                      	// UART0
 148:../src/cr_startup_lpc11.c **** 
 149:../src/cr_startup_lpc11.c ****     USB_IRQHandler,                      	// USB IRQ
 150:../src/cr_startup_lpc11.c ****     USB_FIQHandler,                      	// USB FIQ
 151:../src/cr_startup_lpc11.c **** 
 152:../src/cr_startup_lpc11.c ****     ADC_IRQHandler,                      	// ADC   (A/D Converter)
 153:../src/cr_startup_lpc11.c ****     WDT_IRQHandler,                      	// WDT   (Watchdog Timer)
 154:../src/cr_startup_lpc11.c ****     BOD_IRQHandler,                      	// BOD   (Brownout Detect)
 155:../src/cr_startup_lpc11.c ****     FMC_IRQHandler,                      	// Flash (IP2111 Flash Memory Controller)
 156:../src/cr_startup_lpc11.c ****     PIOINT3_IRQHandler,                     // PIO INT3
 157:../src/cr_startup_lpc11.c ****     PIOINT2_IRQHandler,                     // PIO INT2
 158:../src/cr_startup_lpc11.c ****     PIOINT1_IRQHandler,                     // PIO INT1
 159:../src/cr_startup_lpc11.c ****     PIOINT0_IRQHandler,                     // PIO INT0
 160:../src/cr_startup_lpc11.c **** };
 161:../src/cr_startup_lpc11.c **** 
 162:../src/cr_startup_lpc11.c **** //*****************************************************************************
 163:../src/cr_startup_lpc11.c **** //
 164:../src/cr_startup_lpc11.c **** // The following are constructs created by the linker, indicating where the
 165:../src/cr_startup_lpc11.c **** // the "data" and "bss" segments reside in memory.  The initializers for the
 166:../src/cr_startup_lpc11.c **** // for the "data" segment resides immediately following the "text" segment.
 167:../src/cr_startup_lpc11.c **** //
 168:../src/cr_startup_lpc11.c **** //*****************************************************************************
 169:../src/cr_startup_lpc11.c **** extern unsigned char _etext;
 170:../src/cr_startup_lpc11.c **** extern unsigned char _data;
 171:../src/cr_startup_lpc11.c **** extern unsigned char _edata;
 172:../src/cr_startup_lpc11.c **** extern unsigned char _bss;
 173:../src/cr_startup_lpc11.c **** extern unsigned char _ebss;
 174:../src/cr_startup_lpc11.c **** 
 175:../src/cr_startup_lpc11.c **** //*****************************************************************************
 176:../src/cr_startup_lpc11.c **** //
 177:../src/cr_startup_lpc11.c **** // This is the code that gets called when the processor first starts execution
 178:../src/cr_startup_lpc11.c **** // following a reset event.  Only the absolutely necessary set is performed,
 179:../src/cr_startup_lpc11.c **** // after which the application supplied entry() routine is called.  Any fancy
 180:../src/cr_startup_lpc11.c **** // actions (such as making decisions based on the reset cause register, and
 181:../src/cr_startup_lpc11.c **** // resetting the bits in that register) are left solely in the hands of the
 182:../src/cr_startup_lpc11.c **** // application.
 183:../src/cr_startup_lpc11.c **** //
 184:../src/cr_startup_lpc11.c **** //*****************************************************************************
 185:../src/cr_startup_lpc11.c **** void Reset_Handler(void)
 186:../src/cr_startup_lpc11.c **** {
  82              		.loc 1 186 0
  83              		.cfi_startproc
  84              		@ args = 0, pretend = 0, frame = 8
  85              		@ frame_needed = 1, uses_anonymous_args = 0
  86 0000 80B5     		push	{r7, lr}
  87              		.cfi_def_cfa_offset 8
  88              		.cfi_offset 7, -8
  89              		.cfi_offset 14, -4
  90 0002 82B0     		sub	sp, sp, #8
  91              		.cfi_def_cfa_offset 16
  92 0004 00AF     		add	r7, sp, #0
  93              		.cfi_def_cfa_register 7
 187:../src/cr_startup_lpc11.c ****     unsigned char *pulSrc, *pulDest;
 188:../src/cr_startup_lpc11.c **** 
 189:../src/cr_startup_lpc11.c ****     //
 190:../src/cr_startup_lpc11.c ****     // Copy the data segment initializers from flash to SRAM.
 191:../src/cr_startup_lpc11.c ****     //
 192:../src/cr_startup_lpc11.c ****     pulSrc = &_etext;
  94              		.loc 1 192 0
  95 0006 134B     		ldr	r3, .L8
  96 0008 7B60     		str	r3, [r7, #4]
 193:../src/cr_startup_lpc11.c ****     for(pulDest = &_data; pulDest < &_edata; )
  97              		.loc 1 193 0
  98 000a 134B     		ldr	r3, .L8+4
  99 000c 3B60     		str	r3, [r7]
 100 000e 07E0     		b	.L2
 101              	.L3:
 194:../src/cr_startup_lpc11.c ****     {
 195:../src/cr_startup_lpc11.c ****         *pulDest++ = *pulSrc++;
 102              		.loc 1 195 0
 103 0010 3B68     		ldr	r3, [r7]
 104 0012 5A1C     		adds	r2, r3, #1
 105 0014 3A60     		str	r2, [r7]
 106 0016 7A68     		ldr	r2, [r7, #4]
 107 0018 511C     		adds	r1, r2, #1
 108 001a 7960     		str	r1, [r7, #4]
 109 001c 1278     		ldrb	r2, [r2]
 110 001e 1A70     		strb	r2, [r3]
 111              	.L2:
 193:../src/cr_startup_lpc11.c ****     for(pulDest = &_data; pulDest < &_edata; )
 112              		.loc 1 193 0 discriminator 1
 113 0020 3A68     		ldr	r2, [r7]
 114 0022 0E4B     		ldr	r3, .L8+8
 115 0024 9A42     		cmp	r2, r3
 116 0026 F3D3     		bcc	.L3
 196:../src/cr_startup_lpc11.c ****     }
 197:../src/cr_startup_lpc11.c **** 
 198:../src/cr_startup_lpc11.c ****     //
 199:../src/cr_startup_lpc11.c ****     // Zero fill the bss segment.
 200:../src/cr_startup_lpc11.c ****     //
 201:../src/cr_startup_lpc11.c **** 	for(pulDest = &_bss; pulDest < &_ebss; pulDest++)
 117              		.loc 1 201 0
 118 0028 0D4B     		ldr	r3, .L8+12
 119 002a 3B60     		str	r3, [r7]
 120 002c 05E0     		b	.L4
 121              	.L5:
 202:../src/cr_startup_lpc11.c **** 	  *pulDest = 0;
 122              		.loc 1 202 0 discriminator 3
 123 002e 3B68     		ldr	r3, [r7]
 124 0030 0022     		movs	r2, #0
 125 0032 1A70     		strb	r2, [r3]
 201:../src/cr_startup_lpc11.c **** 	  *pulDest = 0;
 126              		.loc 1 201 0 discriminator 3
 127 0034 3B68     		ldr	r3, [r7]
 128 0036 0133     		adds	r3, r3, #1
 129 0038 3B60     		str	r3, [r7]
 130              	.L4:
 201:../src/cr_startup_lpc11.c **** 	  *pulDest = 0;
 131              		.loc 1 201 0 is_stmt 0 discriminator 1
 132 003a 3A68     		ldr	r2, [r7]
 133 003c 094B     		ldr	r3, .L8+16
 134 003e 9A42     		cmp	r2, r3
 135 0040 F5D3     		bcc	.L5
 203:../src/cr_startup_lpc11.c **** 
 204:../src/cr_startup_lpc11.c **** #ifdef __USE_CMSIS
 205:../src/cr_startup_lpc11.c **** 	SystemInit();
 206:../src/cr_startup_lpc11.c **** #endif
 207:../src/cr_startup_lpc11.c **** 	//
 208:../src/cr_startup_lpc11.c **** 	// Call the application's entry point.
 209:../src/cr_startup_lpc11.c **** 	// __main() is the entry point for redlib based applications (which calls main())
 210:../src/cr_startup_lpc11.c **** 	// main() is the entry point for newlib based applications
 211:../src/cr_startup_lpc11.c **** 	//
 212:../src/cr_startup_lpc11.c **** 	if (__main)
 136              		.loc 1 212 0 is_stmt 1
 137 0042 094B     		ldr	r3, .L8+20
 138 0044 002B     		cmp	r3, #0
 139 0046 02D0     		beq	.L6
 213:../src/cr_startup_lpc11.c **** 		__main() ;
 140              		.loc 1 213 0
 141 0048 FFF7FEFF 		bl	__main
 142 004c 01E0     		b	.L7
 143              	.L6:
 214:../src/cr_startup_lpc11.c **** 	else
 215:../src/cr_startup_lpc11.c **** 		main() ;
 144              		.loc 1 215 0
 145 004e FFF7FEFF 		bl	main
 146              	.L7:
 216:../src/cr_startup_lpc11.c **** 
 217:../src/cr_startup_lpc11.c **** 	//
 218:../src/cr_startup_lpc11.c **** 	// main() shouldn't return, but if it does, we'll just enter an infinite loop 
 219:../src/cr_startup_lpc11.c **** 	//
 220:../src/cr_startup_lpc11.c **** 	while (1) {
 221:../src/cr_startup_lpc11.c **** 		;
 222:../src/cr_startup_lpc11.c **** 	}
 147              		.loc 1 222 0 discriminator 1
 148 0052 FEE7     		b	.L7
 149              	.L9:
 150              		.align	2
 151              	.L8:
 152 0054 00000000 		.word	_etext
 153 0058 00000000 		.word	_data
 154 005c 00000000 		.word	_edata
 155 0060 00000000 		.word	_bss
 156 0064 00000000 		.word	_ebss
 157 0068 00000000 		.word	__main
 158              		.cfi_endproc
 159              	.LFE0:
 161              		.weak	ResetISR
 162              		.thumb_set ResetISR,Reset_Handler
 163              		.section	.text.NMI_Handler,"ax",%progbits
 164              		.align	2
 165              		.weak	NMI_Handler
 166              		.code	16
 167              		.thumb_func
 169              	NMI_Handler:
 170              	.LFB1:
 223:../src/cr_startup_lpc11.c **** }
 224:../src/cr_startup_lpc11.c **** 
 225:../src/cr_startup_lpc11.c **** //*****************************************************************************
 226:../src/cr_startup_lpc11.c **** //
 227:../src/cr_startup_lpc11.c **** // This is the code that gets called when the processor receives a NMI.  This
 228:../src/cr_startup_lpc11.c **** // simply enters an infinite loop, preserving the system state for examination
 229:../src/cr_startup_lpc11.c **** // by a debugger.
 230:../src/cr_startup_lpc11.c **** //
 231:../src/cr_startup_lpc11.c **** //*****************************************************************************
 232:../src/cr_startup_lpc11.c **** void NMI_Handler(void)
 233:../src/cr_startup_lpc11.c **** {
 171              		.loc 1 233 0
 172              		.cfi_startproc
 173              		@ args = 0, pretend = 0, frame = 0
 174              		@ frame_needed = 1, uses_anonymous_args = 0
 175 0000 80B5     		push	{r7, lr}
 176              		.cfi_def_cfa_offset 8
 177              		.cfi_offset 7, -8
 178              		.cfi_offset 14, -4
 179 0002 00AF     		add	r7, sp, #0
 180              		.cfi_def_cfa_register 7
 181              	.L11:
 234:../src/cr_startup_lpc11.c ****     //
 235:../src/cr_startup_lpc11.c ****     // Enter an infinite loop.
 236:../src/cr_startup_lpc11.c ****     //
 237:../src/cr_startup_lpc11.c ****     while(1)
 238:../src/cr_startup_lpc11.c ****     {
 239:../src/cr_startup_lpc11.c ****     }
 182              		.loc 1 239 0 discriminator 1
 183 0004 FEE7     		b	.L11
 184              		.cfi_endproc
 185              	.LFE1:
 187 0006 C046     		.section	.text.HardFault_Handler,"ax",%progbits
 188              		.align	2
 189              		.weak	HardFault_Handler
 190              		.code	16
 191              		.thumb_func
 193              	HardFault_Handler:
 194              	.LFB2:
 240:../src/cr_startup_lpc11.c **** }
 241:../src/cr_startup_lpc11.c **** 
 242:../src/cr_startup_lpc11.c **** //*****************************************************************************
 243:../src/cr_startup_lpc11.c **** //
 244:../src/cr_startup_lpc11.c **** // This is the code that gets called when the processor receives a fault
 245:../src/cr_startup_lpc11.c **** // interrupt.  This simply enters an infinite loop, preserving the system state
 246:../src/cr_startup_lpc11.c **** // for examination by a debugger.
 247:../src/cr_startup_lpc11.c **** //
 248:../src/cr_startup_lpc11.c **** //*****************************************************************************
 249:../src/cr_startup_lpc11.c **** void HardFault_Handler(void)
 250:../src/cr_startup_lpc11.c **** {
 195              		.loc 1 250 0
 196              		.cfi_startproc
 197              		@ args = 0, pretend = 0, frame = 0
 198              		@ frame_needed = 1, uses_anonymous_args = 0
 199 0000 80B5     		push	{r7, lr}
 200              		.cfi_def_cfa_offset 8
 201              		.cfi_offset 7, -8
 202              		.cfi_offset 14, -4
 203 0002 00AF     		add	r7, sp, #0
 204              		.cfi_def_cfa_register 7
 205              	.L13:
 251:../src/cr_startup_lpc11.c ****     //
 252:../src/cr_startup_lpc11.c ****     // Enter an infinite loop.
 253:../src/cr_startup_lpc11.c ****     //
 254:../src/cr_startup_lpc11.c ****     while(1)
 255:../src/cr_startup_lpc11.c ****     {
 256:../src/cr_startup_lpc11.c ****     }
 206              		.loc 1 256 0 discriminator 1
 207 0004 FEE7     		b	.L13
 208              		.cfi_endproc
 209              	.LFE2:
 211 0006 C046     		.section	.text.SVCall_Handler,"ax",%progbits
 212              		.align	2
 213              		.weak	SVCall_Handler
 214              		.code	16
 215              		.thumb_func
 217              	SVCall_Handler:
 218              	.LFB3:
 257:../src/cr_startup_lpc11.c **** }
 258:../src/cr_startup_lpc11.c **** 
 259:../src/cr_startup_lpc11.c **** void SVCall_Handler(void)
 260:../src/cr_startup_lpc11.c **** {
 219              		.loc 1 260 0
 220              		.cfi_startproc
 221              		@ args = 0, pretend = 0, frame = 0
 222              		@ frame_needed = 1, uses_anonymous_args = 0
 223 0000 80B5     		push	{r7, lr}
 224              		.cfi_def_cfa_offset 8
 225              		.cfi_offset 7, -8
 226              		.cfi_offset 14, -4
 227 0002 00AF     		add	r7, sp, #0
 228              		.cfi_def_cfa_register 7
 229              	.L15:
 261:../src/cr_startup_lpc11.c ****     while(1)
 262:../src/cr_startup_lpc11.c ****     {
 263:../src/cr_startup_lpc11.c ****     }
 230              		.loc 1 263 0 discriminator 1
 231 0004 FEE7     		b	.L15
 232              		.cfi_endproc
 233              	.LFE3:
 235 0006 C046     		.section	.text.PendSV_Handler,"ax",%progbits
 236              		.align	2
 237              		.weak	PendSV_Handler
 238              		.code	16
 239              		.thumb_func
 241              	PendSV_Handler:
 242              	.LFB4:
 264:../src/cr_startup_lpc11.c **** }
 265:../src/cr_startup_lpc11.c **** 
 266:../src/cr_startup_lpc11.c **** void PendSV_Handler(void)
 267:../src/cr_startup_lpc11.c **** {
 243              		.loc 1 267 0
 244              		.cfi_startproc
 245              		@ args = 0, pretend = 0, frame = 0
 246              		@ frame_needed = 1, uses_anonymous_args = 0
 247 0000 80B5     		push	{r7, lr}
 248              		.cfi_def_cfa_offset 8
 249              		.cfi_offset 7, -8
 250              		.cfi_offset 14, -4
 251 0002 00AF     		add	r7, sp, #0
 252              		.cfi_def_cfa_register 7
 253              	.L17:
 268:../src/cr_startup_lpc11.c ****     while(1)
 269:../src/cr_startup_lpc11.c ****     {
 270:../src/cr_startup_lpc11.c ****     }
 254              		.loc 1 270 0 discriminator 1
 255 0004 FEE7     		b	.L17
 256              		.cfi_endproc
 257              	.LFE4:
 259 0006 C046     		.section	.text.SysTick_Handler,"ax",%progbits
 260              		.align	2
 261              		.weak	SysTick_Handler
 262              		.code	16
 263              		.thumb_func
 265              	SysTick_Handler:
 266              	.LFB5:
 271:../src/cr_startup_lpc11.c **** }
 272:../src/cr_startup_lpc11.c **** 
 273:../src/cr_startup_lpc11.c **** void SysTick_Handler(void)
 274:../src/cr_startup_lpc11.c **** {
 267              		.loc 1 274 0
 268              		.cfi_startproc
 269              		@ args = 0, pretend = 0, frame = 0
 270              		@ frame_needed = 1, uses_anonymous_args = 0
 271 0000 80B5     		push	{r7, lr}
 272              		.cfi_def_cfa_offset 8
 273              		.cfi_offset 7, -8
 274              		.cfi_offset 14, -4
 275 0002 00AF     		add	r7, sp, #0
 276              		.cfi_def_cfa_register 7
 277              	.L19:
 275:../src/cr_startup_lpc11.c ****     while(1)
 276:../src/cr_startup_lpc11.c ****     {
 277:../src/cr_startup_lpc11.c ****     }
 278              		.loc 1 277 0 discriminator 1
 279 0004 FEE7     		b	.L19
 280              		.cfi_endproc
 281              	.LFE5:
 283 0006 C046     		.section	.text.IntDefaultHandler,"ax",%progbits
 284              		.align	2
 285              		.global	IntDefaultHandler
 286              		.code	16
 287              		.thumb_func
 289              	IntDefaultHandler:
 290              	.LFB6:
 278:../src/cr_startup_lpc11.c **** }
 279:../src/cr_startup_lpc11.c **** 
 280:../src/cr_startup_lpc11.c **** 
 281:../src/cr_startup_lpc11.c **** 
 282:../src/cr_startup_lpc11.c **** //*****************************************************************************
 283:../src/cr_startup_lpc11.c **** //
 284:../src/cr_startup_lpc11.c **** // This is the code that gets called when the processor receives an unexpected
 285:../src/cr_startup_lpc11.c **** // interrupt.  This simply enters an infinite loop, preserving the system state
 286:../src/cr_startup_lpc11.c **** // for examination by a debugger.
 287:../src/cr_startup_lpc11.c **** //
 288:../src/cr_startup_lpc11.c **** //*****************************************************************************
 289:../src/cr_startup_lpc11.c **** void IntDefaultHandler(void)
 290:../src/cr_startup_lpc11.c **** {
 291              		.loc 1 290 0
 292              		.cfi_startproc
 293              		@ args = 0, pretend = 0, frame = 0
 294              		@ frame_needed = 1, uses_anonymous_args = 0
 295 0000 80B5     		push	{r7, lr}
 296              		.cfi_def_cfa_offset 8
 297              		.cfi_offset 7, -8
 298              		.cfi_offset 14, -4
 299 0002 00AF     		add	r7, sp, #0
 300              		.cfi_def_cfa_register 7
 301              	.L21:
 291:../src/cr_startup_lpc11.c ****     //
 292:../src/cr_startup_lpc11.c ****     // Go into an infinite loop.
 293:../src/cr_startup_lpc11.c ****     //
 294:../src/cr_startup_lpc11.c ****     while(1)
 295:../src/cr_startup_lpc11.c ****     {
 296:../src/cr_startup_lpc11.c ****     }
 302              		.loc 1 296 0 discriminator 1
 303 0004 FEE7     		b	.L21
 304              		.cfi_endproc
 305              	.LFE6:
 307              		.weak	WAKEUP_IRQHandler
 308              		.thumb_set WAKEUP_IRQHandler,IntDefaultHandler
 309              		.weak	PIOINT0_IRQHandler
 310              		.thumb_set PIOINT0_IRQHandler,IntDefaultHandler
 311              		.weak	PIOINT1_IRQHandler
 312              		.thumb_set PIOINT1_IRQHandler,IntDefaultHandler
 313              		.weak	PIOINT2_IRQHandler
 314              		.thumb_set PIOINT2_IRQHandler,IntDefaultHandler
 315              		.weak	PIOINT3_IRQHandler
 316              		.thumb_set PIOINT3_IRQHandler,IntDefaultHandler
 317              		.weak	FMC_IRQHandler
 318              		.thumb_set FMC_IRQHandler,IntDefaultHandler
 319              		.weak	BOD_IRQHandler
 320              		.thumb_set BOD_IRQHandler,IntDefaultHandler
 321              		.weak	WDT_IRQHandler
 322              		.thumb_set WDT_IRQHandler,IntDefaultHandler
 323              		.weak	ADC_IRQHandler
 324              		.thumb_set ADC_IRQHandler,IntDefaultHandler
 325              		.weak	USB_FIQHandler
 326              		.thumb_set USB_FIQHandler,IntDefaultHandler
 327              		.weak	USB_IRQHandler
 328              		.thumb_set USB_IRQHandler,IntDefaultHandler
 329              		.weak	UART_IRQHandler
 330              		.thumb_set UART_IRQHandler,IntDefaultHandler
 331              		.weak	SSP_IRQHandler
 332              		.thumb_set SSP_IRQHandler,IntDefaultHandler
 333              		.weak	TIMER32_1_IRQHandler
 334              		.thumb_set TIMER32_1_IRQHandler,IntDefaultHandler
 335              		.weak	TIMER32_0_IRQHandler
 336              		.thumb_set TIMER32_0_IRQHandler,IntDefaultHandler
 337              		.weak	TIMER16_1_IRQHandler
 338              		.thumb_set TIMER16_1_IRQHandler,IntDefaultHandler
 339              		.weak	TIMER16_0_IRQHandler
 340              		.thumb_set TIMER16_0_IRQHandler,IntDefaultHandler
 341              		.weak	I2C_IRQHandler
 342              		.thumb_set I2C_IRQHandler,IntDefaultHandler
 343              		.weak	main
 344              		.weak	__main
 345 0006 C046     		.text
 346              	.Letext0:
DEFINED SYMBOLS
                            *ABS*:00000000 cr_startup_lpc11.c
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:24     .isr_vector:00000000 g_pfnVectors
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:21     .isr_vector:00000000 $d
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:79     .text.Reset_Handler:00000000 ResetISR
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:169    .text.NMI_Handler:00000000 NMI_Handler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:193    .text.HardFault_Handler:00000000 HardFault_Handler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:217    .text.SVCall_Handler:00000000 SVCall_Handler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:241    .text.PendSV_Handler:00000000 PendSV_Handler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:265    .text.SysTick_Handler:00000000 SysTick_Handler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:289    .text.IntDefaultHandler:00000000 WAKEUP_IRQHandler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:289    .text.IntDefaultHandler:00000000 I2C_IRQHandler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:289    .text.IntDefaultHandler:00000000 TIMER16_0_IRQHandler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:289    .text.IntDefaultHandler:00000000 TIMER16_1_IRQHandler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:289    .text.IntDefaultHandler:00000000 TIMER32_0_IRQHandler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:289    .text.IntDefaultHandler:00000000 TIMER32_1_IRQHandler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:289    .text.IntDefaultHandler:00000000 SSP_IRQHandler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:289    .text.IntDefaultHandler:00000000 UART_IRQHandler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:289    .text.IntDefaultHandler:00000000 USB_IRQHandler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:289    .text.IntDefaultHandler:00000000 USB_FIQHandler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:289    .text.IntDefaultHandler:00000000 ADC_IRQHandler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:289    .text.IntDefaultHandler:00000000 WDT_IRQHandler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:289    .text.IntDefaultHandler:00000000 BOD_IRQHandler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:289    .text.IntDefaultHandler:00000000 FMC_IRQHandler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:289    .text.IntDefaultHandler:00000000 PIOINT3_IRQHandler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:289    .text.IntDefaultHandler:00000000 PIOINT2_IRQHandler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:289    .text.IntDefaultHandler:00000000 PIOINT1_IRQHandler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:289    .text.IntDefaultHandler:00000000 PIOINT0_IRQHandler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:74     .text.Reset_Handler:00000000 $t
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:79     .text.Reset_Handler:00000000 Reset_Handler
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:152    .text.Reset_Handler:00000054 $d
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:164    .text.NMI_Handler:00000000 $t
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:188    .text.HardFault_Handler:00000000 $t
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:212    .text.SVCall_Handler:00000000 $t
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:236    .text.PendSV_Handler:00000000 $t
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:260    .text.SysTick_Handler:00000000 $t
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:284    .text.IntDefaultHandler:00000000 $t
C:\Users\dell\AppData\Local\Temp\ccWJtlZn.s:289    .text.IntDefaultHandler:00000000 IntDefaultHandler
                     .debug_frame:00000010 $d
                           .group:00000000 wm4.0.935e200dcf4f236f804f4066baa4d700

UNDEFINED SYMBOLS
_vStackTop
__main
main
_etext
_data
_edata
_bss
_ebss

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
  11              		.file	"cr_startup_lpc11.c"
  12              		.text
  13              	.Ltext0:
  14              		.cfi_sections	.debug_frame
  15              		.global	g_pfnVectors
  16              		.section	.isr_vector,"a",%progbits
  17              		.align	2
  20              	g_pfnVectors:
  21 0000 00000000 		.word	_vStackTop
  22 0004 00000000 		.word	ResetISR
  23 0008 00000000 		.word	NMI_Handler
  24 000c 00000000 		.word	HardFault_Handler
  25 0010 00000000 		.word	0
  26 0014 00000000 		.word	0
  27 0018 00000000 		.word	0
  28 001c 00000000 		.word	0
  29 0020 00000000 		.word	0
  30 0024 00000000 		.word	0
  31 0028 00000000 		.word	0
  32 002c 00000000 		.word	SVCall_Handler
  33 0030 00000000 		.word	0
  34 0034 00000000 		.word	0
  35 0038 00000000 		.word	PendSV_Handler
  36 003c 00000000 		.word	SysTick_Handler
  37 0040 00000000 		.word	WAKEUP_IRQHandler
  38 0044 00000000 		.word	WAKEUP_IRQHandler
  39 0048 00000000 		.word	WAKEUP_IRQHandler
  40 004c 00000000 		.word	WAKEUP_IRQHandler
  41 0050 00000000 		.word	WAKEUP_IRQHandler
  42 0054 00000000 		.word	WAKEUP_IRQHandler
  43 0058 00000000 		.word	WAKEUP_IRQHandler
  44 005c 00000000 		.word	WAKEUP_IRQHandler
  45 0060 00000000 		.word	WAKEUP_IRQHandler
  46 0064 00000000 		.word	WAKEUP_IRQHandler
  47 0068 00000000 		.word	WAKEUP_IRQHandler
  48 006c 00000000 		.word	WAKEUP_IRQHandler
  49 0070 00000000 		.word	WAKEUP_IRQHandler
  50 0074 00000000 		.word	WAKEUP_IRQHandler
  51 0078 00000000 		.word	WAKEUP_IRQHandler
  52 007c 00000000 		.word	I2C_IRQHandler
  53 0080 00000000 		.word	TIMER16_0_IRQHandler
  54 0084 00000000 		.word	TIMER16_1_IRQHandler
  55 0088 00000000 		.word	TIMER32_0_IRQHandler
  56 008c 00000000 		.word	TIMER32_1_IRQHandler
  57 0090 00000000 		.word	SSP_IRQHandler
  58 0094 00000000 		.word	UART_IRQHandler
  59 0098 00000000 		.word	USB_IRQHandler
  60 009c 00000000 		.word	USB_FIQHandler
  61 00a0 00000000 		.word	ADC_IRQHandler
  62 00a4 00000000 		.word	WDT_IRQHandler
  63 00a8 00000000 		.word	BOD_IRQHandler
  64 00ac 00000000 		.word	FMC_IRQHandler
  65 00b0 00000000 		.word	PIOINT3_IRQHandler
  66 00b4 00000000 		.word	PIOINT2_IRQHandler
  67 00b8 00000000 		.word	PIOINT1_IRQHandler
  68 00bc 00000000 		.word	PIOINT0_IRQHandler
  69              		.section	.text.Reset_Handler,"ax",%progbits
  70              		.align	1
  71              		.global	Reset_Handler
  72              		.syntax unified
  73              		.code	16
  74              		.thumb_func
  75              		.fpu softvfp
  77              	Reset_Handler:
  78              	.LFB0:
  79              		.file 1 "../src/cr_startup_lpc11.c"
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
  80              		.loc 1 186 0
  81              		.cfi_startproc
  82              		@ args = 0, pretend = 0, frame = 8
  83              		@ frame_needed = 1, uses_anonymous_args = 0
  84 0000 80B5     		push	{r7, lr}
  85              		.cfi_def_cfa_offset 8
  86              		.cfi_offset 7, -8
  87              		.cfi_offset 14, -4
  88 0002 82B0     		sub	sp, sp, #8
  89              		.cfi_def_cfa_offset 16
  90 0004 00AF     		add	r7, sp, #0
  91              		.cfi_def_cfa_register 7
 187:../src/cr_startup_lpc11.c ****     unsigned char *pulSrc, *pulDest;
 188:../src/cr_startup_lpc11.c **** 
 189:../src/cr_startup_lpc11.c ****     //
 190:../src/cr_startup_lpc11.c ****     // Copy the data segment initializers from flash to SRAM.
 191:../src/cr_startup_lpc11.c ****     //
 192:../src/cr_startup_lpc11.c ****     pulSrc = &_etext;
  92              		.loc 1 192 0
  93 0006 134B     		ldr	r3, .L9
  94 0008 7B60     		str	r3, [r7, #4]
 193:../src/cr_startup_lpc11.c ****     for(pulDest = &_data; pulDest < &_edata; )
  95              		.loc 1 193 0
  96 000a 134B     		ldr	r3, .L9+4
  97 000c 3B60     		str	r3, [r7]
  98 000e 07E0     		b	.L2
  99              	.L3:
 194:../src/cr_startup_lpc11.c ****     {
 195:../src/cr_startup_lpc11.c ****         *pulDest++ = *pulSrc++;
 100              		.loc 1 195 0
 101 0010 7A68     		ldr	r2, [r7, #4]
 102 0012 531C     		adds	r3, r2, #1
 103 0014 7B60     		str	r3, [r7, #4]
 104 0016 3B68     		ldr	r3, [r7]
 105 0018 591C     		adds	r1, r3, #1
 106 001a 3960     		str	r1, [r7]
 107 001c 1278     		ldrb	r2, [r2]
 108 001e 1A70     		strb	r2, [r3]
 109              	.L2:
 193:../src/cr_startup_lpc11.c ****     for(pulDest = &_data; pulDest < &_edata; )
 110              		.loc 1 193 0 discriminator 1
 111 0020 3A68     		ldr	r2, [r7]
 112 0022 0E4B     		ldr	r3, .L9+8
 113 0024 9A42     		cmp	r2, r3
 114 0026 F3D3     		bcc	.L3
 196:../src/cr_startup_lpc11.c ****     }
 197:../src/cr_startup_lpc11.c **** 
 198:../src/cr_startup_lpc11.c ****     //
 199:../src/cr_startup_lpc11.c ****     // Zero fill the bss segment.
 200:../src/cr_startup_lpc11.c ****     //
 201:../src/cr_startup_lpc11.c **** 	for(pulDest = &_bss; pulDest < &_ebss; pulDest++)
 115              		.loc 1 201 0
 116 0028 0D4B     		ldr	r3, .L9+12
 117 002a 3B60     		str	r3, [r7]
 118 002c 05E0     		b	.L4
 119              	.L5:
 202:../src/cr_startup_lpc11.c **** 	  *pulDest = 0;
 120              		.loc 1 202 0 discriminator 3
 121 002e 3B68     		ldr	r3, [r7]
 122 0030 0022     		movs	r2, #0
 123 0032 1A70     		strb	r2, [r3]
 201:../src/cr_startup_lpc11.c **** 	  *pulDest = 0;
 124              		.loc 1 201 0 discriminator 3
 125 0034 3B68     		ldr	r3, [r7]
 126 0036 0133     		adds	r3, r3, #1
 127 0038 3B60     		str	r3, [r7]
 128              	.L4:
 201:../src/cr_startup_lpc11.c **** 	  *pulDest = 0;
 129              		.loc 1 201 0 is_stmt 0 discriminator 1
 130 003a 3A68     		ldr	r2, [r7]
 131 003c 094B     		ldr	r3, .L9+16
 132 003e 9A42     		cmp	r2, r3
 133 0040 F5D3     		bcc	.L5
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
 134              		.loc 1 212 0 is_stmt 1
 135 0042 094B     		ldr	r3, .L9+20
 136 0044 002B     		cmp	r3, #0
 137 0046 02D0     		beq	.L6
 213:../src/cr_startup_lpc11.c **** 		__main() ;
 138              		.loc 1 213 0
 139 0048 FFF7FEFF 		bl	__main
 140 004c 01E0     		b	.L7
 141              	.L6:
 214:../src/cr_startup_lpc11.c **** 	else
 215:../src/cr_startup_lpc11.c **** 		main() ;
 142              		.loc 1 215 0
 143 004e FFF7FEFF 		bl	main
 144              	.L7:
 145              	.L8:
 216:../src/cr_startup_lpc11.c **** 
 217:../src/cr_startup_lpc11.c **** 	//
 218:../src/cr_startup_lpc11.c **** 	// main() shouldn't return, but if it does, we'll just enter an infinite loop 
 219:../src/cr_startup_lpc11.c **** 	//
 220:../src/cr_startup_lpc11.c **** 	while (1) {
 146              		.loc 1 220 0 discriminator 1
 147 0052 FEE7     		b	.L8
 148              	.L10:
 149              		.align	2
 150              	.L9:
 151 0054 00000000 		.word	_etext
 152 0058 00000000 		.word	_data
 153 005c 00000000 		.word	_edata
 154 0060 00000000 		.word	_bss
 155 0064 00000000 		.word	_ebss
 156 0068 00000000 		.word	__main
 157              		.cfi_endproc
 158              	.LFE0:
 160              		.weak	ResetISR
 161              		.thumb_set ResetISR,Reset_Handler
 162              		.section	.text.NMI_Handler,"ax",%progbits
 163              		.align	1
 164              		.weak	NMI_Handler
 165              		.syntax unified
 166              		.code	16
 167              		.thumb_func
 168              		.fpu softvfp
 170              	NMI_Handler:
 171              	.LFB1:
 221:../src/cr_startup_lpc11.c **** 		;
 222:../src/cr_startup_lpc11.c **** 	}
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
 172              		.loc 1 233 0
 173              		.cfi_startproc
 174              		@ args = 0, pretend = 0, frame = 0
 175              		@ frame_needed = 1, uses_anonymous_args = 0
 176 0000 80B5     		push	{r7, lr}
 177              		.cfi_def_cfa_offset 8
 178              		.cfi_offset 7, -8
 179              		.cfi_offset 14, -4
 180 0002 00AF     		add	r7, sp, #0
 181              		.cfi_def_cfa_register 7
 182              	.L12:
 234:../src/cr_startup_lpc11.c ****     //
 235:../src/cr_startup_lpc11.c ****     // Enter an infinite loop.
 236:../src/cr_startup_lpc11.c ****     //
 237:../src/cr_startup_lpc11.c ****     while(1)
 183              		.loc 1 237 0 discriminator 1
 184 0004 FEE7     		b	.L12
 185              		.cfi_endproc
 186              	.LFE1:
 188              		.section	.text.HardFault_Handler,"ax",%progbits
 189              		.align	1
 190              		.weak	HardFault_Handler
 191              		.syntax unified
 192              		.code	16
 193              		.thumb_func
 194              		.fpu softvfp
 196              	HardFault_Handler:
 197              	.LFB2:
 238:../src/cr_startup_lpc11.c ****     {
 239:../src/cr_startup_lpc11.c ****     }
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
 198              		.loc 1 250 0
 199              		.cfi_startproc
 200              		@ args = 0, pretend = 0, frame = 0
 201              		@ frame_needed = 1, uses_anonymous_args = 0
 202 0000 80B5     		push	{r7, lr}
 203              		.cfi_def_cfa_offset 8
 204              		.cfi_offset 7, -8
 205              		.cfi_offset 14, -4
 206 0002 00AF     		add	r7, sp, #0
 207              		.cfi_def_cfa_register 7
 208              	.L14:
 251:../src/cr_startup_lpc11.c ****     //
 252:../src/cr_startup_lpc11.c ****     // Enter an infinite loop.
 253:../src/cr_startup_lpc11.c ****     //
 254:../src/cr_startup_lpc11.c ****     while(1)
 209              		.loc 1 254 0 discriminator 1
 210 0004 FEE7     		b	.L14
 211              		.cfi_endproc
 212              	.LFE2:
 214              		.section	.text.SVCall_Handler,"ax",%progbits
 215              		.align	1
 216              		.weak	SVCall_Handler
 217              		.syntax unified
 218              		.code	16
 219              		.thumb_func
 220              		.fpu softvfp
 222              	SVCall_Handler:
 223              	.LFB3:
 255:../src/cr_startup_lpc11.c ****     {
 256:../src/cr_startup_lpc11.c ****     }
 257:../src/cr_startup_lpc11.c **** }
 258:../src/cr_startup_lpc11.c **** 
 259:../src/cr_startup_lpc11.c **** void SVCall_Handler(void)
 260:../src/cr_startup_lpc11.c **** {
 224              		.loc 1 260 0
 225              		.cfi_startproc
 226              		@ args = 0, pretend = 0, frame = 0
 227              		@ frame_needed = 1, uses_anonymous_args = 0
 228 0000 80B5     		push	{r7, lr}
 229              		.cfi_def_cfa_offset 8
 230              		.cfi_offset 7, -8
 231              		.cfi_offset 14, -4
 232 0002 00AF     		add	r7, sp, #0
 233              		.cfi_def_cfa_register 7
 234              	.L16:
 261:../src/cr_startup_lpc11.c ****     while(1)
 235              		.loc 1 261 0 discriminator 1
 236 0004 FEE7     		b	.L16
 237              		.cfi_endproc
 238              	.LFE3:
 240              		.section	.text.PendSV_Handler,"ax",%progbits
 241              		.align	1
 242              		.weak	PendSV_Handler
 243              		.syntax unified
 244              		.code	16
 245              		.thumb_func
 246              		.fpu softvfp
 248              	PendSV_Handler:
 249              	.LFB4:
 262:../src/cr_startup_lpc11.c ****     {
 263:../src/cr_startup_lpc11.c ****     }
 264:../src/cr_startup_lpc11.c **** }
 265:../src/cr_startup_lpc11.c **** 
 266:../src/cr_startup_lpc11.c **** void PendSV_Handler(void)
 267:../src/cr_startup_lpc11.c **** {
 250              		.loc 1 267 0
 251              		.cfi_startproc
 252              		@ args = 0, pretend = 0, frame = 0
 253              		@ frame_needed = 1, uses_anonymous_args = 0
 254 0000 80B5     		push	{r7, lr}
 255              		.cfi_def_cfa_offset 8
 256              		.cfi_offset 7, -8
 257              		.cfi_offset 14, -4
 258 0002 00AF     		add	r7, sp, #0
 259              		.cfi_def_cfa_register 7
 260              	.L18:
 268:../src/cr_startup_lpc11.c ****     while(1)
 261              		.loc 1 268 0 discriminator 1
 262 0004 FEE7     		b	.L18
 263              		.cfi_endproc
 264              	.LFE4:
 266              		.section	.text.SysTick_Handler,"ax",%progbits
 267              		.align	1
 268              		.weak	SysTick_Handler
 269              		.syntax unified
 270              		.code	16
 271              		.thumb_func
 272              		.fpu softvfp
 274              	SysTick_Handler:
 275              	.LFB5:
 269:../src/cr_startup_lpc11.c ****     {
 270:../src/cr_startup_lpc11.c ****     }
 271:../src/cr_startup_lpc11.c **** }
 272:../src/cr_startup_lpc11.c **** 
 273:../src/cr_startup_lpc11.c **** void SysTick_Handler(void)
 274:../src/cr_startup_lpc11.c **** {
 276              		.loc 1 274 0
 277              		.cfi_startproc
 278              		@ args = 0, pretend = 0, frame = 0
 279              		@ frame_needed = 1, uses_anonymous_args = 0
 280 0000 80B5     		push	{r7, lr}
 281              		.cfi_def_cfa_offset 8
 282              		.cfi_offset 7, -8
 283              		.cfi_offset 14, -4
 284 0002 00AF     		add	r7, sp, #0
 285              		.cfi_def_cfa_register 7
 286              	.L20:
 275:../src/cr_startup_lpc11.c ****     while(1)
 287              		.loc 1 275 0 discriminator 1
 288 0004 FEE7     		b	.L20
 289              		.cfi_endproc
 290              	.LFE5:
 292              		.section	.text.IntDefaultHandler,"ax",%progbits
 293              		.align	1
 294              		.global	IntDefaultHandler
 295              		.syntax unified
 296              		.code	16
 297              		.thumb_func
 298              		.fpu softvfp
 300              	IntDefaultHandler:
 301              	.LFB6:
 276:../src/cr_startup_lpc11.c ****     {
 277:../src/cr_startup_lpc11.c ****     }
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
 302              		.loc 1 290 0
 303              		.cfi_startproc
 304              		@ args = 0, pretend = 0, frame = 0
 305              		@ frame_needed = 1, uses_anonymous_args = 0
 306 0000 80B5     		push	{r7, lr}
 307              		.cfi_def_cfa_offset 8
 308              		.cfi_offset 7, -8
 309              		.cfi_offset 14, -4
 310 0002 00AF     		add	r7, sp, #0
 311              		.cfi_def_cfa_register 7
 312              	.L22:
 291:../src/cr_startup_lpc11.c ****     //
 292:../src/cr_startup_lpc11.c ****     // Go into an infinite loop.
 293:../src/cr_startup_lpc11.c ****     //
 294:../src/cr_startup_lpc11.c ****     while(1)
 313              		.loc 1 294 0 discriminator 1
 314 0004 FEE7     		b	.L22
 315              		.cfi_endproc
 316              	.LFE6:
 318              		.weak	WAKEUP_IRQHandler
 319              		.thumb_set WAKEUP_IRQHandler,IntDefaultHandler
 320              		.weak	PIOINT0_IRQHandler
 321              		.thumb_set PIOINT0_IRQHandler,IntDefaultHandler
 322              		.weak	PIOINT1_IRQHandler
 323              		.thumb_set PIOINT1_IRQHandler,IntDefaultHandler
 324              		.weak	PIOINT2_IRQHandler
 325              		.thumb_set PIOINT2_IRQHandler,IntDefaultHandler
 326              		.weak	PIOINT3_IRQHandler
 327              		.thumb_set PIOINT3_IRQHandler,IntDefaultHandler
 328              		.weak	FMC_IRQHandler
 329              		.thumb_set FMC_IRQHandler,IntDefaultHandler
 330              		.weak	BOD_IRQHandler
 331              		.thumb_set BOD_IRQHandler,IntDefaultHandler
 332              		.weak	WDT_IRQHandler
 333              		.thumb_set WDT_IRQHandler,IntDefaultHandler
 334              		.weak	ADC_IRQHandler
 335              		.thumb_set ADC_IRQHandler,IntDefaultHandler
 336              		.weak	USB_FIQHandler
 337              		.thumb_set USB_FIQHandler,IntDefaultHandler
 338              		.weak	USB_IRQHandler
 339              		.thumb_set USB_IRQHandler,IntDefaultHandler
 340              		.weak	UART_IRQHandler
 341              		.thumb_set UART_IRQHandler,IntDefaultHandler
 342              		.weak	SSP_IRQHandler
 343              		.thumb_set SSP_IRQHandler,IntDefaultHandler
 344              		.weak	TIMER32_1_IRQHandler
 345              		.thumb_set TIMER32_1_IRQHandler,IntDefaultHandler
 346              		.weak	TIMER32_0_IRQHandler
 347              		.thumb_set TIMER32_0_IRQHandler,IntDefaultHandler
 348              		.weak	TIMER16_1_IRQHandler
 349              		.thumb_set TIMER16_1_IRQHandler,IntDefaultHandler
 350              		.weak	TIMER16_0_IRQHandler
 351              		.thumb_set TIMER16_0_IRQHandler,IntDefaultHandler
 352              		.weak	I2C_IRQHandler
 353              		.thumb_set I2C_IRQHandler,IntDefaultHandler
 354              		.weak	main
 355              		.weak	__main
 356              		.text
 357              	.Letext0:
DEFINED SYMBOLS
                            *ABS*:0000000000000000 cr_startup_lpc11.c
     /tmp/ccPcUIOf.s:20     .isr_vector:0000000000000000 g_pfnVectors
     /tmp/ccPcUIOf.s:17     .isr_vector:0000000000000000 $d
     /tmp/ccPcUIOf.s:77     .text.Reset_Handler:0000000000000000 ResetISR
     /tmp/ccPcUIOf.s:170    .text.NMI_Handler:0000000000000000 NMI_Handler
     /tmp/ccPcUIOf.s:196    .text.HardFault_Handler:0000000000000000 HardFault_Handler
     /tmp/ccPcUIOf.s:222    .text.SVCall_Handler:0000000000000000 SVCall_Handler
     /tmp/ccPcUIOf.s:248    .text.PendSV_Handler:0000000000000000 PendSV_Handler
     /tmp/ccPcUIOf.s:274    .text.SysTick_Handler:0000000000000000 SysTick_Handler
     /tmp/ccPcUIOf.s:300    .text.IntDefaultHandler:0000000000000000 WAKEUP_IRQHandler
     /tmp/ccPcUIOf.s:300    .text.IntDefaultHandler:0000000000000000 I2C_IRQHandler
     /tmp/ccPcUIOf.s:300    .text.IntDefaultHandler:0000000000000000 TIMER16_0_IRQHandler
     /tmp/ccPcUIOf.s:300    .text.IntDefaultHandler:0000000000000000 TIMER16_1_IRQHandler
     /tmp/ccPcUIOf.s:300    .text.IntDefaultHandler:0000000000000000 TIMER32_0_IRQHandler
     /tmp/ccPcUIOf.s:300    .text.IntDefaultHandler:0000000000000000 TIMER32_1_IRQHandler
     /tmp/ccPcUIOf.s:300    .text.IntDefaultHandler:0000000000000000 SSP_IRQHandler
     /tmp/ccPcUIOf.s:300    .text.IntDefaultHandler:0000000000000000 UART_IRQHandler
     /tmp/ccPcUIOf.s:300    .text.IntDefaultHandler:0000000000000000 USB_IRQHandler
     /tmp/ccPcUIOf.s:300    .text.IntDefaultHandler:0000000000000000 USB_FIQHandler
     /tmp/ccPcUIOf.s:300    .text.IntDefaultHandler:0000000000000000 ADC_IRQHandler
     /tmp/ccPcUIOf.s:300    .text.IntDefaultHandler:0000000000000000 WDT_IRQHandler
     /tmp/ccPcUIOf.s:300    .text.IntDefaultHandler:0000000000000000 BOD_IRQHandler
     /tmp/ccPcUIOf.s:300    .text.IntDefaultHandler:0000000000000000 FMC_IRQHandler
     /tmp/ccPcUIOf.s:300    .text.IntDefaultHandler:0000000000000000 PIOINT3_IRQHandler
     /tmp/ccPcUIOf.s:300    .text.IntDefaultHandler:0000000000000000 PIOINT2_IRQHandler
     /tmp/ccPcUIOf.s:300    .text.IntDefaultHandler:0000000000000000 PIOINT1_IRQHandler
     /tmp/ccPcUIOf.s:300    .text.IntDefaultHandler:0000000000000000 PIOINT0_IRQHandler
     /tmp/ccPcUIOf.s:70     .text.Reset_Handler:0000000000000000 $t
     /tmp/ccPcUIOf.s:77     .text.Reset_Handler:0000000000000000 Reset_Handler
     /tmp/ccPcUIOf.s:151    .text.Reset_Handler:0000000000000054 $d
     /tmp/ccPcUIOf.s:163    .text.NMI_Handler:0000000000000000 $t
     /tmp/ccPcUIOf.s:189    .text.HardFault_Handler:0000000000000000 $t
     /tmp/ccPcUIOf.s:215    .text.SVCall_Handler:0000000000000000 $t
     /tmp/ccPcUIOf.s:241    .text.PendSV_Handler:0000000000000000 $t
     /tmp/ccPcUIOf.s:267    .text.SysTick_Handler:0000000000000000 $t
     /tmp/ccPcUIOf.s:293    .text.IntDefaultHandler:0000000000000000 $t
     /tmp/ccPcUIOf.s:300    .text.IntDefaultHandler:0000000000000000 IntDefaultHandler
                           .group:0000000000000000 wm4.0.a91a75295d12acab8a45dbf128a8bd68

UNDEFINED SYMBOLS
_vStackTop
__main
main
_etext
_data
_edata
_bss
_ebss

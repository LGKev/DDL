/*****************************************************************************
 *   config.h:  config file for blinky example for NXP LPC11xx Family
 *   Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.12.07  ver 1.00    Preliminary version, first Release
 *
******************************************************************************/

//#define ADC_DEBUG				1	// For the demo code, we run in debug mode
#define SEMIHOSTED_ADC_OUTPUT	1	// Generate printf output in the debugger
#define OUTPUT_ONLY_CH0			1	// We only output channel 0- this channel has
									// a potentiometer on it on the LPCXpresso
									// baseboard.


#define LED_PORT_R 0		// Port for red led
#define LED_BIT_R 7		// Bit on port for red led

#define LED_PORT_G 0		// Port for green led
#define LED_BIT_G 8		// Bit on port for green led

#define LED_PORT_B 0		// Port for blue led
#define LED_BIT_B 9		// Bit on port for blue led

#define LED_ON 0		// Level to set port to turn on led
#define LED_OFF 1		// Level to set port to turn off led
#define LED_TOGGLE_TICKS 100 // 100 ticks = 1 Hz flash rate
#define FAST_LED_TOGGLE_TICKS 50 // 100 ticks = 1 Hz flash rate
#define COUNT_MAX		3 // how high to count on the LED display

/*********************************************************************************
**                            End Of File
*********************************************************************************/

/*
===============================================================================
 Name        : DDL_Lab4.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC11xx.h"
#endif

#include <cr_section_macros.h>
#define PIN2_1 			(0b10) //2
#define PIN0_7			(0b111) //7

/**
 * @brief Configures GPIO: Pins 2.1(interrupt) , 0.7 (LED)
 * 	interrupt 2.1:
 * 		rising edge
 * 	LED 0.7:
 * 		represents the frequency read, and modifies duty cycle
 * 		25% and 75%
 */
void GPIOInit(void);



/**
 * @brief Configures the Timer0 32 bit timer. Configured for a 1ms ticking, 
 * 	though nyquist suggests .5ms is a better timer interval
 */
void TIMER32Init(void);



/**
 * @brief When the interrupt (rising) is tirggered, this is what is ran. 
 * 	use it to start and stop time, get a period measurement
 * @globals: I know I will have a bunch, something like a count to let us know how 
 * many zero crossings we've had, a start/stop flag,   
 */
void PIOINT2_IRQHandler(void);

/**
 * @brief Configured to trigger every 1ms (0.5ms tbd). 
 * @globals: something to parse time out for 25% and 75% duty cycles
 * 	a few more because we have timing for led, 
 */
void TIMER32_0_IRQHandler(void);


int main(void) {

	GPIOInit();
//	TIMER3Init();


	while(1){
		LPC_GPIO0 -> DATA |= 0b01000000; //all on
		LPC_GPIO0 -> DATA = 0x00; //all off
	}
    return 0 ;
}


void GPIOInit(void){
	//iocon_piio2.1 interrupt, probably want pulldown.
	// 31:11 reserved.
	//10-0: 00011001000 (binary): hex: 003020
	LPC_IOCON -> PIO2_1 = 0x003020; //gpio, pull down, no hysterisis, standar gpio
	LPC_GPIO2 -> DIR &= ~PIN2_1; //only pin2 is an input! 0 is input 1 is output
	LPC_GPIO2 -> IS &= ~PIN2_1; //edge triggered, i think that is the rising case...
	LPC_GPIO2 -> IBE &= ~PIN2_1; //default should be fine, but never too careful
	LPC_GPIO2 -> IEV |= PIN2_1; // set rising EDGE

	// TODO: need to register with the NVIC
	// TODO: enable global interrupts


	//iocon_pio0.7 led
	//10-0: 0 0011 0  00 000 -> hex: 003000
	LPC_IOCON -> PIO0_7 =  0x003000;
	LPC_GPIO0 -> DIR |= 0xFFF; //output red led btw make them all outputs!
	LPC_GPIO0 -> DATA = 0X00; //turn  all off
        // NO need for interrupt stuff	
}

void TIMER32Init(void){

}

void PIOINT2_IRQHandler(void){

}





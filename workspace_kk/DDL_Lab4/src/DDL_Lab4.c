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
#define PIN2_1 			(0b000000000010) //2
//#define PIN2_1 			(0b10) //2
#define PIN0_7			(0b000001000000) //7
//#define PIN0_7			(0b111) //7

#define LED_G_P0_8		(0xEFF)
#define LED_B_P0_9		(0xDFF)
#define LED_R_P0_7		(0xF7F)
#define LED_WHITE		(0xC7F)
#define LED_OFF			(0xFFF)
/**
 * @brief Configures GPIO: Pins 2.1(interrupt) , 0.7 (LED)
 * 	Enables APB Clock, APB- peripheral bus,clock needed, for peripherals: GPIO
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
// TODO: you're going to need some jumper cables to do a test for interrupt
void PIOINT2_IRQHandler(void);

/**
 * @brief Configured to trigger every 1ms (0.5ms tbd). 
 * @globals: something to parse time out for 25% and 75% duty cycles
 * 	a few more because we have timing for led, 
 */
void TIMER32_0_IRQHandler(void);


int main(void) {

	GPIOInit();
	TIMER32Init();


	while(1){
		//LPC_GPIO0 -> DATA |= 0b1110000000; //all on
		//LPC_GPIO0 -> DATA &= ~0b1110000000; //all off
	}
    return 0 ;
}


void GPIOInit(void){
	// configure clock for APB/ AHB
	// technically the reset value is 1, for gpio. as in already set. 
	LPC_SYSCON -> SYSAHBCLKCTRL |= (1<<6) | (1<<16); //bit is the gpio enable
	//iocon bit 16 is the io/ block clock enable

	//iocon_piio2.1 interrupt, probably want pulldown.
	// 31:11 reserved.
	//10-0: 00011001000 (binary): hex: 003020
	LPC_IOCON -> PIO2_1 = 0x003020; //gpio, pull down, no hysterisis, standar gpio
	LPC_GPIO2 -> DIR &= ~PIN2_1; //only pin2 is an input! 0 is input 1 is output
	LPC_GPIO2 -> IS &= ~PIN2_1; //edge triggered, i think that is the rising case...
	LPC_GPIO2 -> IBE &= ~PIN2_1; //default should be fine, but never too careful
	LPC_GPIO2 -> IEV |= PIN2_1; // set rising EDGE

	// TODO: need to register with the NVIC
	  NVIC_EnableIRQ(EINT2_IRQn); //port2 external interrupt
	// TODO: enable global interrupts


	//iocon_pio0.7 led
	//10-0: 0 0011 0  00 000 -> hex: 003000
	LPC_IOCON -> PIO0_7 = 0xd0; //0xd0 default will work. but never too sure
	LPC_GPIO0 -> DIR |= 0xFFF; //output red led btw make them all outputs!
	// the led's configured such that a GPIO:0 is on, and GPIO:1 is off.
	LPC_GPIO0 -> DATA |= LED_OFF; //turn  all off
        // NO need for interrupt stuff	
}



/**
 * @brief "21.2 Basic Configuration"
 * 	CT32B_0 are configured using the following registers:
 * 		pins: ct32b0 pins must be configured in the IOCONFIG register (7.4)
 *			// I think above is for if you wanted to change GPIO to clock source output.
 * 		power and peripheral clock: set bit 9 (timer32_0, bit 10 for 32_1)
 *
 * 		The internal RC Oscillator is the main clock. must be chanced to use external crystal
 * 		IRC frequency: 12 MHz >> main clock >> (ahb div = 1)  >> system clock = 12MHz
 */
void TIMER32Init(void){
// check 7.4 for pins for the 32 bit timer, IOCONFIG, some are used for jtag
	// check table 21/20 for power and peripheral blocks

	//enable clocks for timer32
	LPC_SYSCON -> SYSAHBCLKCTRL |= (1<<9); //bit 9 is timer32_0

	// we want interrupts, so TMR32B0_IR

		
	// we want to set the prescale divisor to get .5 mS resolution
		// 	recall, system clock is feeding APB
	LPC_TMR32B0 -> TCR |= (1<<0); // enable timer
	LPC_TMR32B0 -> TCR |= (1<<1); //reset timer
	LPC_TMR32B0 -> TCR &= ~(1<<1); //set bit 1 to zero.
	LPC_TMR32B0 -> TC = 0; // reset counter

	//set for 0.5ms tick count? lets not for now, maybe later,
	// currently we tick counter each time, and were at 1/12Mhz per tick.
	
	// we want to set what happens on a match, so TMR32B0_MCR and MCR0
	LPC_TMR32B0 -> MCR |= (1<<1); // enable reset for TMR32b0, when match0
	LPC_TMR32B0 -> MCR |= (1<<0); // enable interrupt for TMR32b0, when match0
	LPC_TMR32B0 -> MR0 = 12000000; //value we count up to

	NVIC_EnableIRQ(TIMER_32_0_IRQn); //timer32b timer0 interrupt
}

//gloabl
uint8_t toggle = 0;


//TODO: the gpio interrupt handler will most likely set MAtch 1 and 0 values. 
void PIOINT2_IRQHandler(void){

	//clear the flag, check the flag, light an led
	if(LPC_GPIO2 -> MIS & 0b10){
		//interrupt happened, clear that bit
		LPC_GPIO2 -> IC |= 0b10; //1 to the clear register clears that bit

		/*TODO: logic for timing */
		//could we just use system tick here? and get the difference?

		if(toggle == 0){
		LPC_GPIO0 -> DATA &= ~LED_WHITE; //on
		toggle = 1;
		}
		else{
		LPC_GPIO0 -> DATA |= LED_WHITE; //on
		toggle = 0;
		}
	}
}


// global

uint8_t quartlet = 0; //quarter of the peirod because 25% and 75% are multiples of 1/4
void TIMER32_0_IRQHandler(void){

	//check which source fired
	if(LPC_TMR32B0 -> IR |= (1<<0)){ //match0
		//clear interrupt
		LPC_TMR32B0 -> IR &= ~(1<<0);


		if(quartlet == 0){
		LPC_GPIO0 -> DATA &= ~LED_G_P0_8; //on
		quartlet++;
		return;
		}
		
		if(quartlet >= 1){
		LPC_GPIO0-> DATA |= LED_G_P0_8; //off
		quartlet++;
			if(quartlet == 5){
				quartlet = 0;//reset get ready to turn led back on.
				return;
			}	
		}
	} //end of match0
	if(LPC_TMR32B0 -> IR |= (1<<1)){ //match1
		LPC_TMR32B0 -> IR &= ~(1<<1); //clear flag
		return;
	}//end of match1
}

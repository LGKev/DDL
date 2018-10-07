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


void sysTickInit(void);


int main(void) {

	GPIOInit();
	sysTickInit(); //enable the systick
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
	//10-0: 00011001000 (binary): hex: 0C8
	LPC_IOCON -> PIO2_1 = 0xC8; //gpio, pull down, no hysterisis, standar gpio
	LPC_GPIO2 -> DIR &= ~PIN2_1; //only pin2 is an input! 0 is input 1 is output
	LPC_GPIO2 -> IS &= ~PIN2_1; //edge triggered, i think that is the rising case...
	LPC_GPIO2 -> IBE &= ~PIN2_1; //default should be fine, but never too careful
	LPC_GPIO2 -> IEV |= PIN2_1; // set rising EDGE
	LPC_GPIO2 -> IE |= PIN2_1; // do not mask.

	LPC_GPIO2 -> IC = 0xFFF; //12 1's
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
	LPC_TMR32B0 -> MCR |= (1<<1); // enable reset of TC on match MR0
	LPC_TMR32B0 -> MCR |= (1<<0); // enable interrupt for TMR32b0, when match0
	LPC_TMR32B0 -> MR0 = 12000000; //value we count up to
	LPC_TMR32B0 -> MR1 = 24000000; //value we count up to

	// NOTE: not using the mr1 so need to reset the TC when MR0 is matched
	//LPC_TMR32B0 -> MCR |= (1<<4) | (1<<3); // disable reset for TMR32b0, when match0, so we can do the toggling.


	NVIC_EnableIRQ(TIMER_32_0_IRQn); //timer32b timer0 interrupt
}


void sysTickInit(void){
	SysTick -> LOAD = 12000000;
	SysTick -> CTRL |= (1<<0) | (1<<2); // enable, and use system clock no div (fastest)
	//enable

}



//gloabl
uint8_t toggle = 0;
uint8_t zeroCrossing = 0;
uint32_t startTime;
uint32_t endTime;
uint32_t elapsedTime;
void PIOINT2_IRQHandler(void){

	//clear the flag, check the flag, light an led
	if(LPC_GPIO2 -> MIS & 0b10){
		//interrupt happened, clear that bit

		LPC_GPIO2 -> IC = 0b10; //1 to the clear register clears that bit
		/*TODO: logic for timing */
		//could we just use system tick here? and get the difference?

		if(zeroCrossing == 1){
		endTime = SysTick -> VAL;
			LPC_GPIO0 -> DATA |= LED_R_P0_7; // turn off blue led
			LPC_GPIO0 -> DATA |= LED_B_P0_9; // turn off blue led
			LPC_GPIO0 -> DATA &= ~LED_B_P0_9; // turn off blue led
			zeroCrossing = 0;
			return;
		}

		if(zeroCrossing == 0){
			LPC_GPIO0 -> DATA |= LED_B_P0_9;
			LPC_GPIO0 -> DATA |= LED_R_P0_7;
			LPC_GPIO0 -> DATA &= ~LED_R_P0_7;
			startTime = SysTick -> VAL;
			zeroCrossing = 1;
			return;
		}

	}
}

#ifdef GPIO_FULL_INTERRUPT

//TODO: the gpio interrupt handler will most likely set MAtch 1 and 0 values. 
void PIOINT2_IRQHandler(void){

	//clear the flag, check the flag, light an led
	if(LPC_GPIO2 -> MIS & 0b10){
		//interrupt happened, clear that bit
		LPC_GPIO2 -> IC |= 0b10; //1 to the clear register clears that bit

		/*TODO: logic for timing */
		//could we just use system tick here? and get the difference?

		if(zeroCrossing == 0){
			LPC_GPIO0 -> DATA &= ~LED_B_P0_9; //on
			LPC_GPIO0 -> DATA |= LED_R_P0_7; // turn off blue led
			startTime = SysTick -> VAL;
			zeroCrossing++;
			LPC_GPIO0 -> DATA &= ~LED_B_P0_9;
			return;
		}


		if(zeroCrossing == 1){
		endTime = SysTick -> VAL;
			LPC_GPIO0 -> DATA |= LED_B_P0_9; // turn off blue led
			LPC_GPIO0 -> DATA &= ~LED_R_P0_7; // turn off blue led

			if(endTime > startTime){ // over flowed.
				elapsedTime = endTime - startTime;
				zeroCrossing = 0;
				return;
			}
			else{   //normal
				elapsedTime = startTime - endTime;
				zeroCrossing = 0;
				return;
			}
		}

	}
}
#endif

// global

//		LPC_GPIO0 -> DATA &= ~LED_R_P0_7;



uint32_t numberOfMatchesIn_10s = 10;
uint32_t currentNumberOfMatches = 0;
uint8_t quartlet = 0; //quarter of the peirod because 25% and 75% are multiples of 1/4
uint8_t toggleDuty = 0; //this value is changed by the Match1 interrupt
#define FULL_INTERRUPT
#ifdef FULL_INTERRUPT
void TIMER32_0_IRQHandler(void){

	//check which source fired
	if(LPC_TMR32B0 -> IR &= (1<<0)){ //match0
		//clear interrupt
		LPC_TMR32B0 -> IR &= ~(1<<0);


/* check to see if we have had enough, and need to toggle duty cycles */
		if(currentNumberOfMatches == numberOfMatchesIn_10s){
			toggleDuty ^= 1; //toggle
			//reset
			currentNumberOfMatches = 0;
		}

		// TODO verify that the line below, TC = 0; is unnecessary now I have the proper If - else
		//LPC_TMR32B0 -> TC = 0; //TODO:
/* ======================================================== */
// 25 % duty cycle
/* ======================================================== */
		if(toggleDuty == 0){
			if(quartlet == 0){
				//on time 25% on
				LPC_GPIO0 -> DATA &= ~LED_R_P0_7;
				quartlet = 1;
			}
			else if(quartlet >= 1 && quartlet <4){
				//off time 75%
				LPC_GPIO0 -> DATA |= LED_R_P0_7;
				quartlet++;
				if(quartlet == 4){
					quartlet = 0; //reset
				}
			}
			else{ // redundant since the if within the else if above but never too sure?
				quartlet = 0;
			}
		}
/* ======================================================== */
// 75 % duty cycle
/* ======================================================== */
		else if(toggleDuty == 1){
			if(quartlet == 0){
				//on time 25% on
				LPC_GPIO0 -> DATA |= LED_R_P0_7;
				quartlet = 1;
			}
			else if(quartlet >= 1 && quartlet <4){
				//off time 75%
				LPC_GPIO0 -> DATA &= ~LED_R_P0_7;
				quartlet++;
				if(quartlet == 4){
					quartlet = 0; //reset
				}
			}
			else{ // redundant since the if within the else if above but never too sure?
				quartlet = 0;
			}
		}
/* ======================================================== */

		currentNumberOfMatches++; //increment everytime we had a timer interrupt
		return;
	} //end of match0

	if(LPC_TMR32B0 -> IR &= (1<<1)){ //match1 // 10 second period
		LPC_TMR32B0 -> IR &= ~(1<<1); //clear flag

		/*
		toggleDuty ^=1; //toggle!
		LPC_GPIO0 -> DATA &= ~LED_B_P0_9;
		LPC_GPIO0 -> DATA |= LED_R_P0_7;
		return;
	*/
	}//end of match1
}
#endif




//#define kevin
/*
 *
 * 	sysTick gives us the period.
 * 		period gives us the duration of one quarter.
 * 			this value is set to the MR0. with a reset of TC on match.
 * 				for 25% duty cycle: when MR0_count < 1 turn on led.
 * 					then when MR0_count >1, turn off led,
 * 						if MR0_count == 3; count = 0; reset.
 * 			Need to cacluate a counter of the Quarlet.  to determine the 10 second period.
 * 				question: how many times does the MR0 interrupt occur in a 10 second period
 * 					equation: 10 second / MR0_duration = number of times the MR0 interrupt occurs.
 * 					when we reach our number we change to the alternate duty cycle
 *
 *    */


#ifdef kevin
		if(toggleDuty == 1){
/*==================================================================================================*/
// This is the 25% duty cycle case
/*==================================================================================================*/
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
		}
		else if(toggleDuty ==0){
/*==================================================================================================*/
// This is the 75% duty cycle case
/*==================================================================================================*/
		if(quartlet == 0){
		quartlet++;
		LPC_GPIO0-> DATA |= LED_R_P0_7; //off
		return;
		}

		if(quartlet >= 1){
		LPC_GPIO0 -> DATA &= ~LED_R_P0_7; //on
		quartlet++;
			if(quartlet == 5){
				quartlet = 0;//reset get ready to turn led back on.
				return;
			}
		}
	} //end of the switch for 75% and 25% duty cycles
/*==================================================================================================*/








#endif

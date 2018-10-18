/****************************************************************************
 *   $Id:: uart_main.c 4824 2010-09-07 18:47:51Z nxp21346                   $
 *   Project: NXP LPC11xx UART example
 *
 *   Description:
 *     This file contains UART test modules, main entry, to test UART APIs.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#include "driver_config.h"
#include "target_config.h"
#include "timer32.h"
#include "uart.h"
#include "gpio.h"
#include "adc.h"

#include "LPC11xx.h"
#include <cr_section_macros.h>



// #define part1 //prints out hello world



#define PIN2_1 			(0b000000000010) //2
//#define PIN2_1 			(0b10) //2
#define PIN0_7			(0b000001000000) //7
//#define PIN0_7			(0b111) //7

#define LED_G_P0_8		(0xEFF)
#define LED_B_P0_9		(0xDFF)
#define LED_R_P0_7		(0xF7F)
#define LED_WHITE		(0xC7F)
#define LED_OFF			(0xFFF)


extern volatile uint32_t UARTCount;
extern volatile uint8_t UARTBuffer[BUFSIZE];

extern volatile uint32_t timer32_0_counter; //increments every 10ms, in the interrupt handler

//global
/* Fucntions tthat touch these globals:
 * 		-setLEDON
 * */
float currentDutyCycle = 0.5; //[percentage]
uint32_t currentPeriod = 100; // [miliseconds]

/*==================================== */


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

void idleState(uint8_t value);

void setLEDON(void);





//global
uint8_t uartCharReceived = 0;
uint32_t delay = 0;
uint8_t currentStateFlag = 0;


int main (void) {
	  /* Basic chip initialization is taken care of in SystemInit() called
	   * from the startup code. SystemInit() and chip settings are defined
	   * in the CMSIS system_<part family>.c file.
	   */

#ifdef part1
UARTBuffer[0]='h';
UARTBuffer[1]='E';
UARTBuffer[2]='L';
UARTBuffer[3]='L';
UARTBuffer[4]='O';
UARTBuffer[5]=' ';
UARTBuffer[6]='W';
UARTBuffer[7]='O';
UARTBuffer[8]='R';
UARTBuffer[9]='L';
UARTBuffer[10]='D';
UARTBuffer[11]='\n';
UARTBuffer[12]='\0';
#endif
  init_timer32(0, TIME_INTERVAL);
  enable_timer32(0);

  GPIOInit();


  /* NVIC is installed inside UARTInit file. */
  UARTInit(UART_BAUD);
 // UARTSend("AT", 3); //TODO fix this, something with line endings.
  //UARTSend((uint8_t)"AT+Set53", 9);

	//  UARTCount = 13;
  while (1) 
  {				/* Loop forever */

#ifdef part1
	  LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
	 UARTSend( (uint8_t *)UARTBuffer, UARTCount );


	  UARTCount = 13;
	  LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */
	  for(delay=0; delay<20000; delay++);


#endif

//part 2

	  /* CAPTURE the value form the uart */
	  /* ============================================================================================ */
	  if ( UARTCount != 0 ) //set by the interrupt handler
	  	{
	  	  LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
	  	  uartCharReceived = UARTBuffer[0];
	  	  UARTCount = 0;
	  	  LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */
	  	}
	  /* state machine, decide*/

if(currentStateFlag == 0){
	  if(uartCharReceived == '1'){
		  //turn on led >> State: LED Control
		  //set a flag to let us know what state we are in.i
		  currentStateFlag = 1;
	  }
	  else if(uartCharReceived == '2'){
		  //turn off led >> State: ADC Control
		  currentStateFlag = 2;
	  }
	  else{
		  //print out menu again
		  currentStateFlag = 0;
	  }
} // end of state 0

if(currentStateFlag == 1){
	/* checking to see if we are changing states */

	/* checking if we put in a menu option  */
	if(uartCharReceived == '1'){
		setLEDON();
	}
	else if(uartCharReceived == '2'){
	//	setLEDBlinkOff();
		LPC_GPIO0 ->DATA |= 0xfff; //TODO: no magic numbers.
	}
	else if(uartCharReceived == '3'){
		currentStateFlag = 4;
	}
	else if(uartCharReceived == '4'){
		currentStateFlag = 5;
	}
	else if(uartCharReceived == '5'){
		currentStateFlag = 0;
	}
	/* invalid input just stay in current state */
	else{
		currentStateFlag = 1; //spin
	}
} //end of state 1

if(currentStateFlag == 4){

	if(uartCharReceived == '6'){
		currentStateFlag = 1;
		//go to the duty cycle menu
	}
	else if(uartCharReceived == '1' ){
		//set duty cycle to 10%
		currentDutyCycle = 0.1;
	}
	else if(uartCharReceived == '2' ){
		//set duty cycle to 25%
		currentDutyCycle = 0.25;
	}
	else if(uartCharReceived == '3' ){
		//set duty cycle to 50%
		currentDutyCycle = 0.5;
	}
	else if(uartCharReceived == '4' ){
		//set duty cycle to 75%
		currentDutyCycle = 0.75;
	}
	else if(uartCharReceived == '5' ){
		//set duty cycle to 90%
		currentDutyCycle = 0.9;
	}
	else {
		currentStateFlag = 4; //do nothing just spin
	}
} //end of state 4

if(currentStateFlag == 5){
	if(uartCharReceived == '6'){
			currentStateFlag = 1; //go back up
		}
		else if(uartCharReceived == '1')
		{
			//slow freq
			currentPeriod = 1000;
			currentStateFlag = 1;
		}
		else if(uartCharReceived == '2')
		{
			//medium freq
			currentPeriod = 100;
			currentStateFlag = 1;
		}
		else if(uartCharReceived == '3')
		{
			//fast freq0
			currentPeriod = 50;
			currentStateFlag = 1;
		}
		else if(uartCharReceived == '4')
		{
			//verry fast
			currentPeriod = 25;
			currentStateFlag = 1;
		}
		else {
			currentStateFlag = 3; //do nothing just spin
		}

} //end of state 1

if(currentStateFlag == 2){

	if(uartCharReceived == '1'){
	// adc report on
	}
	else if(uartCharReceived == '2') {
	// adc report off
	}
	else if(uartCharReceived == '3') {
		//set report freq
	}else if(uartCharReceived == '4') {
		currentStateFlag = 0; //go back to the main menu
	}
	else{
		currentStateFlag = 2; //just spin
	}
} //end of state 2


if(currentStateFlag == 3){
	if(uartCharReceived == '5'){
			currentStateFlag = 2; //go back up
			//go to the duty cycle menu
		}
		else if(uartCharReceived == '1')
		{
			//slow freq
		}
		else if(uartCharReceived == '2')
		{
			//medium freq
		}
		else if(uartCharReceived == '3')
		{
			//fast freq
		}
		else if(uartCharReceived == '4')
		{
			//verry fast
		}
		else {
			currentStateFlag = 3; //do nothing just spin
		}

} //end of state 2







	  /* ============================================================================================ */
  }
}
/*
void idleState(uint8_t value){
	switch (value):
				case 1:

					break;
				case 2:
					break;
	default:
		break;
}
*/

void GPIOInit(void){
	// configure clock for APB/ AHB
	// technically the reset value is 1, for gpio. as in already set.
	LPC_SYSCON -> SYSAHBCLKCTRL |= (1<<6) | (1<<16); //bit is the gpio enable

	//iocon_pio0.7 led
	//10-0: 0 0011 0  00 000 -> hex: 003000
	LPC_IOCON -> PIO0_7 = 0xd0; //0xd0 default will work. but never too sure
	LPC_GPIO0 -> DIR |= 0xFFF; //output red led btw make them all outputs!
	// the led's configured such that a GPIO:0 is on, and GPIO:1 is off.
	LPC_GPIO0 -> DATA |= LED_OFF; //turn  all off
        // NO need for interrupt stuff
}



/* We need the following:
 * 	- period
 * 	- duty cycle
 * 	- currentTimerCount
 *
 * 	note: if we blink in a while loop, this can be interrupted by the uart IRQ.
 * 		if we get an interrupt we set a flag. but we return to the while loop. SO in the while loop check for the same. or set a enw flag
 *
 *
 * 	*/



/* ============================================================================================ */
// 	 LED Frequency  Menu Functions
/* ============================================================================================ */


void setLEDON(void){
timer32_0_counter = 0; // reset counter
//uint32_t delay;
		//on
		while(timer32_0_counter < (uint32_t)((float)currentDutyCycle*(float)currentPeriod))
		{
		LPC_GPIO0 -> DATA = 0x000;
		}
		//off
		while(timer32_0_counter >= (uint32_t)((float)currentDutyCycle*(float)currentPeriod) && timer32_0_counter < currentPeriod )
		{
			LPC_GPIO0 -> DATA |= 0xfff;
		}
}

void setLEDOFF(void){
	LPC_GPIO0 -> DATA |= LED_B_P0_9;
}



/* ============================================================================================ */
// 	 LED Duty Cycle  Menu Functions
/* ============================================================================================ */


/* ============================================================================================ */
// 	 ADC Control  Menu Functions
/* ============================================================================================ */




/* ============================================================================================ */
// 	 ADC Reporting Frequency  Menu Functions
/* ============================================================================================ */













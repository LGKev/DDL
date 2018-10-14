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

#include "uart.h"

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






//global
uint8_t uartCharReceived = 0;
uint32_t delay = 0;
uint8_t currentStateFlag = 0;


int main (void) {
	  /* Basic chip initialization is taken care of in SystemInit() called
	   * from the startup code. SystemInit() and chip settings are defined
	   * in the CMSIS system_<part family>.c file.
	   */


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

  /* NVIC is installed inside UARTInit file. */
  UARTInit(UART_BAUD);

	  UARTCount = 13;
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

	if(uartCharReceived == '3'){
		currentStateFlag = 4;
		//go to the duty cycle menu
	}
	else if(uartCharReceived =='4'){
		//go to the led frequency menu
		currentStateFlag = 5;
	}
	else{
		currentStateFlag = 1; //spin
	}
} //end of state 1

if(currentStateFlag == 4){

	if(uartCharReceived == '5'){
		currentStateFlag = 1;
		//go to the duty cycle menu
	}
	else {
		currentStateFlag = 4; //do nothing just spin
	}
} //end of state 4

if(currentStateFlag == 5){

	if(uartCharReceived == '6'){
		currentStateFlag = 1; //go back up
		//go to the duty cycle menu
	}
	else {
		currentStateFlag = 5; //do nothing just spin
	}
} //end of state 1

if(currentStateFlag == 2){

	if(uartCharReceived == '3'){
		currentStateFlag = 3; //go to the adc report freq state
		//go to the duty cycle menu
	}
	else if(uartCharReceived == '4') {
		currentStateFlag = 0; //go back to the main menu
	}
	else{
		currentStateFlag = 2; //just spin
	}
} //end of state 2


if(currentStateFlag == 3){

	if(uartCharReceived == '5'){
		currentStateFlag = 2; //go up a menu
		//go to adc control menu
	}
	else{
		currentStateFlag = 3; //just spin
	}
} //end of state 2







	  /* ============================================================================================ */
  }
}

void idleState(uint8_t value){
	switch (value):
				case 1:

					break;
				case 2:
					break;
	default:
		break;
}


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

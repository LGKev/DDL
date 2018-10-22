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


volatile char asciiDigits[10]; // for decimal to ascii numbers for printing
volatile  uint8_t digitArray[10]; //array holding up to 4 digit numbers, numbers will be stored in reverse. to read correctly we must read backwards.
//global
/* Fucntions tthat touch these globals:
 * 		-setLEDON
 * */
float currentDutyCycle = 0.5; //[percentage]
uint32_t currentPeriod = 100; // [miliseconds]
uint32_t currentADCDelay = 2000000;
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
uint8_t displayMenu = 1;


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

	ADCInit( ADC_CLK );


  /* NVIC is installed inside UARTInit file. */
  UARTInit(UART_BAUD);
 // UARTSend("AT", 3); //TODO fix this, something with line endings.
  //UARTSend((uint8_t)"AT+Set53", 9);

	//  UARTCount = 13;
  while (1)
  {				/* Loop forever */

	  ADCRead( 0 );
	  while ( !ADCIntDone );
	  ADCIntDone = 0;
	  uint32_t adcValue = ADCValue[0];
	  float voltage_V = (float)(((float)adcValue / 1023)*(3.3))*1000.0;
	  uint32_t voltage_mV = (uint32_t)voltage_V;






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
	if(displayMenu == 1){
		  UARTSend("1. Control LED \n", 17 );
		  UARTSend("2. Control ADC \n", 17 );
		displayMenu = 0;
	}
	  if(uartCharReceived == '1'){
		  //turn on led >> State: LED Control
		  //set a flag to let us know what state we are in.i
		  currentStateFlag = 1;
	  	  displayMenu = 1;
	  }
	  else if(uartCharReceived == '2'){
		  //turn off led >> State: ADC Control
		  currentStateFlag = 2;
	  	  displayMenu = 1;
	  }
	  else{
		  //print out menu again
		  currentStateFlag = 0;

	  }
} // end of state 0

if(currentStateFlag == 1){

	if(displayMenu == 1){
			  UARTSend("1. Blink On \n", 14 );
			  UARTSend("2. Blink Off \n", 15 );
			  UARTSend("3. Set Duty Cycle \n", 20 );
			  UARTSend("4. Set Frequency \n", 19 );
			  UARTSend("5. Go Back \n", 13 );
			displayMenu = 0;
		}
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
	  	  displayMenu = 1;
		currentStateFlag = 4;
	}
	else if(uartCharReceived == '4'){
		currentStateFlag = 5;
	  	  displayMenu = 1;
	}
	else if(uartCharReceived == '5'){
		currentStateFlag = 0;
	  	  displayMenu = 1;
	}
	/* invalid input just stay in current state */
	else{
		setLEDON();
		currentStateFlag = 1; //spin


	}

} //end of state 1

if(currentStateFlag == 4){

	if(displayMenu == 1){
			  UARTSend("1. 10% \n", 9 );
			  UARTSend("2. 25% \n", 9 );
			  UARTSend("3. 50% \n", 9 );
			  UARTSend("4. 75% \n", 9 );
			  UARTSend("5. 90% \n", 9 );
			  UARTSend("6. Go Back \n", 13 );
			displayMenu = 0;
	}
	if(uartCharReceived == '6'){
		currentStateFlag = 1;
		displayMenu = 1;
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
		//setLEDON();
		currentStateFlag = 4; //do nothing just spin


	}

	}
 //end of state 4

if(currentStateFlag == 5){


	if(displayMenu == 1){
				  UARTSend("1. Slow \n", 10 );
				  UARTSend("2. Medium \n", 11 );
				  UARTSend("3. Fast \n", 10 );
				  UARTSend("4. Very Fast \n", 15 );
				  UARTSend("5. Go Back \n", 13 );
				displayMenu = 0;
			}
	if(uartCharReceived == '5'){
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


} //end of state 5

if(currentStateFlag == 2){


uint32_t i=0;
uint8_t test = 53; //ascii 5
if(displayMenu == 1){
			  UARTSend("1. ADC Reporting On \n", 22 );
			  UARTSend("2. ADC Reporting Off \n", 23 );
			  UARTSend("3. Set ADC Frequency \n", 23 );
			  UARTSend("4. Go Back \n", 13 );
			displayMenu = 0;
		}
	if(uartCharReceived == '1'){
	// adc report on
		numberToAscii(voltage_mV);
		UARTSend((uint8_t *) asciiDigits, 10);
		UARTBuffer[0]='\n';
		/* when we just sent '\0' with uartsend, we dont' get a new line.
		 * but with putting into the buffer and then using it, we got a new line
		 * is it the casting of the pointer? */
		UARTSend((uint8_t *)UARTBuffer, 2);
		for(i=0; i<currentADCDelay; i++);
		for(i=0; i<10; i++){
			asciiDigits[i] = '\0';
		}
	}
	else if(uartCharReceived == '2') {
	// adc report off
	}
	else if(uartCharReceived == '3') {
		currentStateFlag =3;
		displayMenu = 1;
		//set report freq
	}else if(uartCharReceived == '4') {
		currentStateFlag = 0; //go back to the main menu
		displayMenu = 1;
	}
	else{
		currentStateFlag = 2; //just spin

	}

} //end of state 2


if(currentStateFlag == 3){

	if(displayMenu == 1){
				  UARTSend("1. Slow \n", 10 );
				  UARTSend("2. Medium \n", 11 );
				  UARTSend("3. Fast \n", 10 );
				  UARTSend("4. Very Fast \n", 15 );
				  UARTSend("5. Go Back \n", 13 );
				displayMenu = 0;
			}
	if(uartCharReceived == '5'){
			currentStateFlag = 2; //go back up
			displayMenu = 1;
			//go to the duty cycle menu
		}
		else if(uartCharReceived == '1')
		{
			//slow freq
			currentADCDelay = 3000000;
		}
		else if(uartCharReceived == '2')
		{
			//medium freq
			currentADCDelay = 2000000;
		}
		else if(uartCharReceived == '3')
		{
			//fast freq
			currentADCDelay = 1000000;
		}
		else if(uartCharReceived == '4')
		{
			//verry fast
			currentADCDelay = 500000;
		}
		else {
			currentStateFlag = 3; //do nothing just spin


		}

} //end of state 3







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


void numberToAscii(uint16_t number){
	int8_t incr = 0;
	uint8_t incr2 = 0;
	//we could also fill the array backwards.


	//breaks the number number given into its digits, into an Array
	// the array will be backwards representation of the actual number_number
	while(number > 0)
	{
		digitArray[incr] = number % 10;
		number = number/10;
		incr++;
	}
	incr--;


	while(incr != -1)// at this point we start with incr at end of the current number
		{
		switch(digitArray[incr])
		{
			case 0:
				// _ _ _ _ _
				asciiDigits[incr2] = '0';
				break;

			case 1:
				// *_ _ _ _
				asciiDigits[incr2] = '1';
				break;

			case 2:
				// ** _ _ _
				asciiDigits[incr2] = '2';

				break;

			case 3:
				//*** _ _
				asciiDigits[incr2] = '3';
				break;

			case 4:
				//**** _
				asciiDigits[incr2] = '4';
				break;

			case 5:
				//* * * * *
				asciiDigits[incr2] = '5';
				break;

			case 6:
				// _ * * * *
				asciiDigits[incr2] = '6';
				break;

			case 7:
				//_  _  * * *
				asciiDigits[incr2] = '7';
				break;

			case 8:
				// _ _  _ * *
				asciiDigits[incr2] = '8';
				break;

			case 9:
				// _ _ _  _ *
				asciiDigits[incr2] = '9';
				break;

			default:
				return;
		}
		incr--;
		incr2++;
		}
	asciiDigits[incr2++] = 'm';
	asciiDigits[incr2++] = 'V';
	}
//#define mine
#ifdef mine
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

extern volatile uint32_t UARTCount;
extern volatile uint8_t UARTBuffer[BUFSIZE];
uint8_t currentState = 0;

int main (void) {
	  /* Basic chip initialization is taken care of in SystemInit() called
	   * from the startup code. SystemInit() and chip settings are defined
	   * in the CMSIS system_<part family>.c file.
	   */

  /* NVIC is installed inside UARTInit file. */
  UARTInit(UART_BAUD);

#if MODEM_TEST
  ModemInit();
#endif
//#define part1
#ifdef part1
  UARTBuffer[0] = 'H';
  UARTBuffer[1] = 'e';
  UARTBuffer[2] = 'l';
  UARTBuffer[3] = 'l';
  UARTBuffer[4] = 'o';
  UARTBuffer[5] = ' ';
  UARTBuffer[6] = 'W';
  UARTBuffer[7] = 'o';
  UARTBuffer[8] = 'r';
  UARTBuffer[9] = 'l';
  UARTBuffer[10] = 'd';
  UARTBuffer[11] = '\n';
  UARTBuffer[12] = '\0';


  while (1)
  {				/* Loop forever */

	if ( UARTCount != 0 )
	{
	  LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
	  UARTSend( (uint8_t *)UARTBuffer, UARTCount );
	  UARTCount = 13;
	  LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */
	  uint32_t delay;
	  for(delay = 0; delay < 2000000; delay++);
	}




  }
#endif
}
#endif

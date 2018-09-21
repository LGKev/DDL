/*****************************************************************************
 *    Main
 *    Author: Ali 
 *    Author: Kevin Kuwata
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.12.07  ver 1.00    Preliminary version, first Release
 *
 ******************************************************************************/
#include "driver_config.h"
#include "target_config.h"

#include "timer32.h"
#include "gpio.h"

#define DASH_DOT_DELAY					480000
#define HALF_VCC_ADC_512				512

/******************************************************************************
 **   Main Function  main()
 ******************************************************************************/

uint16_t getFib(uint8_t n);

/*
 *  input a fib number, this will parse number into an array (reversed order) 
 *  then will show the digit in morse code with blue and red led.
 * */
void morse(uint16_t fib);

/* display a long dash for a certain period
 * Blue LED for DASHES
 * */
void dash(uint8_t numberOfDashes);

/* display a dot n number of times
 * RED LED for DOTS
 * */
void dot(uint8_t numberOfDots);


int main (void)
{

	uint32_t elapsedTimeTicks = 0;
	uint32_t elapsedTimeMiliSeconds = 0;


	init_timer32(0, TIME_INTERVAL); //60Mhz gives 10ms
	enable_timer32(0); //will use later to calculate the frequency. 
	GPIOInit();
	GPIOSetDir(LED_PORT_B, LED_BIT_B, 1);
	GPIOSetValue(LED_PORT_B, LED_BIT_B, LED_OFF);

	GPIOSetDir(LED_PORT_R, LED_BIT_R, 1);
	GPIOSetValue(LED_PORT_R, LED_BIT_R, LED_OFF);


	uint16_t fibArray[20];
	uint8_t nth_fib;
	uint16_t fibNum;

	//fill up an array of pre-calculated fib numbers
	//0th number is 1 and 3rd fib is 3.
	for ( nth_fib= 0; nth_fib < 20; nth_fib++)
	{
		fibArray[nth_fib] = getFib(nth_fib+1);
		fibNum = fibArray[nth_fib];
		//	morse(fibNum);
	}


	morse(10);


	while(1)
	{

		//	dash(3);
		dot(1);
		//#define demo1
#ifdef demo1
		if( adcValue >= HALF_VCC_ADC_512) {
			GPIOSetValue(LED_PORT_B, LED_BIT_B, LED_ON);
		}
		GPIOSetValue(LED_PORT_B, LED_BIT_B, LED_OFF);
#endif


		//#define blink2seconds
#ifdef blink2seconds
		if(timer32_0_counter > 200){
			GPIOSetValue(LED_PORT_B, LED_BIT_B, LED_ON);	

		}
		if(timer32_0_counter > 400){
			GPIOSetValue(LED_PORT_B, LED_BIT_B, LED_OFF);	
			timer32_0_counter=0;
		}
#endif

	}
} //end of main

/* ============================================================================================================  */
/* ============================================================================================================  */
/* ============================================================================================================  */

uint16_t getFib(uint8_t n)
{
	uint16_t arr[20];
	arr[0] = 1;
	arr[1] = 1;
	uint8_t i = 0;
	for(i = 2; i<=n;i++)
	{
		arr[i] = arr[i-1] + arr[i-2];
	}
	n = arr[n-1];
	return n;
}



void morse(uint16_t fib)
{
	uint8_t incr = 0;
	uint8_t digitArray[4]; //array holding up to 4 digit numbers, numbers will be stored in reverse. to read correctly we must read backwards.
	//we could also fill the array backwards. 

	//breaks the fib number given into its digits, into an Array
	// the array will be backwards representation of the actual fib_number
	while(fib > 0)
	{
		digitArray[incr] = fib % 10;
		fib = fib/10;
		incr++;
	}
	while(incr != 0)// at this point we start with incr=4
	{
		switch(digitArray[incr -1])
		{
			case 0:
				// *_ _ _ _
				dot(1);
				dash(4);		
				break;

			case 1:
				// ** _ _ _
				dot(2);
				dash(3);
				break;

			case 2:
				// *** _ _
				dot(2);
				dash(3);

				break;

			case 3:
				//**** _
				dot(2);
				dash(3);
				break;

			case 4:
				//*****
				dot(2);
				dash(3);


				break;

			case 5:
				//_ * * * * *
				dot(2);
				dash(3);

				break;

			case 6:
				// _ _ * * * 
				dot(2);
				dash(3);

				break;

			case 7:
				//_ _ _ * *
				dot(2);
				dash(3);

				break;

			case 8:
				// _ _ _ _ *
				dot(2);
				dash(3);

				break;

			case 9:
				// _ _ _ _ _  
				dot(2);
				dash(3);

				break;

			default:
				return;
		}
		incr--;
	}
}


void dash(uint8_t numberOfDashes){
	uint8_t count = 0;
	uint32_t delay = 0;
	for(count = 1; count<= numberOfDashes; count++){
		GPIOSetValue(LED_PORT_B, LED_BIT_B, LED_ON);
		for(delay=0; delay<=DASH_DOT_DELAY*2; delay++); //*2 so that a dash is truely 2 times as long as a dot
		GPIOSetValue(LED_PORT_B, LED_BIT_B, LED_OFF);
		for(delay=0; delay<=DASH_DOT_DELAY; delay++);	
	}
}

void dot(uint8_t numberOfDots){
	uint8_t count = 0;
	uint32_t delay = 0;
	for(count = 1; count<= numberOfDots; count++){
		GPIOSetValue(LED_PORT_R, LED_BIT_R, LED_ON);
		for(delay=0; delay<=DASH_DOT_DELAY; delay++);
		GPIOSetValue(LED_PORT_R, LED_BIT_R, LED_OFF);
		for(delay=0; delay<=DASH_DOT_DELAY; delay++);
	}
}

/******************************************************************************
 **                            End Of File
 ******************************************************************************/

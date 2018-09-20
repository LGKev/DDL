/*****************************************************************************
 *   adctest.c:  main C entry file for NXP LPC11xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.12.07  ver 1.00    Preliminary version, first Release
 *
 ******************************************************************************/
/*****************************************************************************
 *   adctest.c:  main C entry file for NXP LPC11xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.12.07  ver 1.00    Preliminary version, first Release
 *
 ******************************************************************************/
#include "driver_config.h"
#include "target_config.h"

#include "adc.h"
#include "debug_printf.h"
#include "timer32.h"
#include "gpio.h"


#define TOP_VCC_ADC_1023				1023
#define HALF_VCC_ADC_512				0
#define ADC_TOLERANCE					10 // SO 512-10 = 502 IS THE LOW AND 522 IS THE HIGH

/******************************************************************************
 **   Main Function  main()
 ******************************************************************************/
int main (void)
{

	uint8_t hit =  0;// hit rate, essentially zero crossing
	uint32_t elapsedTimeTicks = 0;
	uint32_t elapsedTimeMiliSeconds = 0;
	float frequency = 0.0;


	init_timer32(0, TIME_INTERVAL); //60Mhz gives 10ms
	enable_timer32(0); //will use later to calculate the frequency. 
	GPIOInit();
	GPIOSetDir(LED_PORT_B, LED_BIT_B, 1);
	GPIOSetValue(LED_PORT_B, LED_BIT_B, LED_OFF);



	/* Basic chip initialization is taken care of in SystemInit() called
	 * from the startup code. SystemInit() and chip settings are defined
	 * in the CMSIS system_<part family>.c file.
	 */

	/* Initialize ADC  */
	ADCInit( ADC_CLK );

	/* LED Initialization code here */


	while(1)
	{
		/* Read one sample from the ADC port 'AD0' */
		ADCRead( 0 );
		while ( !ADCIntDone );
		ADCIntDone = 0;
		/* LED lighting and analog signal frequency calculation and printing code here */

		uint32_t adcValue = ADCValue[0];
		
#ifdef demo1
		if( adcValue >= HALF_VCC_ADC_512) {
			GPIOSetValue(LED_PORT_B, LED_BIT_B, LED_ON);
		}
		GPIOSetValue(LED_PORT_B, LED_BIT_B, LED_OFF);
#endif

#define betterAlgo2
#ifdef betterAlgo2
		uint8_t allow_inc = 0;

// at the bottom
		if((ADCValue[0] <= (HALF_VCC_ADC_512 + ADC_TOLERANCE) )&& (ADCValue[0] >= (HALF_VCC_ADC_512 - ADC_TOLERANCE)) )
		{


			if(hit == 2)
			{
				elapsedTimeTicks =  elapsedTimeTicks *2;
				//timer32_0_counter = 0; //reset timer
				hit = 0;
				elapsedTimeMiliSeconds = elapsedTimeTicks * 10* 2; // mS
				frequency = (float) ( (1.0)/ (float)(elapsedTimeMiliSeconds*1000));
				frequency += 0;
			}
		} // end of adc zero crossing
//top

	if((ADCValue[0] <= (TOP_VCC_ADC_1023 + ADC_TOLERANCE) )&& (ADCValue[0] >= (TOP_VCC_ADC_1023)- ADC_TOLERANCE)) )
		{

			if(hit == 2)
			{
				elapsedTimeTicks =  elapsedTimeTicks *2;
				//timer32_0_counter = 0; //reset timer
				hit = 0;
				elapsedTimeMiliSeconds = elapsedTimeTicks * 10* 2; // mS
				frequency = (float) ( (1.0)/ (float)(elapsedTimeMiliSeconds*1000));
				frequency += 0;
			}
		} // end of adc zero crossing


#endif



			hit++;
///#define betterAlgo
#ifdef betterAlgo
		uint8_t allow_inc = 0;


		if((ADCValue[0] <= (HALF_VCC_ADC_512 + ADC_TOLERANCE) )&& (ADCValue[0] >= (HALF_VCC_ADC_512 - ADC_TOLERANCE)) )
		{

			if(hit == 0){
				///time1 = timer32_0_counter;
				timer32_0_counter = 0;
			}

			if(hit == 1){
				elapsedTimeTicks = timer32_0_counter;
				//timer32_0_counter = 0 ;
			}
			hit++;

			if(hit == 2)
			{
				elapsedTimeTicks =  elapsedTimeTicks *2;
				//timer32_0_counter = 0; //reset timer
				hit = 0;
				elapsedTimeMiliSeconds = elapsedTimeTicks * 10* 2; // mS
				frequency = (float) ( (1.0)/ (float)(elapsedTimeMiliSeconds*1000));
				frequency += 0;
			}




		} // end of adc zero crossing
#endif


/#define betterAlgo
#ifdef betterAlgo
		uint8_t allow_inc = 0;

		
		if((ADCValue[0] <= (HALF_VCC_ADC_512 + ADC_TOLERANCE) )&& (ADCValue[0] >= (HALF_VCC_ADC_512 - ADC_TOLERANCE)) )
		{

			if(hit == 0){
				///time1 = timer32_0_counter;
				timer32_0_counter = 0;
			}

			if(hit == 1){
				elapsedTimeTicks = timer32_0_counter;
				//timer32_0_counter = 0 ;
			}
			hit++;
			
			if(hit == 2)
			{
				elapsedTimeTicks =  elapsedTimeTicks *2;
				//timer32_0_counter = 0; //reset timer
				hit = 0;
				elapsedTimeMiliSeconds = elapsedTimeTicks * 10* 2; // mS
				frequency = (float) ( (1.0)/ (float)(elapsedTimeMiliSeconds*1000));
				frequency += 0;
			}
	
	

	
		} // end of adc zero crossing
#endif



			hit++;



//#define kevin
#ifdef kevin


		uint8_t allow_inc = 0;
		if((ADCValue[0] <= (HALF_VCC_ADC_512 + ADC_TOLERANCE) )&& (ADCValue[0] >= (HALF_VCC_ADC_512 - ADC_TOLERANCE)) ){
//	if(ADCValue[0] == HALF_VCC_ADC_512){
		//we had a zero crossing event
		//if it was the first zero crossing, reset the timer
		if(hit == 0){ 
			timer32_0_counter = 0;
			allow_inc = 1;
		}

		else if(hit == 2){
			elapsedTimeTicks = timer32_0_counter;
			elapsedTimeMiliSeconds =  (elapsedTimeTicks * 10 ); // to get into miliseconds, each tick is 10ms
			frequency = (float) (1/((float)elapsedTimeMiliSeconds)*1000.0);
			hit = 0; //reset hit
			allow_inc = 0;
		}

		if(allow_inc == 1)
			hit++;
		}

	} // end of adc zero crossing
#endif

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
}

/******************************************************************************
 **                            End Of File
 ******************************************************************************/

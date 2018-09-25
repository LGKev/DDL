/*
===============================================================================
 Name        : lab_3.c
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

// TODO: insert other include files here
#include "driver_config.h"
#include "target_config.h"
#include "gpio.h"
#include "timer32.h"
// TODO: insert other definitions and declarations here
uint16_t GetFib(uint8_t n);
void morse(uint16_t fib);

void Long(uint8_t reps);
void Short(uint8_t reps);

int main(void) {

    // TODO: insert code here
	 /* LED Initialization code here */
	  init_timer32(0, TIME_INTERVAL);
	  enable_timer32(0);
	  while(timer32_0_counter == 0) enable_timer32(0);
	  /* Initialize GPIO (sets up clock) */
	  GPIOInit();
	  /* Set LED port pin to output */
	  GPIOSetDir(LED_PORT_B, LED_BIT_B, 1 );
	  GPIOSetValue(LED_PORT_B,LED_BIT_B,LED_OFF);
	  /* Initialize ADC  */
	   ADCInit( ADC_CLK );

	uint16_t arr[20];
	    uint8_t i;
	    uint16_t fibnum;
	    for ( i = 0; i < 20; i++)
	        {
	            arr[i] = GetFib(i+1);
	            fibnum = arr[i];
	            morse(fibnum);
	            //printf("%d \n",arr[i]);
	        }

    // Force the counter to be placed into memory
    //volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    /*while(1) {
        i++ ;
    }*/
    return 0 ;
}


uint16_t GetFib(uint16_t n)
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
    uint8_t arr[4];
    while(fib > 0)
    {
        arr[incr] = fib % 10;
        fib = fib/10;
        incr++;
    }
    while(incr != 0)
    {
        switch(arr[incr])
        {
            case 0:
            //do time shit here
            	Long(5);
            break;

            case 1:
            //do time shit here
            	Short(1);
            	Long(4);
            break;

            case 2:
            //do time shit here
            	Short(2);
            	Long(3);
            break;

            case 3:
            //do time shit here
            	Short(3);
            	Long(2);
            break;
            case 4:
            //do time shit here
            	Short(4);
            	Long(1);
            break;

            case 5:
            //do time shit here
            	Short(5);
            break;

            case 6:
            //do time shit here
            	Long(1);
            	Short(4);
            break;

            case 7:
            //do time shit here
            	Long(2);
            	Short(3);
            break;

            case 8:
            //do time shit here
            	Long(3);
            	Short(2);
            break;

            case 9:
            //do time shit here
            	Long(4);
            	Short(1);
            break;

            default:
                return;
        }
        incr--;
    }
}


void Long(uint8_t reps)
{
	while(reps > 0)
	{
	timer32_0_counter = 0;
	while(timer32_0_counter <100)
		{
			GPIOSetValue(LED_PORT_B,LED_BIT_B,LED_ON);
		}
		while(timer32_0_counter>=100 && timer32_0_counter <200)
		{
			GPIOSetValue(LED_PORT_B,LED_BIT_B,LED_OFF);
		}
		reps--;
	}
}
void Short(uint8_t reps)
{
	while(reps > 0)
		{
		timer32_0_counter = 0;
		while(timer32_0_counter <50)
			{
				GPIOSetValue(LED_PORT_B,LED_BIT_B,LED_ON);
			}
			while(timer32_0_counter>=50 && timer32_0_counter <100)
			{
				GPIOSetValue(LED_PORT_B,LED_BIT_B,LED_OFF);
			}
			reps--;
		}
}


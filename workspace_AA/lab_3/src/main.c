/*
===============================================================================
 Name        : lab_3.c
 Author      : Ali Al Naji & Kevin Kuwata
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
extern int GetFib(int n);
//uint16_t GetFib(uint8_t n);
/*
 *  input a fib number, this will parse number into an array (reversed order)
 *  then will show the digit in morse code with long and short flashes.
 * */
void morse(uint16_t fib);

void Long(uint8_t reps);//enter how many repetitions of long and long flashes
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

	  	uint32_t arr[20];
	    //uint8_t i;
	    int fibnum;
	    //fill up an array of pre-calculated fib numbers
	    	//0th number is 1 and 3rd fib is 3.
	    // the variable i in the for loop was messing up the registers in the
	    //GetFib function so we just decided to spell out all the cases
	    arr[0] = GetFib(1);
	    fibnum = arr[0];
	    fibnum += 0;
	    morse(arr[0]);
	    arr[1] = GetFib(2);
	    morse(arr[1]);
	    arr[2] = GetFib(3);
	    morse(arr[2]);
	    arr[3] = GetFib(4);
	    morse(arr[3]);
	    arr[4] = GetFib(5);
	    morse(arr[4]);
	    arr[5] = GetFib(6);
	    morse(arr[5]);
	    arr[6] = GetFib(7);
	    morse(arr[6]);
	    arr[7] = GetFib(8);
	    morse(arr[7]);
	    arr[8] = GetFib(9);
	    morse(arr[8]);
	    arr[9] = GetFib(10);
	    morse(arr[9]);
	    arr[10] = GetFib(11);
	    morse(arr[10]);
	    arr[11] = GetFib(12);
	    morse(arr[11]);
	    arr[12] = GetFib(13);
	    morse(arr[12]);
	    arr[13] = GetFib(14);
	    morse(arr[13]);
	    arr[14] = GetFib(15);
	    morse(arr[14]);
	    arr[15] = GetFib(16);
	    morse(arr[15]);
	    arr[16] = GetFib(17);
	    morse(arr[16]);
	    arr[17] = GetFib(18);
	    morse(arr[17]);
	    arr[18] = GetFib(19);
	    morse(arr[18]);
	    arr[19] = GetFib(20);
	    morse(arr[19]);


	    /*
	    for ( i = 0; i < 20; i++)
	        {
	            int j = i+1;
	    		//arr[i] = GetFib(j);
	            fibnum = arr[i];
	            fibnum += 0;
	            morse(fibnum);
	            //printf("%d \n",arr[i]);
	        }
	     */

    return 0 ;
}

//#define cFib
#ifdef cFib
uint16_t GetFib(uint8_t n)
{
  uint16_t arr[20];
  arr[0] = 1;
  arr[1] = 1;
  uint8_t i;
  for(i = 2; i<=n;i++)
  {
    arr[i] = arr[i-1] + arr[i-2];
  }
  uint16_t N = arr[n-1];
  return N;
}
#endif

void morse(uint16_t fib)
{
    uint8_t incr = 0;
    uint8_t arr[4];
    //array holding up to 4 digit numbers, numbers will be stored in reverse. to read correctly we must read backwards.
    	//we could also fill the array backwards.

    	//breaks the fib number given into its digits, into an Array
    	// the array will be backwards representation of the actual fib_number
    while(fib > 0)
    {
        arr[incr] = fib % 10;
        fib = fib/10;
        incr++;
    }
    //incr--;
    while(incr != 0)// at this point we start with incr at end of the current number
    {
        switch(arr[incr-1])
        {
            case 0:
            	Long(5);
            break;

            case 1:
            	Short(1);
            	Long(4);
            break;

            case 2:
            	Short(2);
            	Long(3);
            break;

            case 3:
            	Short(3);
            	Long(2);
            break;
            case 4:
            	Short(4);
            	Long(1);
            break;

            case 5:
            	Short(5);
            break;

            case 6:
            	Long(1);
            	Short(4);
            break;

            case 7:
            	Long(2);
            	Short(3);
            break;

            case 8:
            	Long(3);
            	Short(2);
            break;

            case 9:
            	Long(4);
            	Short(1);
            break;

            default:
                return;
        }

        if(incr == 0)
        {
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
void Short(uint8_t reps)
{
	while(reps > 0)
		{
		timer32_0_counter = 0;
		while(timer32_0_counter < 10)
			{
				GPIOSetValue(LED_PORT_B,LED_BIT_B,LED_ON);
			}
			while(timer32_0_counter>=10 && timer32_0_counter <20)
			{
				GPIOSetValue(LED_PORT_B,LED_BIT_B,LED_OFF);
			}
			reps--;
		}
}


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

/****************************************************************************
 *   $Id:: i2c_main.c 4785 2010-09-03 22:39:27Z nxp21346                    $
 *   Project: NXP LPC11xx I2C example
 *
 *   Description:
 *     This file contains I2C test modules, main entry, to test I2C APIs.
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

#include "type.h"
#include "i2c.h"
#include "mpu6050.h"

/* Data Buffer */
int16_t accBuffer[3];

/*******************************************************************************
**  Main Function  main()
*******************************************************************************/
int main (void)
{
	  /* Basic chip initialization is taken care of in SystemInit() called
	   * from the startup code. SystemInit() and chip settings are defined
	   * in the CMSIS system_<part family>.c file.
	   */

  uint32_t i;

  if ( I2CInit( (uint32_t)I2CMASTER ) == FALSE )	/* initialize I2c */
  {
	while ( 1 );				/* Fatal error */
  }

  /* power up MPU6050 and use X axis Gyro reference clock*/
  // TO-DO

  /* configure acc measurement range */
  // TO-DO

  /* Be careful with below fixed delay. From device to device, or
  even same device with different write length, or various I2C clock, 
  below delay length may need to be changed accordingly. Having 
  a break point before Write/Read start will be helpful to isolate 
  the problem. */
  for ( i = 0; i < 0x200000; i++ );	/* Delay after write */

  /* Read and Print WHO_AM_I register */
  // TO-DO


  /* Continuously reading acc data*/
  while (1) {
	  /* Read acceleration 3 axis data*/
	  mpu6050Read(ACC_REG, ACC_BYTES, accBuffer);

	  printf("%d, %d, %d \n",accBuffer[0], accBuffer[1], accBuffer[2]);
  }

  return 0;
}

/******************************************************************************
**                            End Of File
******************************************************************************/

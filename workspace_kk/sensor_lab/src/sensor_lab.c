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
#include "LPC11xx.h"
#include <cr_section_macros.h>


/* Data Buffer */
int16_t accBuffer[3];

#include "type.h"
#include "i2c.h"

extern volatile uint32_t I2CCount;
extern volatile uint8_t I2CMasterBuffer[BUFSIZE];
extern volatile uint8_t I2CSlaveBuffer[BUFSIZE];
extern volatile uint32_t I2CMasterState;
extern volatile uint32_t I2CReadLength, I2CWriteLength;

/*******************************************************************************
**   Main Function  main()
*******************************************************************************/
int main (void)
{
	/* configure led gpio */
	LPC_SYSCON -> SYSAHBCLKCTRL |= (1<<6) | (1<<16); //bit is the gpio enable

	//iocon_pio0.7 led
	//10-0: 0 0011 0  00 000 -> hex: 003000
	LPC_IOCON -> PIO0_7 = 0xd0; //0xd0 default will work. but never too sure
	LPC_GPIO0 -> DIR |= 0xFFF; //output red led btw make them all outputs!
	// the led's configured such that a GPIO:0 is on, and GPIO:1 is off.
	LPC_GPIO0 -> DATA |= 0xfff; //turn  all off
        // NO need for interrupt stuff
/* ======================================= */

	  /* Basic chip initialization is taken care of in SystemInit() called
	   * from the startup code. SystemInit() and chip settings are defined
	   * in the CMSIS system_<part family>.c file.
	   */

  uint32_t i;

  if ( I2CInit( (uint32_t)I2CMASTER ) == FALSE )	/* initialize I2c */
  {
	while ( 1 );				/* Fatal error */
  }

  /* In order to start the I2CEngine, the all the parameters
  must be set in advance, including I2CWriteLength, I2CReadLength,
  I2CCmd, and the I2cMasterBuffer which contains the stream
  command/data to the I2c slave device.
  (1) If it's a I2C write only, the number of bytes to be written is
  I2CWriteLength, I2CReadLength is zero, the content will be filled
  in the I2CMasterBuffer.
  (2) If it's a I2C read only, the number of bytes to be read is
  I2CReadLength, I2CWriteLength is 0, the read value will be filled
  in the I2CMasterBuffer.
  (3) If it's a I2C Write/Read with repeated start, specify the
  I2CWriteLength, fill the content of bytes to be written in
  I2CMasterBuffer, specify the I2CReadLength, after the repeated
  start and the device address with RD bit set, the content of the
  reading will be filled in I2CMasterBuffer index at
  I2CMasterBuffer[I2CWriteLength+2].

  e.g. Start, DevAddr(W), WRByte1...WRByteN, Repeated-Start, DevAddr(R),
  RDByte1...RDByteN Stop. The content of the reading will be filled
  after (I2CWriteLength + two devaddr) bytes. */

  /* Write SLA(W), address and one data byte */

  /* i2c write to register: acc config */
  I2CWriteLength = 3; //is equal to , # of bytes,: counting: slave addr, register addres, data
  I2CReadLength = 0;
  I2CMasterBuffer[0] = MPU6050_ADDR;
  I2CMasterBuffer[1] = ACC_CONFIG;		/* address */
  I2CMasterBuffer[2] = ACC_2G;		/* all  */
  I2CEngine();
//sleep mode
  I2CWriteLength = 3;
  I2CReadLength = 0;
  I2CMasterBuffer[0] = MPU6050_ADDR;
  I2CMasterBuffer[1] = 0x6B;		/* address */
  I2CMasterBuffer[2] = 0x00;		/* all  */
  I2CEngine();





  uint32_t delay = 0;

  while(1){
#ifdef correctWrite
  I2CWriteLength = 3;
  I2CReadLength = 0;
  I2CMasterBuffer[0] = MPU6050_ADDR;
  I2CMasterBuffer[1] = ACC_CONFIG;	//power config	/* address */
  I2CMasterBuffer[2] =ACC_4G ;		/* all  */
  I2CEngine();
#endif
#define correctRead
#ifdef correctRead
	  /* read 2 byte */
  I2CWriteLength = 2; //maybe 4
  I2CReadLength = 4; //2 to get 2 consecutigve data bytes
  I2CMasterBuffer[0] = MPU6050_ADDR;
  I2CMasterBuffer[1] = ACC_X_HI; // gyro x axis
//  I2CMasterBuffer[1] = 0x43; // gyro x axis
 // //I2CMasterBuffer[1] = 0x75;
 //I2CMasterBuffer[1] = ACC_CONFIG;
//  I2CMasterBuffer[1] = ACC_X_LOW;
  I2CMasterBuffer[2] = MPU6050_ADDR|0b1; //repeated start
  I2CEngine();
#endif
  for(delay=0; delay<20000; delay++);

  //y axis
  if(I2CSlaveBuffer[2] <= 50 && I2CSlaveBuffer[3] >150){
	  //turn on led backward:
	  LPC_GPIO0 ->DATA &= ~(1<<7 | 1<<8);
  }
  else if(I2CSlaveBuffer[2] > 74 && I2CSlaveBuffer[2] < 230){
//turn on led forwrd: red
	  LPC_GPIO0 ->DATA &= ~(1<<7);
  }
  else if(I2CSlaveBuffer[0] <= 60  ){
	  //turn on led LEFT: BLUE
	  LPC_GPIO0 ->DATA &= ~(1<<9);
  }
  else if(I2CSlaveBuffer[0] > 60 && I2CSlaveBuffer[0] < 225){
//turn on led RIGHT: GREEN
	  LPC_GPIO0 ->DATA &= ~(1<<8);
  }
  else
  {
	  //turn off led
	  LPC_GPIO0 ->DATA |= 0xffff;
  }


//#define bonus
#ifdef bonus
  /* z up down bonus*/
  if(I2CSlaveBuffer[0] >= 70){
	  //turn on led
	  LPC_GPIO0 ->DATA = 0x0000;
  }
  else
  {
	  //turn off led
	  LPC_GPIO0 ->DATA |= 0xffff;
  }
  /* z up down bonus*/
#endif
  }





  /* Check the content of the Master and slave buffer */
  while ( 1 );
  return 0;
}

/******************************************************************************
**                            End Of File
******************************************************************************/

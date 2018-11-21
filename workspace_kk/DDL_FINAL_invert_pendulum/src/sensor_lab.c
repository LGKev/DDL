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
#include "BNO055.h"
#include "type.h"
#include "i2c.h"
#include "gpio.h"
#include "LPC11xx.h"
#include <cr_section_macros.h>
#include "Pid.h"
#include "uart.h"
#include "string.h"


/* Data Buffer */
int16_t accBuffer[3];

#include "type.h"
#include "i2c.h"

extern volatile uint32_t I2CCount;
extern volatile uint8_t I2CMasterBuffer[BUFSIZE];
extern volatile uint8_t I2CSlaveBuffer[BUFSIZE];
extern volatile uint32_t I2CMasterState;
extern volatile uint32_t I2CReadLength, I2CWriteLength;


//uart buffers
extern volatile uint32_t UARTCount;
extern volatile uint8_t UARTBuffer[BUFSIZE];


 volatile uint8_t  uartCharReceived = 0;
volatile uint8_t currentState =0;
volatile uint8_t oldState =0;

/*******************************************************************************
**   Main Function  main()
*******************************************************************************/
/* read 2 byte */

void bno055Read(uint8_t startRegAddr, uint8_t length, int16_t *accBuffer) {

        // Clear buffers
        uint32_t i;
        for (i = 0; i < BUFSIZE; i++) {
            I2CMasterBuffer[i] = 0x00;
            I2CSlaveBuffer[i] = 0x00;
        }

         I2CWriteLength = 2;
         I2CReadLength = length; //2 to get 2 consecutigve data bytes
         I2CMasterBuffer[0] = BNO055_ADDR;
         I2CMasterBuffer[1] = startRegAddr; // gyro x axis

        // Clear buffers
      /* for (i = 0; i < BUFSIZE; i++) {
            I2CMasterBuffer[i] = 0x00;
            I2CSlaveBuffer[i] = 0x00;
        }
*/

        // Write to MPU6050 sensor: start to read
        // And tell the senor how many bytes you want to read from
        // TO-DO
       I2CMasterBuffer[2] = BNO055_ADDR|0b1; //repeated start
  I2CEngine();


        // Store data to acc buffers
        // TO-DO

  	  for(i=0; i<length; i++){
  		  	 accBuffer[i] = I2CSlaveBuffer[i];
  	  }

 } //end of mpu6050 read

int main (void)
{

   //UARTInit(UART_BAUD);






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

  /* i2c write to register: imu mode config */
  // using the default values of power on reset
  I2CWriteLength = 3; //is equal to , # of bytes,: counting: slave addr, register addres, data
  I2CReadLength = 0;
  I2CMasterBuffer[0] = BNO055_ADDR;
  I2CMasterBuffer[1] = 0x3D;	 //operation mode register	/* address */
  I2CMasterBuffer[2] = 0x08; // IMU mode 0b1000	/* all  */
  I2CEngine();






	  #ifdef correctWrite
  I2CWriteLength = 3;
  I2CReadLength = 0;
  I2CMasterBuffer[0] = MPU6050_ADDR;
  I2CMasterBuffer[1] = ACC_CONFIG;	//power config	/* address */
  I2CMasterBuffer[2] =ACC_4G ;		/* all  */
  I2CEngine();
#endif


 //#define correctRead
#ifdef correctRead
	  /* read 2 byte */
  I2CWriteLength = 2; //maybe 4
  I2CReadLength = 6; //2 to get 2 consecutigve data bytes
  I2CMasterBuffer[0] = MPU6050_ADDR;
  I2CMasterBuffer[1] = ACC_X_HI; // gyro x axis
  I2CMasterBuffer[2] = MPU6050_ADDR|0b1; //repeated start
  I2CEngine();
#endif


  uint8_t dataACCL[6];

  uint32_t delay;



  while(1){
	  bno055Read(0x1C, 2, dataACCL);
	  for(delay = 0; delay <10000; delay++);
  }


 return 0;
} //end of main

/******************************************************************************
**                            End Of File
******************************************************************************/

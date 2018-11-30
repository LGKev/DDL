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
#include "gpio.h"
#include "LPC11xx.h"
#include <cr_section_macros.h>
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

void mpu6050Read(uint8_t startRegAddr, uint8_t length, int16_t *accBuffer) {

        // Clear buffers
        uint32_t i;
        for (i = 0; i < BUFSIZE; i++) {
            I2CMasterBuffer[i] = 0x00;
            I2CSlaveBuffer[i] = 0x00;
        }

         I2CWriteLength = 2;
         I2CReadLength = length; //2 to get 2 consecutigve data bytes
         I2CMasterBuffer[0] = MPU6050_ADDR;
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
       I2CMasterBuffer[2] = MPU6050_ADDR|0b1; //repeated start
  I2CEngine();


        // Store data to acc buffers
        // TO-DO

  	  for(i=0; i<length; i++){
  		  	 accBuffer[i] = I2CSlaveBuffer[i];
  	  }

 } //end of mpu6050 read

int main (void)
{

   UARTInit(UART_BAUD);






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
	  if ( UARTCount != 0 ) //set by the interrupt handler
	  	{
	  	  LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
	  	  UARTCount = 0;
	  	  LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */
	  	}

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


  mpu6050Read(ACC_X_HI, 6, dataACCL);
  //getData();

  for(delay=0; delay<20000; delay++);

  //y axis
  if(I2CSlaveBuffer[2] <= 50 && I2CSlaveBuffer[3] >150){
	  //turn on led backward:
	  LPC_GPIO0 ->DATA &= ~(1<<7 | 1<<8);
	  currentState = 1;
  }
  else if(I2CSlaveBuffer[2] > 74 && I2CSlaveBuffer[2] < 230){
//turn on led forwrd: red
	  LPC_GPIO0 ->DATA &= ~(1<<7);
	  currentState = 2;
  }
  else if(I2CSlaveBuffer[0] <= 60 && I2CSlaveBuffer[2] <255 ){
	  //turn on led LEFT: BLUE
	  LPC_GPIO0 ->DATA &= ~(1<<9);
	 currentState = 3;
  }
  else if(I2CSlaveBuffer[0] > 60 && I2CSlaveBuffer[0] < 225){
//turn on led RIGHT: GREEN
	 // UARTSend("1. Control LED \n",strlen("1. Control LED \n"));
	  LPC_GPIO0 ->DATA &= ~(1<<8);
	  currentState = 4;
  }
  else if(I2CSlaveBuffer[4] >= 70){
	  //turn on led
	  LPC_GPIO0 ->DATA = 0x0000;
	  currentState = 5;
  }
  else
  {
	  //turn off led
	  LPC_GPIO0 ->DATA |= 0xffff;
	  currentState = 0;
  }
  /* z up down bonus*/

  if(currentState == 1 && oldState != currentState ){
  	  UARTSend("backward\n", 10);
  	  oldState = currentState;
  }
  else if(currentState == 2 && oldState != currentState ){
    	  UARTSend("forward\n", 9);
    	  oldState = currentState;
    }
  else if(currentState == 3 && oldState != currentState ){
    	  UARTSend("left\n", 6);
    	  oldState = currentState;
    }
  else if(currentState == 4 && oldState != currentState ){
    	  UARTSend("right\n", 7);
    	  oldState = currentState;
    }
  else if(currentState == 5 && oldState != currentState ){
    	  UARTSend("upside down\n", 13);
    	  oldState = currentState;
    }
  else{
  	//  UARTSend("flat\n", 6);
  	  oldState = currentState;
  }

  }







  /* Check the content of the Master and slave buffer */
  return 0;
} //end of main

/******************************************************************************
**                            End Of File
******************************************************************************/

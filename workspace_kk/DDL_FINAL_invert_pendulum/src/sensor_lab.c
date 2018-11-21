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
#include "timer32.h"

#include "type.h"

/* Data Buffer */
int16_t accBuffer[3];


extern volatile uint32_t I2CCount;
extern volatile uint8_t I2CMasterBuffer[BUFSIZE];
extern volatile uint8_t I2CSlaveBuffer[BUFSIZE];
extern volatile uint32_t I2CMasterState;
extern volatile uint32_t I2CReadLength, I2CWriteLength;


//uart buffers
extern volatile uint32_t UARTCount;
extern volatile uint8_t UARTBuffer[BUFSIZE];

//timer
extern volatile uint32_t timer32_0_counter;

//pid
extern unsigned long lastTime;
extern double Input, Output, Setpoint;
extern double errSum, lastErr;
extern double kp, ki, kd;


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

uint32_t millis(void);

uint32_t millis(void){
	return timer32_0_counter;
}

void initTimer32(void){
	//init_timer32(0, TIME_INTERVAL);
		//enable_timer32(0);
		// check 7.4 for pins for the 32 bit timer, IOCONFIG, some are used for jtag
			// check table 21/20 for power and peripheral blocks

			//enable clocks for timer32
			LPC_SYSCON -> SYSAHBCLKCTRL |= (1<<9); //bit 9 is timer32_0

			// we want interrupts, so TMR32B0_IR


			// we want to set the prescale divisor to get .5 mS resolution
				// 	recall, system clock is feeding APB
			LPC_TMR32B0 -> TCR |= (1<<0); // enable timer
			LPC_TMR32B0 -> TCR |= (1<<1); //reset timer
			LPC_TMR32B0 -> TCR &= ~(1<<1); //set bit 1 to zero.
			LPC_TMR32B0 -> TC = 0; // reset counter

			//set for 0.5ms tick count? lets not for now, maybe later,
			// currently we tick counter each time, and were at 1/12Mhz per tick.

			// we want to set what happens on a match, so TMR32B0_MCR and MCR0
			LPC_TMR32B0 -> MCR |= (1<<1); // enable reset of TC on match MR0
			LPC_TMR32B0 -> MCR |= (1<<0); // enable interrupt for TMR32b0, when match0


			//TODO: once the GPIO handler can calculate frequency, / or main. we
			// can set the MR0 to be a value, recalculate the 10s tick period.
			LPC_TMR32B0 -> MR0 = 24000; //value we count up to
			// TODO: fully remove eventually LPC_TMR32B0 -> MR1 = 24000000; //value we count up to

			// NOTE: not using the mr1 so need to reset the TC when MR0 is matched
			//LPC_TMR32B0 -> MCR |= (1<<4) | (1<<3); // disable reset for TMR32b0, when match0, so we can do the toggling.

			LPC_TMR32B0 -> IR = 0;
			NVIC_EnableIRQ(TIMER_32_0_IRQn); //timer32b timer0 interrupt
}

void initLED(){

	LPC_SYSCON -> SYSAHBCLKCTRL |= (1<<6) | (1<<16); //bit is the gpio enable

	//iocon_pio0.7 led
	//10-0: 0 0011 0  00 000 -> hex: 003000
	LPC_IOCON -> PIO0_7 = 0xd0; //0xd0 default will work. but never too sure
	LPC_GPIO0 -> DIR |= 0xFFF; //output red led btw make them all outputs!
	// the led's configured such that a GPIO:0 is on, and GPIO:1 is off.
	LPC_GPIO0 -> DATA |= 0xfff; //turn  all off
}

void initBNO055(void){
	  /* i2c write to register: imu mode config */
	  // using the default values of power on reset
	  I2CWriteLength = 3; //is equal to , # of bytes,: counting: slave addr, register addres, data
	  I2CReadLength = 0;
	  I2CMasterBuffer[0] = BNO055_ADDR;
	  I2CMasterBuffer[1] = 0x3D;	 //operation mode register	/* address */
	  I2CMasterBuffer[2] = 0x08; // IMU mode 0b1000	/* all  */
	  I2CEngine();
}

int main (void)
{
//	initTimer32();
	//initLED();
	//initBNO055();
    UARTInit(UART_BAUD);

    uint32_t delay;

    while(1){
	UARTSend("1. Control LED \n",strlen("1. Control LED \n"));
    for(delay=0; delay<30000; delay++);
    }

/* ======================================= */

  if ( I2CInit( (uint32_t)I2CMASTER ) == FALSE )	/* initialize I2c */
  {
	while ( 1 );				/* Fatal error */
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


setTunings(0,0,0);
Setpoint = 0;

  while(1){
	 bno055Read(0x1C, 2, dataACCL);
	 Input = dataACCL[0];
	  compute();

	  //Output should be calculated
	  //if statements.
  }
 return 0;
} //end of main

/******************************************************************************
**                            End Of File
******************************************************************************/

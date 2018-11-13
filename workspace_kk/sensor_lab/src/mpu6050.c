/*
 * mpu6050.c
 *
 *  Created on: Oct 17, 2017
 *      Author: AA_LQ
 */
#include "mpu6050.h"
#include "i2c.h"
#include "driver_config.h"
#include "target_config.h"

#include "type.h"

extern volatile uint32_t I2CCount;
extern volatile uint8_t I2CMasterBuffer[BUFSIZE];
extern volatile uint8_t I2CSlaveBuffer[BUFSIZE];
extern volatile uint32_t I2CMasterState;
extern volatile uint32_t I2CReadLength, I2CWriteLength;

/* MPU6050 read data, can be used to grab data from sensor*/
#ifdef broke
void mpu6050Read(uint8_t startRegAddr, uint8_t length, int16_t *accBuffer) {

        // Clear buffers
        uint32_t i;
        for (i = 0; i < BUFSIZE; i++) {
            I2CMasterBuffer[i] = 0x00;
            I2CSlaveBuffer[i] = 0x00;
        }

        // Write to MPU6050 sensor: start to read from which sensor
         I2CWriteLength = 2;
         I2CReadLength = length; //2 to get 2 consecutigve data bytes
         I2CMasterBuffer[0] = MPU6050_ADDR;
         //I2CMasterBuffer[1] = startRegAddr; // gyro x axis
         I2CMasterBuffer[1] = 0x3B; // gyro x axis

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

    }
#endif
/*:w
 *

void getData(void){
I2CWriteLength = 2; //maybe 4
I2CReadLength = 6; //2 to get 2 consecutigve data bytes
I2CMasterBuffer[0] = MPU6050_ADDR;
I2CMasterBuffer[1] = ACC_X_HI; // gyro x axis
I2CMasterBuffer[2] = MPU6050_ADDR|0b1; //repeated start
I2CEngine();
}*/


/* MPU6050 write data, can be used to configure register*/
void mpu6050Write(uint8_t regAdd,uint8_t regValue) {
        // Clear buffers
        uint32_t i;
        /*for (i = 0; i < BUFSIZE; i++) {
            I2CMasterBuffer[i] = 0x00;
            I2CSlaveBuffer[i] = 0x00;
        }*/

        I2CWriteLength = 3; //is equal to , # of bytes,: counting: slave addr, register addres, data
        I2CReadLength = 0;
        I2CMasterBuffer[0] = MPU6050_ADDR;
        I2CMasterBuffer[1] = regAdd;	//power config	/* address */
        I2CMasterBuffer[2] = regValue ;		/* all  */
        I2CEngine();
}

/* MPU6050 read who_am_i register, can be used to test I2C communication*/
void mpu6050CommTest(void) {
        // Clear buffers
        uint32_t i;
        /*for (i = 0; i < BUFSIZE; i++) {
            I2CMasterBuffer[i] = 0x00;
            I2CSlaveBuffer[i] = 0x00;
        }*/

        I2CWriteLength = 2; //maybe 4
          I2CReadLength = 6; //2 to get 2 consecutigve data bytes
          I2CMasterBuffer[0] = MPU6050_ADDR;
          I2CMasterBuffer[1] = 0x75 ; // the who the AM I REGISTER. I AM ME. have a laugh.
         I2CMasterBuffer[2] = MPU6050_ADDR|0b1; //repeated start
          I2CEngine();


   }



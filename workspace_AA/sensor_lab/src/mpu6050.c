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
void mpu6050Read(uint8_t startRegAddr, uint8_t length, int16_t *accBuffer) {

        // Clear buffers
        uint32_t i;
        for (i = 0; i < BUFSIZE; i++) {
            I2CMasterBuffer[i] = 0x00;
            I2CSlaveBuffer[i] = 0x00;
        }

        // Write to MPU6050 sensor: start to read from which sensor
        // TO-DO



        // Clear buffers
        // TO-DO



        // Write to MPU6050 sensor: start to read
        // And tell the senor how many bytes you want to read from
        // TO-DO




        // Store data to acc buffers
        // TO-DO



    }


/* MPU6050 write data, can be used to configure register*/
void mpu6050Write(uint8_t regAdd,uint8_t regValue) {
        // Clear buffers
        uint32_t i;
        for (i = 0; i < BUFSIZE; i++) {
            I2CMasterBuffer[i] = 0x00;
            I2CSlaveBuffer[i] = 0x00;
        }

        // Write to MPU6050: set a value to a register
        // TO-DO
    }


/* MPU6050 read who_am_i register, can be used to test I2C communication*/
void mpu6050CommTest(void) {
        // Clear buffers
        uint32_t i;
        for (i = 0; i < BUFSIZE; i++) {
            I2CMasterBuffer[i] = 0x00;
            I2CSlaveBuffer[i] = 0x00;
        }

        /* Read who am i register for testing */
        // Tell MPU6050 sensor: what is your name? -- Read the WHO_AM_I register
        // TO-DO

        // Print the value stored in WHO_AM_I register
        printf("Who_am_I = 0x%X ?\n",I2CSlaveBuffer[0]);
    }



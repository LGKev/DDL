/*
 * mpu6050.h
 *
 *  Created on: Oct 17, 2017
 *      Author: AA_LQ
 */

#include "driver_config.h"
#include "target_config.h"

#include "type.h"

#ifndef MPU6050_H_
#define MPU6050_H_

/*******************************************************************************
**	register
*******************************************************************************/
#define MPU6050_ADDR		0xD0
#define PWR_MGMT1			0x6B
#define WHO_AM_I			0x75
#define MPU6050_READ		0x01
#define ACC_REG				0x3B
#define ACC_BYTES 			0x06
#define ACC_CONFIG 			0x1C
// ACC_CONFIG = ACC_xG
#define ACC_2G				0x00 //16384 LSB/g
#define ACC_4G				0x08 //8192 LSB/g
#define ACC_8G				0x10 //4096 LSB/g
#define ACC_16G				0x18 //2048 LSB/g


/*******************************************************************************
**	functions
*******************************************************************************/
extern void mpu6050Read(uint8_t startRegAddr, uint8_t length, int16_t *accBuffer);
extern void mpu6050Write(uint8_t regAdd,uint8_t regValue);
extern void mpu6050CommTest(void);

#endif /* MPU6050_H_ */

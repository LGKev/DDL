#include "driver_config.h"
#include "target_config.h"
#include "BNO055.h"
#include "type.h"
#include "i2c.h"
#include "gpio.h"
#include "LPC11xx.h"
#include <cr_section_macros.h>
//#include "Pid.h"
//#include "PID_v1.h"
#include "uart.h"
#include "string.h"
#include "timer32.h"
#include "timer16.h"

#include "pid_team.h"

#include "type.h"

#define newPID





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

//timer32
extern volatile uint32_t timer32_0_counter;
extern volatile uint32_t timer32_1_counter;

//timer16
volatile uint32_t period = 1000;  //1khz PWM frequency, 500 is 2khz
volatile uint8_t dutyCycle = 0;

#ifdef oldPID
//pid
extern unsigned long lastTime;
extern float Input, Output, Setpoint;
extern double errSum, lastErr;
extern double kp, ki, kd;
#endif

#ifdef newPID
float Input, Output, SetPoint;
float kp = 0.1;
float ki = 0;
float kd = 0;

#endif

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

	  if ( I2CInit( (uint32_t)I2CMASTER ) == FALSE )	/* initialize I2c */
	  {
		while ( 1 );				/* Fatal error */
	  }
	  /* i2c write to register: imu mode config */
	  // using the default values of power on reset
	  I2CWriteLength = 3; //is equal to , # of bytes,: counting: slave addr, register addres, data
	  I2CReadLength = 0;
	  I2CMasterBuffer[0] = BNO055_ADDR;
	  I2CMasterBuffer[1] = 0x3D;	 //operation mode register	/* address */
	  I2CMasterBuffer[2] = 0x08; // IMU mode 0b1000	/* all  */
	  I2CEngine();
}

void initGPIO_PWM_LEFT(void){
	//AHB clock set with initLED();
//	LPC_GPIO1 -> DIR |= (1<<9);
	//LPC_GPIO1 -> DATA &= ~(1<<9); //off

	//Input 1 and input 2 set up GPIO output
	//port 3 pin1 and port 3 pin2
	LPC_GPIO3 -> DIR |= (1<<1 | 1<<2);
	LPC_GPIO3 -> DATA &= ~(1<<1 | 1<<2); //off

}
void initGPIO_PWM_RIGHT(void){
	//AHB clock set with initLED();

	//Input 3 and input 4 set up GPIO output
	//port 2 pin1 and port 3 pin2
	LPC_GPIO2 -> DIR |= (1<<1 | 1<<2);
	LPC_GPIO2 -> DATA &= ~(1<<1 | 1<<2); //off

}

void setDutyCycle16_0(uint8_t dutyCycle){ //pass in a percentage from 0 to 99;

	float dutyCycleCalculated = (float)(1.0)/(1.0-((float)dutyCycle/100.0));

	uint32_t result = (uint32_t)((float) period/dutyCycleCalculated);

	LPC_TMR16B0->MR0 = result;

}


#ifdef newPID
PidType pidObject;
#endif

int main (void){
    uint32_t delay;
	init_timer16(0, TIME_INTERVAL);
	init_timer16PWM(0, period, MATCH0, 0);
	enable_timer16(0);

	initTimer32();

	initLED();

	initBNO055();
    //UARTInit(UART_BAUD);
	initGPIO_PWM_LEFT();
	initGPIO_PWM_RIGHT();

	setDutyCycle16_0(50);



/* ======================================= */
 uint8_t dataACCL[6];

#ifdef oldPID
double kp1 = 1;
double kd1 = 0;// 1.2;
double ki1 = 0;
double addDuty = 30;
double window =4;
double range = 3000;
double maxRange = 300;
setTunings(kp1,ki1, kd1);
Setpoint = -22.0;
#endif

#ifdef newPID


	  				PID_init(&pidObject, kp, ki, kd, PID_Direction_Direct);
	  				PID_SetMode(&pidObject, PID_Mode_Automatic);
	  				PID_SetOutputLimits(&pidObject, -99, 99);
	  				PID_SetSampleTime(&pidObject, 5); //5 milliseconds

	  				pidObject.mySetpoint = -45;//faling towards heat sink.
	  				//-35 for falling away from heat sink

#endif
  while(1){


	 bno055Read(0x1C, 2, dataACCL);

#ifdef newPID
	 Input = (float)(((I2CSlaveBuffer[1]<<24) | I2CSlaveBuffer[0] <<16))/65536.0;
#endif

	 pidObject.myInput = Input;
	 pidObject.kd = kd;
	 pidObject.kp = kp;
	 pidObject.ki = ki;

	 printf("input: %f \t \t", pidObject.myInput);


	 //for(delay = 0; delay <10000; delay++);

#ifdef oldPID
	 Input = (float)(((I2CSlaveBuffer[1]<<24) | I2CSlaveBuffer[0] <<16))/65536.0;
#endif
	 double Input_dataaccl = (double)( (dataACCL[2]<<8) | dataACCL[0]);



#ifdef oldPID
	 compute();
#endif


#ifdef newPID
#endif
	  //Output should be calculated
	  //if statements.
	 // UARTSend(BufferPtr, )

#ifdef oldPId
	 printf("output: %f \t", Output);
	  printf("input: %f \t \n", Input);

#endif
	  //LEFT

#ifdef newPID

PID_Compute(&pidObject);

printf("pidObject->myOutput: %f \n", pidObject.myOutput);

#endif


//#define stupid
#ifdef stupid
	  		if(Input >-10)
	  		{
	  			//LEFT
	  				  							LPC_GPIO3->DATA |= (1<<1);
	  				  							LPC_GPIO3->DATA &= ~(1<<2);

	  				  						//RIGHT
	  				  							LPC_GPIO2->DATA |= (1<<1);
	  				  							LPC_GPIO2->DATA &= ~(1<<2);



	  		}
	  		else if(Input < -30)
	  		{
	  			//LEFT
	  				  							LPC_GPIO3->DATA |= (1<<2);
	  				  							LPC_GPIO3->DATA &= ~(1<<1);

	  				  						//RIGHT
	  				  							LPC_GPIO2->DATA |= (1<<2);
	  				  							LPC_GPIO2->DATA &= ~(1<<1);
	  		}
	  		else
	  		{
	  			initGPIO_PWM_LEFT();
	  				initGPIO_PWM_RIGHT();
	  		}
#endif

#define normal
#ifdef normal




	  		float offsetOutput = 200 + pidObject.myOutput;

	  if(pidObject.myOutput > 0.0)
	  {
		  //dutyCycle = (uint32_t)((Output) / range *100.0) +addDuty;
			//LEFT
				LPC_GPIO3->DATA |= (1<<2);
				LPC_GPIO3->DATA &= ~(1<<1);

			//RIGHT
				LPC_GPIO2->DATA |= (1<<2);
				LPC_GPIO2->DATA &= ~(1<<1);


	 	  setDutyCycle16_0((1.0)*pidObject.myOutput); //checked out on scope, looks correct
	  }
	  else if(pidObject.myOutput < 0)
	  {

			LPC_GPIO3->DATA &= ~(1<<2);
			LPC_GPIO3->DATA |= (1<<1);

		//RIGHT
			LPC_GPIO2->DATA &= ~(1<<2);
			LPC_GPIO2->DATA |= (1<<1);

		 // dutyCycle = (uint32_t)(Output / -range * 100.0) +addDuty;
			/*//LEFT
				LPC_GPIO3->DATA |= (1<<1);
				LPC_GPIO3->DATA &= ~(1<<2);

			//RIGHT
				LPC_GPIO2->DATA |= (1<<1);
				LPC_GPIO2->DATA &= ~(1<<2);
				*/

				float offsetOutput = 200 + pidObject.myOutput;

				float dutyTest =(-1.0)*(pidObject.myOutput);

	 	  setDutyCycle16_0(dutyTest);
	  }
		//  setDutyCycle16_0(0);

#endif

//#define test2
#ifdef test2

		float offsetOutput = 200 + pidObject.myOutput;

while(pidObject.myOutput > 0.0)
{
PID_Compute(&pidObject);
	  //dutyCycle = (uint32_t)((Output) / range *100.0) +addDuty;
		//LEFT
			LPC_GPIO3->DATA |= (1<<2);
			LPC_GPIO3->DATA &= ~(1<<1);

		//RIGHT
			LPC_GPIO2->DATA |= (1<<2);
			LPC_GPIO2->DATA &= ~(1<<1);


	  setDutyCycle16_0((1.0)*pidObject.myOutput); //checked out on scope, looks correct
}
while(pidObject.myOutput < 0)
{

PID_Compute(&pidObject);
		LPC_GPIO3->DATA &= ~(1<<2);
		LPC_GPIO3->DATA |= (1<<1);

	//RIGHT
		LPC_GPIO2->DATA &= ~(1<<2);
		LPC_GPIO2->DATA |= (1<<1);

	 // dutyCycle = (uint32_t)(Output / -range * 100.0) +addDuty;
		/*//LEFT
			LPC_GPIO3->DATA |= (1<<1);
			LPC_GPIO3->DATA &= ~(1<<2);

		//RIGHT
			LPC_GPIO2->DATA |= (1<<1);
			LPC_GPIO2->DATA &= ~(1<<2);
			*/

			float offsetOutput = 200 + pidObject.myOutput;

			float dutyTest =(-1.0)*(pidObject.myOutput);

	  setDutyCycle16_0(dutyTest);
}
	//  setDutyCycle16_0(0);

#endif
  }
return 0;

}
//end of main
/******************************************************************************
**                            End Of File
******************************************************************************/
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

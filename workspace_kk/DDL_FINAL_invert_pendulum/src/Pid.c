/*
 * Pid.c
 *
 *  Created on: Nov 21, 2018
 *      Author: http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-introduction/
 */
#include "Pid.h"
#include "type.h"

extern uint32_t millis();

/*working variables*/
unsigned long lastTime;
float Input, Output, Setpoint;
double errSum, lastErr;
double kp, ki, kd;
double lastOutput;
void compute()
{
   /*How long since we last calculated*/
   unsigned long now = millis();
   double timeChange = (double)(now - lastTime);

   /*Compute all the working error variables*/
   double error = Setpoint - Input;
   errSum += (error * timeChange);
   double dErr = (error - lastErr) / timeChange;

   /*Compute PID Output*/
   Output = kp * error + ki * errSum + kd * dErr;
   lastOutput = Output;

  /* if(Output >= 2300){
	   Output = 2300;
   }else if(Output <= -3400){
	   Output =-3400;
   }
   else{
	   Output = lastOutput;
   }
*/

   /*Remember some variables for next time*/
   lastErr = error;
   lastTime = now;
}

void setTunings(double Kp, double Ki, double Kd)
{
   kp = Kp;
   ki = Ki;
   kd = Kd;
}

/*
 * Pid.c
 *
 *  Created on: Nov 21, 2018
 *      Author: kkuwata
 */
#include "Pid.h"

/*working variables*/
unsigned long lastTime;
double Input, Output, Setpoint;
double errSum, lastErr;
double kp, ki, kd;
void Compute(void){

   /*Compute all the working error variables*/
   double error = Setpoint - Input;
 //  errSum += (error * timeChange);
   //double dErr = (error - lastErr) / timeChange;

   /*Compute PID Output*/
//   Output = kp * error + ki * errSum + kd * dErr;

   /*Remember some variables for next time*/
  // lastErr = error;
   //lastTime = now;
}

void SetTunings(double Kp, double Ki, double Kd){
   kp = Kp;
   ki = Ki;
   kd = Kd;
}

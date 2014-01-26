#include "hbridgelib.h"
#include <wiringPi.h>
#include <string.h>
#include <errno.h>
#include <stdio.h> 

/* Motor control inputs:
* 		M1_IN1 / M2_IN4		M1_IN2 / M2_IN3	
*	FW		1			0
*	BW		0			1
*	Break		1			1
*	Free		0			0
*/



HBridge::HBridge (	int in1, 
			int in2, 
			int in3, 
			int in4, 
			int enA, 
			int enB	) : pwm_m1(false), pwm_m2(false)
{
	m1_in1 = in1;	m1_in2 = in2;
	m2_in1 = in3;	m2_in2 = in4;
	enableA = enA;	enableB = enB;

        pwm_m1.setPWMFreq(PWM_FREQ);
        pwm_m2.setPWMFreq(PWM_FREQ);

	// Init GPIO
        if (wiringPiSetupGpio () == -1)
        {
                fprintf (stderr, "Can't initialise wiringPi: %s\n", strerror (errno));
        } else {
                pinMode(m1_in1, OUTPUT);	pinMode(m1_in2, OUTPUT);
                pinMode(m2_in1, OUTPUT);	pinMode(m2_in2, OUTPUT);
        }
}

bool HBridge::setDirection(bool d)
{
	if ( d==FW ) {
		digitalWrite(m1_in1, HIGH); digitalWrite(m2_in2, HIGH);
		digitalWrite(m1_in2, LOW); digitalWrite(m2_in1, LOW);
	} else if ( d==BW ) {
		digitalWrite(m1_in1, LOW); digitalWrite(m2_in2, LOW);
		digitalWrite(m1_in2, HIGH); digitalWrite(m2_in1, HIGH);	
	} else {
		return false;
	}
        return true;
}

bool HBridge::setSpeed(int percentage)
{
	if (percentage>0 && percentage<=100){
		int ticks = PWM_NO_TICKS * percentage / 100;
		pwm_m1.setPWM(enableA, 0, ticks);
		pwm_m2.setPWM(enableB, 0, ticks);
		return true;
	} else return false;
}


void HBridge::stopMotors(){
	digitalWrite(m1_in1, HIGH); digitalWrite(m2_in2, HIGH);
	digitalWrite(m1_in2, HIGH); digitalWrite(m2_in1, HIGH);	
	pwm_m1.setPWM(enableA, 0, PWM_NO_TICKS/2);
	pwm_m2.setPWM(enableB, 0, PWM_NO_TICKS/2);
}


void HBridge::setFreespin(){
	digitalWrite(m1_in1, LOW); digitalWrite(m2_in2, LOW);
	digitalWrite(m1_in2, LOW); digitalWrite(m2_in1, LOW);
}

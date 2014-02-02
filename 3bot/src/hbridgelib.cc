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

DCMotor::DCMotor ( int in1, int in2, int en ) : pwm_m(false)
{
	m_in1 = in1; m_in2 = in2;
	enable = en;
	pwm_m1.setPWMFreq(PWM_FREQ);

	// Init GPIO
        if (wiringPiSetupGpio () == -1)
        {
                fprintf (stderr, "Can't initialise wiringPi: %s\n", strerror (errno));
        } else {
                pinMode(m_in1, OUTPUT);	pinMode(m_in2, OUTPUT);
        }
	
}


bool DCMotor::SetDirection(bool d)
{
	if ( d==FW ) {
		digitalWrite(m_in1, HIGH);	digitalWrite(m_in2, LOW);
	} else if ( d==BW ) {
		digitalWrite(m_in1, LOW);	digitalWrite(m_in2, HIGH);	
	} else {
		return false;
	}
        return true;
}

DCMotor::setSpeed(int percentage)
{
	if (percentage>0 && percentage<=100){
		int ticks = PWM_NO_TICKS * percentage / 100;
		pwm_m.setPWM(enable, 0, ticks);
		return true;
	} else return false;
}

DCMotor::stopMotor(){
	digitalWrite(m_in1, HIGH); digitalWrite(m_in2, HIGH);	
	pwm_m.setPWM(enable, 0, PWM_NO_TICKS);
}

DCMotor::setFreespin(){
	digitalWrite(m_in1, LOW);	digitalWrite(m_in2, LOW);
	pwm_m.setPWM(enable, 0, 0);
}

HBridge::HBridge (	int in1, 
			int in2, 
			int in3, 
			int in4, 
			int enA, 
			int enB	)
{
	m1(in1, in2, enA);
	m2(in3,	in4, enB);
}


bool HBridge::movePlatform(float speed, float radius)
{
	// TODO
	if (speed>=0) {
		m1.setDirection(FW);
		m2.setDirection(FW);
	} else {
		m1.setDirection(BW);
		m2.setDirection(BW);
	}

	m1.setSpeed(50);
	m2.setSpeed(50);
	return true;
}


void HBridge::stopPlatform(){
	// TODO
	m1.stopMotor();
	m2.stopMotor();

}



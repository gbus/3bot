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
	pwm_m.setPWMFreq(PWM_FREQ);

	// Init GPIO
        if (wiringPiSetupGpio () == -1)
        {
                fprintf (stderr, "Can't initialise wiringPi: %s\n", strerror (errno));
        } else {
                pinMode(m_in1, OUTPUT);	pinMode(m_in2, OUTPUT);
        }
	
}


bool DCMotor::setDirection(bool d)
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

bool DCMotor::setSpeed(int percentage)
{
	if (percentage>0 && percentage<=100){
		int ticks = PWM_MAX_TICKS * percentage / 100;
		pwm_m.setPWM(enable, 0, ticks);
		return true;
	} else return false;
}

bool DCMotor::setPWMticks(int ticks)
{
	if (ticks>=0 && ticks<PWM_MAX_TICKS) {
		pwm_m.setPWM(enable, 0, ticks);
		return true;
	} else {
		return false;
	}
}

void DCMotor::stopMotor(){
	digitalWrite(m_in1, HIGH); digitalWrite(m_in2, HIGH);	
	pwm_m.setPWM(enable, 0, PWM_MAX_TICKS);
}

void DCMotor::setFreespin(){
	digitalWrite(m_in1, LOW);	digitalWrite(m_in2, LOW);
	pwm_m.setPWM(enable, 0, 0);
}

HBridge::HBridge (	int in1, 
			int in2, 
			int in3, 
			int in4, 
			int enA, 
			int enB	) : rightmotor(in1, in2, enA), leftmotor(in3, in4, enB)
{
}

void HBridge::directPlatform(bool direction){
        if (direction) {
                rightmotor.setDirection(FW);
                leftmotor.setDirection(BW);
        } else {
                rightmotor.setDirection(BW);
                leftmotor.setDirection(FW);
        }
}

bool HBridge::PWMtuning(bool direction, int tick_1, int tick_2) {
	directPlatform(direction);
	if ( rightmotor.setPWMticks(tick_1) && leftmotor.setPWMticks(tick_2) ) {
		return true;
	} else return false;
}

bool HBridge::movePlatform(float speed, float radius)
{
	// TODO
	if (speed>=0) {
		directPlatform(FW);
	} else {
		directPlatform(BW);
	}

	rightmotor.setSpeed(80);
	leftmotor.setSpeed(80);
	return true;
}


bool HBridge::stopPlatform(){
	// TODO
	rightmotor.stopMotor();
	leftmotor.stopMotor();
	return true;
}



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
	if ( d ) {
		digitalWrite(m_in1, HIGH);	digitalWrite(m_in2, LOW);
	} else {
		digitalWrite(m_in1, LOW);	digitalWrite(m_in2, HIGH);	
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

GamePadHBridge::GamePadHBridge(
				int in1,
				int in2,
				int in3,
				int in4,
				int enA,
				int enB) : HBridge(in1,in2,in3,in4,enA,enB){
	
}

void GamePadHBridge::calculateDirection(){
	// Top half circle of the joystick is in 0-180 degrees: move forward
	if (value >= 0 and value <= 180) {
		directPlatform(FW);
	} else {
		directPlatform(BW);
	}
}

/*
*
*
*
*/
void GamePadHBridge::angleToPWMspeeds(){
	int sector;
	if (value>=0 and value<90) {
		sector=1;
	} else if (value>=90 and value<180) {
		sector=2;
		value = value - 90;
	} else if (value>=180 and value<270) {
		sector=3;
		value = value - 180;
	} else if (value>=270 and value<360) {
		sector=4;
		value = value - 270;
	}

	// From here "value" is a number between 0 and 90
	// Calculate no of ticks proportionally to "value"
	// and reduce according to "intensity"
	int jl_pwm_val = (int)PWM_MAX_TICKS*value/90*intensity;
	int jl_pwm_max = (int)PWM_MAX_TICKS * intensity;

	if (sector == 1 or sector == 4) { // Joystick on the right
		pwm_left	= jl_pwm_max;
		pwm_right	= jl_pwm_val;
	} else { // Joystick on the left
		pwm_left	= jl_pwm_val;
		pwm_right	= jl_pwm_max;
	}
}

void GamePadHBridge::setCommand(char* c, char* e, char* v, float i){
	if ( c == "jl" ) value = (int)v;
	else button_value = v;
	command		= c;
	event		= e;
	intensity	= i;
}

int GamePadHBridge::runCommand(){
	if (command == "jl"){
		if (event == "release") {
			stopPlatform();
		} else if (event == "press") {
			calculateDirection();
			angleToPWMspeeds();
			rightmotor.setPWMticks(pwm_right);
			leftmotor.setPWMticks(pwm_left);
		}
	} else if (command[0] == 'b'){
		stopPlatform();
	} else return -1;
}

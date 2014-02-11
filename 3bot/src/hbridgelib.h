#ifndef hbridgelibH
#define hbridgelibH

/*
* Rasperry PI, Dual-hbridge library.
* Implement basic functions to drive two DC motors using a L298N H-Bridge:
* - setDirection
* - setSpeed
* - stopMotors
* - setFreespin
* 
* The L298N is controlled by 4 GPIO outputs (direction) and 2 PWM channels (speed)
*/

#include "pwmlib.h"

#define PWM_FREQ                1000

// Speed definitions
#define PWM_MAX_TICKS		4095

#define FW			0
#define BW			1

// GamePad control definitions
#define	GAMEPAD_LEFT	0
#define	GAMEPAD_FW	90
#define	GAMEPAD_RIGHT	180
#define	GAMEPAD_BACK	270


class DCMotor
{
 private:
	PWM pwm_m;
	int m_in1,m_in2;
	int enable;
 public:
	DCMotor(int,int,int);
	bool setDirection(bool);
	bool setSpeed(int);
	bool setPWMticks(int);
	void stopMotor();
	void setFreespin();
};


class HBridge
{
protected:
        DCMotor rightmotor;
        DCMotor leftmotor;
	void directPlatform(bool direction);
public:
        HBridge(int in1, int in2, int in3, int in4, int enA, int enB);
	bool PWMtuning(bool, int, int);
	bool movePlatform(float speed, float radius);
	bool stopPlatform();
};


class GamePadHBridge:public HBridge
{
private:
	char*	command;
	char*	event;
	char*	button_value;
	int	value;
	float	intensity;
	float	pwm_left;
	float	pwm_right;
	void	calculateDirection();
	void	angleToPWMspeeds();
public:
	GamePadHBridge(int in1, int in2, int in3, int in4, int enA, int enB);
	void setCommand(char* c, char* e, char* v, float i);
	int runCommand();
};


#endif

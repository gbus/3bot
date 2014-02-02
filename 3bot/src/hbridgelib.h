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
#define PWM_NO_TICKS		4095

#define FW			0
#define BW			1

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
	void stopMotor();
	void setFreespin();
}


class HBridge
{
private:
        DCMotor m1;
        DCMotor m2;
public:
        HBridge(int in1, int in2, int in3, int in4, int enA, int enB);
	bool movePlatform(float speed, float radius);
	bool stopPlatform();
};
#endif

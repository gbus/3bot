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


class HBridge
{
private:
        PWM pwm_m1;
        PWM pwm_m2;
	int m1_in1, m1_in2, m2_in1, m2_in2;
	int enableA, enableB;
public:
        HBridge(int, int, int, int, int, int);
	bool setDirection(bool);
	bool setSpeed(int);
	void stopMotors();
	void setFreespin();
};

#endif

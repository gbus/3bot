#ifndef servolibH
#define servolibH

#include "../i2c_pi_c/pwmlib.h"

#define PWM_FREQ		60

class Servo: public PWM
{
private:
	int servomin;
	int servomax;
	int channel;
protected:
	int get_neutral_pos();	
public:
	Servo(bool, int, int, int): PWM(bool);
	int reset_position();
	int set_position( int );
	void set_channel( int, int, int );
	int step_position( int );
	int get_current_pos();	
};

#endif

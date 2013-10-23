#ifndef servolibH
#define servolibH

#include "../i2c_pi_c/pwmlib.h"

#define PWM_FREQ		60

class Servo: public PWM
{
private:
	int min_pos;
	int max_pos;
	int channel;
	int pos;
protected:
	int get_neutral_pos();	
public:
	Servo(bool debug, int ch, int min, int max);
	int reset_position();
	int set_position( int );
	void set_servo( int, int, int );
	int step_position( int );
	int get_current_pos();	
};

#endif

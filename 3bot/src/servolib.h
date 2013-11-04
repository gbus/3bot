#ifndef servolibH
#define servolibH

#include "pwmlib.h"

#define PWM_FREQ		60

// Define the min/max speed in m/s
#define MIN_SPEED		0.2
#define MAX_SPEED		0.8

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
	int step_position( int );

	int set_position( int );
	int get_current_pos();	
	float get_current_speed();
	int speed_to_pos(float);
};

#endif

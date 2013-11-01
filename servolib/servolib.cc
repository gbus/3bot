#include "servolib.h"


Servo::Servo(bool debug, int ch, int min, int max) : PWM(debug)
{
	channel = ch;
	min_pos = min;
	max_pos = max;
	setPWMFreq(PWM_FREQ);
}

int Servo::reset_position()
{
	return set_position(get_neutral_pos());
}


// Set a given value (position) for the servo 
int Servo::set_position( int position )
{
	pos = position;
	if (position < min_pos ) {
		pos = min_pos;
	} else if ( position > max_pos ) {
		pos = max_pos;
	}
	setPWM(channel, 0, pos);
	return pos;
}
	
// Set channel to use and load its settings
void Servo::set_servo( int ch, int min, int max )
{
	channel = ch;
	min_pos	= min;
	max_pos	= max;
}


// Increase number of steps the current position
int Servo::step_position( int steps )
{
	pos += steps;
	return set_position(pos);
}


// Get current position
int Servo::get_current_pos()
{
	return pos;
}

// Converts the speed (m/s) in a position for a continous servo
void Servo::speed_to_pos(float)
{
}


float Servo::pos_to_speed()
{
}

// Get neutral position
int Servo::get_neutral_pos()
{
	return min_pos + ((max_pos - min_pos) / 2);
}

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
int Servo::speed_to_pos(float speed)
{
	return ( (max_pos-min_pos)*(speed-MIN_SPEED) / (MAX_SPEED-MIN_SPEED) ) + min_pos;	
}


float Servo::get_current_speed()
{
	float speed = 0.0;
	// implement conversion here
	return speed;
}

// Get neutral position
int Servo::get_neutral_pos()
{
	return min_pos + ((max_pos - min_pos) / 2);
}

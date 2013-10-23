#include "pwmlib.h"


Servo::Servo(bool debug, int ch, int min, int max) : PWM(debug)
{
	channel = ch;
	min_pos = min;
	max_pos = max;
	setPWMFreq(PWM_FREQ);
}

Servo::reset_position()
{
	ret = set_position(get_neutral_pos());
	return ret;
}


# Set a given value (position) for the servo 
int Servo::set_position( int position )
{
	pos = position;
	if (position < min_pos ) {
		pos = min_pos;
	} else if ( position > max_pos ) {
		pos = max_pos;
	}
	return setPWM(channel, 0, pos);
}
	
# Set channel to use and load its settings
void Servo::set_servo( int ch, int min, int max )
{
	channel = ch;
	min_pos	= min;
	max_pos	= max;
}


# Increase number of steps the current position
int Servo::step_position( int steps )
{
	pos += steps;
	return set_position(self.pos);
}


# Get current position
int Servo::get_current_pos()
{
	return pos;
}

# Get neutral position
int Servo::get_neutral_pos()
{
	return min_pos + ((max_pos - min_pos) / 2);
}

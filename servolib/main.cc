
#include "../i2c_pi_c/pwmlib.h"
#include "servolib.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <time.h>

#define CHANNEL 0
#define MIN	300
#define MAX	500
#define DEBUG	false

using namespace std;

int main(void)
{
	Servo s(DEBUG, CHANNEL, MIN, MAX);
	cout << "Setting servo values" << endl;
	s.set_servo( CHANNEL, MIN, MAX );
	
	cout << "Position reset to value " << s.reset_position() << endl;
	cout << "Stepping +20 " << s.step_position(20) << endl;
	sleep(3);
	cout << "Position reset to value " << s.reset_position() << endl;
	
	exit(0);
}


/*
#include <wiringPi.h>
#include <wiringPiI2C.h>
*/
#include <iostream>
#include <time.h>


#define LEFT_ENCODER		11
#define RIGHT_ENCODER 		8
#define NANO_SECOND_MULTIPLIER  1000000

using namespace std;

int main (void)  
{
	timespec sleepval = {0};
	const unsigned long INTERVAL_MS = 200 * NANO_SECOND_MULTIPLIER;
	sleepval.tv_nsec = INTERVAL_MS;
	bool left_status = LOW;
	bool right_status = LOW;
	bool left_curr = LOW;
	bool right_curr = LOW;

	wiringPiSetupGpio ();
	pinMode(LEFT_ENCODER, INPUT);
	pinMode(RIGHT_ENCODER, INPUT);
	

	while (1)
	{
		if (left_curr = digitalRead(LEFT_ENCODER) != left_status)
		{
			left_status = left_curr;
			cout << "Left state changed to: " << left_status << endl;
		}
		if (right_curr = digitalRead(RIGHT_ENCODER) != right_status)
		{
			right_status = right_curr;
			cout << "Right state changed to: " << right_status << endl;
		}
        	nanosleep(&sleepval, NULL);
	}
}






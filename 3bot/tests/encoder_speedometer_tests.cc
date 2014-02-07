

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include <iostream>
#include <time.h>
#include <sys/time.h>


#define LEFT_ENCODER		11
#define RIGHT_ENCODER 		8
#define NANO_SECOND_MULTIPLIER  1000000

using namespace std;


int main(void)
{
	timespec sleepval = {0};
	const unsigned long INTERVAL_MS = 100 * NANO_SECOND_MULTIPLIER;
	sleepval.tv_nsec = INTERVAL_MS;
	struct timeval t1,t2,elapsed;

	long int left_counter = 0; 
	long int right_counter = 0;
	int counter = 0;
	unsigned long left_ticks;
	unsigned long right_ticks;
	bool left_status = LOW;
	bool right_status = LOW;
	bool left_curr = LOW;
	bool right_curr = LOW;

	// Init time 0
	gettimeofday(&t1,NULL);
	while true
	{
		// increase counter when state change
		if (left_curr = digitalRead(LEFT_ENCODER) != left_status)
		{
			left_status = left_curr;
			left_counter++;
		}
		if (right_curr = digitalRead(RIGHT_ENCODER) != right_status)
		{
			right_status = right_curr;
			right_counter++;
		}

		// check time. If timer=100ms calculate speed
		gettimeofday(&t2,NULL);
		timeval_subtract (&elapsed, &t2, &t1);
		if (elapsed >= INTERVAL_MS) {			
			// sum up ticks detected every 100ms and report the average of 10 samples every 1 second
			left_ticks += left_counter;
			right_ticks += right_counter;
			if ( counter++ == 10 ) {
				cout << "Average ticks per 100ms (l/r): " << (float)left_ticks/10 << "/" << (float)right_ticks/10 << endl;
				left_ticks = 0; right_ticks = 0;
				counter = 0;
			}
				
				
			// reset timer and counter
			gettimeofday(&t1,NULL);
			left_counter = 0;
			right_counter = 0;
		}
		
	}

}

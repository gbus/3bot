

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include <iostream>
#include <time.h>
#include <sys/time.h>


#define LEFT_ENCODER		11
#define RIGHT_ENCODER 		8
#define NANO_SECOND_MULTIPLIER  1000000

using namespace std;

int timeval_subtract (struct timeval *result, struct timeval *x, struct timeval *y)
{    
	/* Perform the carry for the later subtraction by updating y. */
	if (x->tv_usec < y->tv_usec) {
		int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
		y->tv_usec -= 1000000 * nsec;
		y->tv_sec += nsec;
	}
	if (x->tv_usec - y->tv_usec > 1000000) {
		int nsec = (x->tv_usec - y->tv_usec) / 1000000;
		y->tv_usec += 1000000 * nsec;
		y->tv_sec -= nsec;
	}
     
	/* Compute the time remaining to wait.
	*  tv_usec is certainly positive. */
	result->tv_sec = x->tv_sec - y->tv_sec;
	result->tv_usec = x->tv_usec - y->tv_usec;
     
	/* Return 1 if result is negative. */
	return x->tv_sec < y->tv_sec;
}


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

        wiringPiSetupGpio ();
        pinMode(LEFT_ENCODER, INPUT);
        pinMode(RIGHT_ENCODER, INPUT);

	// Init time 0
	gettimeofday(&t1,NULL);
	while (1)
	{
		// increase counter when state change
		left_curr = digitalRead(LEFT_ENCODER);
		if (left_curr != left_status)
		{
			left_status = left_curr;
			left_counter++;
		}
		right_curr = digitalRead(RIGHT_ENCODER);
		if (right_curr != right_status)
		{
			right_status = right_curr;
			right_counter++;
		}

		// check time. If timer=100ms calculate speed
		gettimeofday(&t2,NULL);
		timeval_subtract (&elapsed, &t2, &t1);

		if (elapsed.tv_usec >= 100000) {			
			// sum up ticks detected every 100ms and report the average of 10 samples every 1 second
			left_ticks += left_counter;
			right_ticks += right_counter;
			counter++;
			if ( counter == 10 ) {
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

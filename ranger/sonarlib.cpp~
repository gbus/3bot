#include <string.h>
#include <errno.h>  
#include <sys/time.h>
#include <stdio.h>  
#include <wiringPi.h> 
#include "sonarlib.h" 

Sonar::Sonar(int trigger_pin, int echo_pin)
{
	trigpin = trigger_pin;
	echopin = echo_pin;

	if (wiringPiSetupGpio () == -1)  
	{  
		fprintf (stderr, "Can't initialise wiringPi: %s\n", strerror (errno));
	} else {
		pinMode(trigpin, OUTPUT);  
		pinMode(echopin, INPUT);
	}
}


int waitforpin(int pin, int level, int timeout)
{
 	struct timeval now, start;  
 	int done;  
	long micros;
	  
	gettimeofday(&start, NULL);  
	micros = 0;  
	done=0;  
   
	while (!done)  
	{  
		gettimeofday(&now, NULL);  
		if (now.tv_sec > start.tv_sec) {
			micros = 1000000L;
		} else {
			micros = 0;
		}  
		micros = micros + (now.tv_usec - start.tv_usec);  
		if (micros > timeout) done=1;  
		if (digitalRead(pin) == level) done = 1;  
	}  
	return micros;
}


int sonarread ()
{
	/* trigger reading */  
	digitalWrite(trigpin, HIGH);  
	waitforpin(echopin, TIMEOUT, 10); /* wait 10 microseconds */  
	digitalWrite(trigpin, LOW);  
	/* wait for reading to start */  
	waitforpin(echopin, HIGH, 5000); /* 5 ms timeout */
	
	if (digitalRead(echopin) == HIGH)  
	{  
		pulsewidth = this.waitforpin(echopin, LOW, 60000L); /* 60 ms timeout */  
		if (digitalRead(echopin) == LOW)  {  
			/* valid reading */
			return 0;
		} else {  
			/* no object detected (timeout) */
			return -1;
		}  
	} else {  
		/* sensor not firing */
		return -2;
	}
}


/*
* Convert the pulsewidth (us) in meters
* pulse duration is divided by two and converted in seconds
* speed of sound: 343.2 m/s
*/
double getdistance()
{
	double mus = pulsewidth/2*343.2;
	return mus/1000/1000;
}




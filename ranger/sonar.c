#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <signal.h>  
#include <string.h>  
#include <errno.h>  
#include <sys/time.h>  
#include <wiringPi.h>  
#define TRIGGER_PIN 9 
#define ECHO_PIN  11 
#define TIMEOUT 999 /* any value other than LOW or HIGH */ 
 
  
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
	int pulsewidth;
	/* trigger reading */  
	digitalWrite(TRIGGER_PIN, HIGH);  
	waitforpin(ECHO_PIN, TIMEOUT, 10); /* wait 10 microseconds */  
	digitalWrite(TRIGGER_PIN, LOW);  
	/* wait for reading to start */  
	waitforpin(ECHO_PIN, HIGH, 5000); /* 5 ms timeout */
	
	if (digitalRead(ECHO_PIN) == HIGH)  
	{  
		pulsewidth = waitforpin(ECHO_PIN, LOW, 60000L); /* 60 ms timeout */  
		if (digitalRead(ECHO_PIN) == LOW)  {  
			/* valid reading code */  
			/*printf("echo at %d micros\n", pulsewidth);*/
			return pulsewidth;
		} else {  
			/* no object detected code */  
			/*printf("echo timed out\n");  */
			return -1;
		}  
	} else {  
		/* sensor not firing code */  
		/*printf("sensor didn't fire\n");*/
		return -2;
	}
}

/*
* Convert the pulsewidth (us) in meters
* pulse duration is divided by two and converted in seconds
* speed of sound: 343.2 m/s
*/
double pwtometers(int pulsewidth)
{
	double mus = pulsewidth/2*343.2;
	return mus/1000/1000;
}

int main (int argc, char *argv[])  
{  
	int pulsewidth;  
	if (wiringPiSetupGpio () == -1)  
	{  
		fprintf (stderr, "Can't initialise wiringPi: %s\n", strerror (errno)) ;  
		return -1 ;  
	}  
	pinMode(TRIGGER_PIN, OUTPUT);  
	pinMode(ECHO_PIN, INPUT);
	  
	int i;
	for (i = 0; i < 10; i++)  
	{  
		pulsewidth = sonarread();
		if (pulsewidth > 0) {
			printf("Distance : %lf mt\n", pwtometers(pulsewidth));
		} else {
			printf("Error %d\n", pulsewidth);
		}
		
		
	}  
}  




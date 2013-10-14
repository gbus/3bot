#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <signal.h>  
#include <string.h>  
#include <errno.h>  
#include <sys/time.h>  
#include <wiringPi.h>  
#include "sonarlib.h"


int main (void)  
{  
	int trig = 9;
	int echo = 11;
	Sonar* son = new Sonar(trig, echo);
	int resp;
	int i;

	for (i = 0; i < 10; i++)  
	{
		resp = son->sonarread();
		if ( resp == 0) {
			printf("Distance : %lf mt\n", son->getdistance());
		} else {
			printf("Error %d\n", resp);
		}		
	}  
}  




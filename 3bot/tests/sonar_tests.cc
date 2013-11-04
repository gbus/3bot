#include "../src/sonarlib.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>


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




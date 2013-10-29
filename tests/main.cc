#include "../ranger/sonarlib.h"
#include "../i2c_pi_c/pwmlib.h"
#include "../servolib/servolib.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <time.h>

#define CHANNEL1 0
#define CHANNEL2 1
#define MIN	300
#define MAX	500
#define DEBUG	false
#define TRIG	9
#define	ECHO	11
#define	STEP	20

using namespace std;

int distance(Sonar*);

int main(void)
{
	int zero_pos_l, zero_pos_r;
        Servo s(DEBUG, CHANNEL1, MIN, MAX);
        Servo d(DEBUG, CHANNEL2, MIN, MAX);
        Sonar* snr = new Sonar(TRIG, ECHO);
        double dist_t1 = 0.0;
	double dist_t2 = 0.0;
	
        cout << "Left servo reset to value " << s.reset_position() << endl;
        cout << "Right servo reset to value " << d.reset_position() << endl;
        sleep(3);

	zero_pos = s.get_current_pos();
	
	for (int i==zero_pos; i<=MAX; i+=STEP) {
		cout << "pos: " << i << "\t";
		// Forward
		dist_t1 = distance(snr);
		sleep(1);
		dist_t2 = distance(snr);
		cout << dist_t1-dist_t2 << "\t";
		
		// Reverse
		dist_t1 = distance(snr);
		sleep(1);
		dist_t2 = distance(snr);
		cout << dist_t2-dist_t1 << "\t";	
	
	}
	
	s.reset_position();
	d.reset_position();
	exit(0);
}


double distance(Sonar* snr)
{
	int ret = 0;
	
	do {
		ret = snr->sonarread();
		
	} while ( ret != 0 );
	
	return snr->getdistance();
}

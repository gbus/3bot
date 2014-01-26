
#include "../src/hbridgelib.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>


// GPIO output pins
#define GPIO_M1_IN1		18
#define GPIO_M1_IN2		22
#define GPIO_M2_IN3		23
#define GPIO_M2_IN4		28

// Motor speed control (pwm)
#define PWM_CH_M1_ENA		12
#define PWM_CH_M2_ENB		13

using namespace std;

int main(void)
{
	cout << "Initialising. The test begins:" << endl;
	HBridge	hb(	GPIO_M1_IN1, GPIO_M1_IN2, GPIO_M2_IN1, GPIO_M2_IN2, 
			PWM_CH_M1_ENA, PWM_CH_M2_ENB );

        cout << "Progressively increase FW speed and break..." << endl;
	hb.setDirection(FW);
	for (int p = 10; p<=100; p=p+10) {
		cout << p << "% speed increase" << endl;
		hb.setSpeed(p);
		sleep(1);
	}
	hb.stopMotors();

        cout << "Progressively increase BW speed and let it slow down by itself..." << endl;
	hb.setDirection(BW);
	for (int p = 10; p<=100; p=p+10) {
		cout << p << "% speed decrease" << endl;
		hb.setSpeed(p);
		sleep(1);
	}
	hb.setFreespin();

	cout << "End of test" << endl;

}

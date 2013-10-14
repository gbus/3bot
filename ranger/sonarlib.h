#ifndef sonarlibH
#define sonarlibH

#include <wiringPi.h>

#define TIMEOUT 999 /* any value other than LOW or HIGH */ 



class Sonar
{
private:
	int trigger_pin
	int echo_pin

public:
        Sonar(int trigger_pin,int echo_pin);
        int waitforpin(int pin, int level, int timeout);
        int sonarread ();
        float pwtometers(int pulsewidth);
};
#endif

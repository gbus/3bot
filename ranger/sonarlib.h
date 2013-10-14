#ifndef sonarlibH
#define sonarlibH

#include <wiringPi.h>

#define TIMEOUT 999 /* any value other than LOW or HIGH */ 



class Sonar
{
private:
	int trigpin;
	int echopin;
	int pulsewidth;
protected:
        int waitforpin(int pin, int level, int timeout);
public:
        Sonar(int trigger_pin,int echo_pin);
        int sonarread ();
        double getdistance();
};
#endif

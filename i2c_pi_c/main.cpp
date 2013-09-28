 #include "pwmlib.h"
 #include <wiringPi.h>
 #include <wiringPiI2C.h>
 #include <iostream>
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <stdint.h>
 #include <errno.h>

 int main(void)
 {
         PWM* pwm = new PWM(0x40,true);
         pwm->setPWMFreq(60);
         pwm->setPWM(0,0,450);
         sleep(1);
         pwm->setPWM(0,0,350);
         sleep(1); 
         pwm->setPWM(0,0,400);
         sleep(1); 
         pwm->setPWM(1,0,450);
         sleep(1);
         pwm->setPWM(1,0,350);
         sleep(1); 
         pwm->setPWM(1,0,400);
         exit(1);
 }

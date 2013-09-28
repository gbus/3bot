#ifndef pwmlibH
#define pwmlibH

#include <wiringPi.h>
#include <wiringPiI2C.h>


        #define SUBADR1             0x02
        #define SUBADR2             0x03
        #define SUBADR3             0x04
        #define MODE1               0x00
        #define PRESCALE            0xFE
        #define LED0_ON_L           0x06
        #define LED0_ON_H           0x07
        #define LED0_OFF_L          0x08
        #define LED0_OFF_H          0x09
        #define ALLLED_ON_L         0xFA
        #define ALLLED_ON_H         0xFB
        #define ALLLED_OFF_L        0xFC
        #define ALLLED_OFF_H        0xFD

class PWM
{
private:
        int fd;
        int Address;
        bool Debug;
        float prescaleval;
        float prescale;

public:
        PWM(int address,bool debug);
        void setPWMFreq(int freq);
        void setPWM(int channel, int on, int off);
};
#endif

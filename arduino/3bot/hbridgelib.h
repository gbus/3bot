#ifndef hbridgelib_h
#define hbridgelib_h

#include "defines.h"

class DCMotor
{

  private:
    int _dir_pin_1;
    int _dir_pin_2;
    int _power_pin;
    int _dir;
  public:
    DCMotor(int pin1, int pin2, int pin3);
    void setDirection(bool d);
    void setPower(int power); // Set the motor power in the range: 0-100

    void off();
    void brake();

};
#endif

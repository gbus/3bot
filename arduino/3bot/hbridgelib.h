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
  protected:
    unsigned int _power;
  public:
    DCMotor(int pin1, int pin2, int pin3);
    void setDirection(bool d);
    void setPower(int power); // Set the motor power in the range: 0-100

    void off();
    void brake();

};

void encoder_isr();

class EncodedMotor:public DCMotor
{

  private:
    int _pulse_pin;
    int _intr;
    float _curr_speed;
    float _target_speed;
    unsigned long _prevtime;
  public:
    void updateSpeed();
    EncodedMotor(int pin1, int pin2, int pin3, int pin4, int intr);
    void setSpeed(float target);
    float getSpeed();

};

#endif

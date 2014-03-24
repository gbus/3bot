#include <hbridgelib.h>

#include "defines.h"


#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include <pins_arduino.h>
#endif

volatile unsigned long pulse_no;

/*
*
* DCMotor Class definitions
*
*/
DCMotor::DCMotor(int pin1, int pin2, int pin3)
{
  _dir_pin_1	= pin1;
  _dir_pin_2	= pin2;
  _power_pin	= pin3;
  _power	= 0;

  pinMode(_dir_pin_1, OUTPUT);
  pinMode(_dir_pin_2, OUTPUT);
  pinMode(_power_pin, OUTPUT);

  setDirection(FW);
  analogWrite(_power_pin, 0);
}


void DCMotor::setDirection(bool d)
{
	int status1, status2;
        if ( d ) {
		status1 = 1; status2 = 0;
        } else {
		status1 = 0; status2 = 1;
        }
        digitalWrite(_dir_pin_1, status1);       digitalWrite(_dir_pin_2, status2);

	#ifdef DEBUG_MOTORS
	    Serial.println("Pins ");
	    Serial.println(_dir_pin_1);
	    Serial.println(_dir_pin_2);
	    Serial.println("set to...");
	    Serial.println(status1);
	    Serial.println(status2);
	#endif
}

/// Give power to the motor
void DCMotor::setPower(int power)
{
	int throttle = map(abs(power),0,100,0,255);
	if (throttle > 255) throttle = 255;
	analogWrite( _power_pin, throttle);
	_power = power;

#ifdef DEBUG_MOTORS
	Serial.println("Power for motor ");
	Serial.println(_dir_pin_1);
	Serial.println(_dir_pin_2);
	Serial.println("set to...");
	Serial.println(throttle);
#endif
}



/// turn the motor off (free running)
void DCMotor::off()
{
  analogWrite( _power_pin, 0);
  digitalWrite(_dir_pin_1, 0);       digitalWrite(_dir_pin_2, 0);

#ifdef DEBUG_MOTORS
	Serial.println("Turned off motor ");
	Serial.println(_dir_pin_1);
	Serial.println(_dir_pin_2);
#endif
}


/// active motor brake
void DCMotor::brake()
{
  analogWrite( _power_pin, 255);
  digitalWrite(_dir_pin_1, 1);       digitalWrite(_dir_pin_2, 1);

#ifdef DEBUG_MOTORS
	Serial.println("Brake motor ");
	Serial.println(_dir_pin_1);
	Serial.println(_dir_pin_2);
#endif
}



/*
*
* EncodedMotor Class definitions
*
*/
EncodedMotor::EncodedMotor(int pin1, int pin2, int pin3, int pin4, int intr) : DCMotor(pin1,pin2,pin3)
{
  _pulse_pin	= pin4;
  _intr		= intr;
  _curr_speed	= 0;
  _prevtime	= millis();
  pinMode(_pulse_pin, INPUT);
  digitalWrite(_pulse_pin, HIGH);
  // Here attach the input pin interrupt to a ISR
  attachInterrupt(_intr, encoder_isr, CHANGE);
}

// to be run in the sketch loop and delayed MAIN_LOOP_DELAY milliseconds
// - Get the counter value and calculate the speed;
// - Compare the current speed vs target speed and adjust power.
void EncodedMotor::updateSpeed()
{
  unsigned long currtime = millis();
  unsigned long elapsed = _prevtime - currtime;

  //do speed calculation here...
  _curr_speed = (pulse_no/TICKS_PER_METER) / (elapsed/1000);
  // ...and reset timer and counter
  _prevtime = currtime;
  pulse_no = 0;


  // Compare the current speed with target speed.
  // If different increase/decrease power (setPower)
  unsigned int speeddiff = _target_speed - _curr_speed;
  unsigned int p_inc = 1;
  if (_curr_speed < _target_speed) {
	setPower(_power+p_inc);
  } else if (_curr_speed > _target_speed) {
	if (_power > 0)	setPower(_power-p_inc);
  }
}

void EncodedMotor::setSpeed(float target)
{
  _target_speed = target;
}

float EncodedMotor::getSpeed()
{
  return _curr_speed;
}

void encoder_isr() {
	pulse_no++;
}

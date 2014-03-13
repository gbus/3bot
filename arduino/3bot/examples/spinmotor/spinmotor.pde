#include <hbridgelib.h>
#include <defines.h>


#define DIRECTION_PIN_A 31
#define DIRECTION_PIN_B 32
#define PWM_PIN 2

DCMotor m1(DIRECTION_PIN_A, DIRECTION_PIN_B, PWM_PIN);

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  m1.setDirection(0);

  m1.setPower(30); // Start motor 1
  delay (2000);

  m1.setPower(60);
  delay (2000);

  m1.setPower(100);
  delay (2000);

  m1.off(); // free running
  delay (2000);

  m1.setPower(100); // Start motor 1
  delay (2000);

  m1.brake(); // Brake motor 1
  delay (2000);
}

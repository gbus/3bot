#include <hbridgelib.h>

DCMotor m1;

void setup()
{
  Serial.begin(115200);
  m1.begin();
}

void loop()
{
  m1.setDirection(0);

  m1.setSpeed(30); // Start motor 1
  delay (2000);

  m1.setSpeed(60);
  delay (2000);

  m1.setSpeed(100);
  delay (2000);

  m1.off(); // free running
  delay (2000);

  m1.setSpeed(100); // Start motor 1
  delay (2000);

  m1.brake(); // Brake motor 1
  delay (2000);
}

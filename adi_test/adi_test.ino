#include<SonarwServo.h>
SonarwServo servo_son;
void setup() {
  // put your setup code here, to run once:
Serial.begin (9600);
}

void loop() {
  // put your main code here, to run repeatedly:
servo_son.sonarwservo();
}

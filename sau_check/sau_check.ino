#include<velocity.h>
#include<posit.h>
#include<extreme_servo.h>
#include<sense_mot.h>
Velocity velo;
Sense_mot integ;
Posit place;
extreme_servo angular;
void setup() {
  // put your setup code here, to run once:
Serial.begin (9600);
}

void loop() {
  place.posit_pid();
  // put your main code here, to run repeatedly:
  // velo.vel_pid();
   //integ.inte();
//angular.extremes();
}

#include<velocity.h>
#include<posit.h>
#include<SonarwServo.h>
#include<FSRwLED.h>
#include<sense_mot.h>
#include<mrsdStepper.h>
#include<extreme_servo.h>


Velocity velo;
Posit place;
FSRwLED servo;
Sense_mot integ;
SonarwServo servo_son;
mrsdStepper step_motor;
extreme_servo angular;
void setup() {
  // put your setup code here, to run once:
Serial.begin (115200);
}
int state = 0;
void loop() {
  
  switch(state%7){
  case 0: {
    servo.fsrwLED();
    state++;
  }
  case 1: {
    servo_son.sonarwservo();
    state++;
   // digitalWrite(4, LOW); 
  }
  case 2: {
    
    place.posit_pid();
    state++;
    
  }
  case 3: {

    velo.vel_pid();
    state++;
    
    
  }
  case 4: {
    integ.inte();
    state++;
    //Serial.println("there");
    digitalWrite(7, LOW); 
    digitalWrite(8, LOW); 
  }
 case 5: {
    //Serial.println("here1");
    step_motor.stepperModeUser();
    state++;
    
  }
   case 6: {
    step_motor.stepperModePot();
    state++;  
  }

//  case 7: {
//    angular.extremes();
//    state++;  
//  }
  }
  // put your main code here, to run repeatedly:

}

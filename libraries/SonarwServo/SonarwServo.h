#ifndef SonarwServo_h
#define SonarwServo_h

#include "Arduino.h"
#include "Servo.h"

class SonarwServo
{
public:
SonarwServo();
const int Sonar_Pin = A2;
const int buttonPin = 12;
//Variables
long Sonar_Read, Sonar_Value;
int sum = 0; //Sum to Average
int avg = 15; //Sample size to Average
int servoangle_map = 0;//Mapping Sonar distance to servo angle
Servo servo1;
void sonarwservo();
private:
//Define Variables_Debounce
int buttonState;             //current reading from i/p
int lastButtonState = HIGH;   //previous reading from i/p
unsigned long lastDebounceTime = 0;  // last time o/p was toggled
unsigned long debounceDelay = 50;    // the debounce time
};
#endif
/*
  velocity.h - Library for Velocity PID.
  Created by Saurabh Nair, October 12, 2016.
*/
#ifndef sense_mot_h
#define sense_mot_h


#include <Arduino.h>

class Sense_mot
{
  public:
  Sense_mot();
  void inte();
private:
int j = 0;
volatile unsigned int encoder0Pos = 0;
double tmp_Pos = 0;
double temp = 0;
double pid_set = 0;
double ang_vel = 0;
int enable_pin = 11;
int pin_l1 = 7;  //pin l3 for now
int pin_l2 = 8;  //pin l4 for now
long time_int = 0;
double init_pos = 0;
double pid_in = 0, pid_out = 0;
unsigned int count = 0;
double error = 0;
double error_last = 0, error_d = 0, error_i = 0;
double pid_p = 5;
double pid_i = 0.01;
double pid_d = 0;
float distance = 0;

//Define Variables_Debounce
const int buttonPin = 12;
int buttonState;             //current reading from i/p
int lastButtonState = HIGH;   //previous reading from i/p
unsigned long lastDebounceTime = 0;  // last time o/p was toggled
unsigned long debounceDelay = 50;    // the debounce time

};
#endif


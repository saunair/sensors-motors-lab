/*
  velocity.h - Library for Velocity PID.
  Created by Saurabh Nair, October 12, 2016.
*/
#ifndef velocity_h
#define velocity_h


#include <Arduino.h>

class Velocity
{
  public:
  Velocity();
  void vel_pid();
private:
double tmp_Pos = 1;
double temp;
double pid_set = 0;
double ang_vel =0;
int enable_pin = 11;
int pin_l1 = 7;  //pin l3 for now
int pin_l2 = 8;  //pin l4 for now
boolean A_set;
boolean B_set;
long time_int = 0;
long init_pos = 0;
double pid_in= 0, pid_out= 0;
unsigned int count = 0;
double error = 0;
double error_last = 0, error_d = 0, error_i = 0;
double pid_p = 10;
double pid_i = 1.2;
double pid_d = 0.01;
int pin_e1 = 2;
int pin_e2 = 3;

//Define Variables_Debounce
const int buttonPin = 12;
int buttonState=HIGH;             //current reading from i/p
int lastButtonState = HIGH;   //previous reading from i/p
unsigned long lastDebounceTime = 0;  // last time o/p was toggled
unsigned long debounceDelay = 50;    // the debounce time

};

#endif

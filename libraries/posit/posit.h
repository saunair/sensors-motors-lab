/*
  posit.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef posit_h
#define posit_h

#define encoder0PinA 2
#define encoder0PinB 3

#include <Arduino.h>

class Posit
{
  public:
  Posit();
  void posit_pid();
private:
//Global vars
int enable_pin = 11;
int pin_l1 = 7;  //pin l3 for now
int pin_l2 = 8;  //pin l4 for now
int pin_e1 = 2;
int pin_e2 = 3;
const int irSense = A0;          // Connect sensor to analog pin A0
int distance = 0;
int sample = 0;
double temp = 0;
unsigned long i = 0, j = 0;
double error = 0;
double error_last = 0, error_d = 0, error_i = 0;
//PID vars
double pid_in = 0;    //encoder value
double pid_out = 0;   //PWM from 0-255
double pid_set = 0;   //encoder value from IR through mapping
int count = 0;
//double pid_p = 0.8;
//double pid_i = 0.07;
//double pid_d = 1.1;
//double pid_p = 0.65;
//double pid_i = 0.1;
//double pid_d = 2.1;
//double pid_p = 0.72;
//double pid_i = 0.09;
//double pid_d = 1.5;
double pid_p = 0.57;
double pid_i = 0.0802;
double pid_d = 2.6;

double new_pos_val;
long pos_val  = -999;
int loop_check = 0;


//Define Variables_Debounce
const int buttonPin = 12;
int buttonState;             //current reading from i/p
int lastButtonState = HIGH;   //previous reading from i/p
unsigned long lastDebounceTime = 0;  // last time o/p was toggled
unsigned long debounceDelay = 50;    // the debounce time  


};

#endif


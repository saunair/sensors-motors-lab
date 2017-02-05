#ifndef FSRwLED_h
#define FSRwLED_h

#include "Arduino.h"

class FSRwLED
{
public:
FSRwLED();
//Define constants for pins
const int buttonPin = 12;
const int led=5;
const int FSR=A0;
//Define Variables_FSRwLEDFunc
int FSR_Read=0;
unsigned long fsrResistance;
unsigned long fsrConductance; 
long fsrForce;
void fsrwLED();
private:
//Define Variables_Debounce
int buttonState;             //current reading from i/p
int lastButtonState = HIGH;   //previous reading from i/p
unsigned long lastDebounceTime = 0;  // last time o/p was toggled
unsigned long debounceDelay = 50;    // the debounce time
};
#endif
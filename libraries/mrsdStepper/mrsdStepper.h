#ifndef mrsdStepper_h
#define mrsdStepper_h

#include "Arduino.h"
class mrsdStepper
{
	public:
		mrsdStepper();
		void stepperModePot();
	   	void stepperModeUser();
	    int a = 0;
		const int potPin = A4;
		const int buttonPin = 12;
		const int en_step = 13;
		int potValue = 0;
		int sensorValue = 0;
		float sensorValue1 = 0;

	private:
//Define Variables_Debounce
int buttonState=LOW;             //current reading from i/p
int lastButtonState = HIGH;   //previous reading from i/p
unsigned long lastDebounceTime = 0;  // last time o/p was toggled
unsigned long debounceDelay = 50;    // the debounce time
int reading;
};		

#endif
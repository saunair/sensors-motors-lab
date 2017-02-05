#include<Arduino.h>

class extreme_servo {
 //initialize to pin
	
public:
	void extremes();
	extreme_servo();
private:
	//Define Variables_Debounce
const int buttonPin = 12;
int buttonState=HIGH;             //current reading from i/p
int lastButtonState = HIGH;   //previous reading from i/p
unsigned long lastDebounceTime = 0;  // last time o/p was toggled
unsigned long debounceDelay = 50;    // the debounce time

};
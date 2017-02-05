#include <Servo.h> //include servo library
#include<extreme_servo.h>

 
extreme_servo::extreme_servo() {
 //initialize to pin
}

void extreme_servo::extremes() { // Loop through motion tests

Servo servo1;
servo1.attach(4);//define servo
while(1) {

	int reading = digitalRead(buttonPin);//Read State Switch
//  Serial.println(reading);
  if (reading != lastButtonState) 
  {
  lastDebounceTime = millis();// reset the debouncing timer
 // Serial.println("Reset");
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the reading has been there longer than debounce delay, consider as 
    // if the button state has changed:
    if (reading != buttonState) {
     // Serial.println("Buttonpress");
      buttonState = reading;
      if (buttonState == LOW) {
      //  Serial.println("Break");
	   break;
      }
    }
  }
  lastButtonState = reading;

  Serial.write('A');
  Serial.write('e');
  Serial.write(0);
  Serial.write(0);
  Serial.write(0);
  Serial.write('\n');
  servo1.write(0);
  delay(1000); 
  servo1.write(180);
  delay(1000); 
  servo1.write(90);
  delay(500); 
} 
}

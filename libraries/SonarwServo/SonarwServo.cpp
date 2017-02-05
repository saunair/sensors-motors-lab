#include <Arduino.h>
#include <SonarwServo.h>


SonarwServo::SonarwServo()
{
   //initialize to pin
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
}

void SonarwServo::sonarwservo()
{
  int temp = 0;
 while(1)
  {
    servo1.attach(4);
  int reading = digitalRead(buttonPin);//Read State Switch
  //Serial.println(reading);
  if (reading != lastButtonState) 
  {
  lastDebounceTime = millis();// reset the debouncing timer
    }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the reading has been there longer than debounce delay, consider as 
    // if the button state has changed:
    if (reading != buttonState) {
    //  Serial.println("Buttonpress");
      buttonState = reading;
      if (buttonState == LOW) {
      //  Serial.println("Break");
	break;
      }
    }
  }
  lastButtonState = reading;
  for (int i = 0; i < avg ; i++)
  {
    
    Sonar_Read = analogRead(Sonar_Pin)/1.998;//Read analog value, divided by 2 to get in inches since the scale factor is(Vcc/512)per inch= ~9.8mV/in.
    sum += Sonar_Read;
    delay(5);
  }
  Sonar_Value = sum/avg;
  //Serial.print("MAXSonar_EZ:");
  //Serial.print(Sonar_Value);
  sum = 0;  //reset for next read
  servoangle_map = map(Sonar_Value, 5, 17, 180, 0);
  //servoangle_map = map(Sonar_Value, 5, 17, 180, 0);
  
  if(Sonar_Value < 5)
  {
      servoangle_map = 180;

  }
  if(Sonar_Value > 17) {
    servoangle_map = 0;
  }
  //Serial.print("Servo angle:" );
  //Serial.print(servoangle_map);
  servo1.write(servoangle_map);
  Serial.write('A');
  Serial.write('s');
  Serial.write(char(0));
  Serial.write(char(Sonar_Value));
  Serial.write(char(servoangle_map));
  Serial.write('\n');
  delay(45);
}
}
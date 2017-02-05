#include "Arduino.h"
#include <mrsdStepper.h>
#include "BasicStepperDriver.h"

#define MOTOR_STEPS 200
#define DIR 9
#define STEP 10
#define MICROSTEPS 1
#define RPM 120

BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);


mrsdStepper::mrsdStepper()
{
 pinMode(buttonPin, INPUT);
 pinMode(en_step, OUTPUT);
 digitalWrite(buttonPin, HIGH);
}

void mrsdStepper::stepperModePot()
{
	
	stepper.setRPM(RPM);
	stepper.setMicrostep(MICROSTEPS);
	while(1)
  { //String send_stepper_pot = String("A");
    	digitalWrite(en_step, LOW);
          Serial.write('A');
          Serial.write('i');
          Serial.write(char(0));
          Serial.write(char(sensorValue));
          Serial.write(char(sensorValue1));
          Serial.write('\n');

      int reading = digitalRead(buttonPin);//Read State Switch
  //Serial.println(reading);
  if (reading != lastButtonState) 
  {
  lastDebounceTime = millis();// reset the debouncing timer
  //Serial.println("Reset");
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the reading has been there longer than debounce delay, consider as 
    // if the button state has changed:
    if (reading != buttonState) {
      //Serial.println("Buttonpress");
      buttonState = reading;
      if (buttonState == LOW) {
       // Serial.println("Break");
	   digitalWrite(en_step, HIGH);
  break;
      }
  
    }
  }
lastButtonState = reading;

    sensorValue = analogRead(potPin);
    sensorValue1 = (int)((float)(sensorValue-potValue)/2.84);

    if ((sensorValue - potValue) > 0)
    {
      stepper.rotate(sensorValue1);
      sensorValue1=map(sensorValue1,0,360,0,255);
      //sensorValue=map(sensorValue,0,1023,0,255);
          Serial.write('A');
          Serial.write('i');
          Serial.write(char(0));
          Serial.write(char(sensorValue));
          Serial.write(char(sensorValue1));
          Serial.write('\n');

      //Serial.print("\t angle = ");
      //Serial.println(sensorValue1);
    }
      
    else if ((sensorValue - potValue) < 0)
    {
      stepper.rotate(sensorValue1);
      sensorValue1=map(sensorValue1,0,360,0,255);
      //sensorValue=map(sensorValue,0,1023,0,255);
          Serial.write('A');
          Serial.write('i');
          Serial.write(char(0));
          Serial.write(char(sensorValue));
          Serial.write(char(sensorValue1));
          Serial.write('\n');
      //Serial.print("\t angle = ");
      //Serial.println(sensorValue1);
    }

    potValue = sensorValue;
      
    delay(20);

      }
  
}

void mrsdStepper::stepperModeUser()
{

  unsigned long now = millis ();
   while (millis () - now < 1000)
   Serial.read ();  // read and discard any input
stepper.setRPM(RPM);
stepper.setMicrostep(MICROSTEPS);  
while(1)
  {
    Serial.write('A');
          Serial.write('k');
          Serial.write('0');
          Serial.write('0');
          Serial.write(char(a));
          Serial.write('\n');
        digitalWrite(en_step, LOW);
   // String send_stepper = String("A");
  int reading = digitalRead(buttonPin);//Read State Switch
  //Serial.println(reading);
  if (reading != lastButtonState) 
  {
  lastDebounceTime = millis();// reset the debouncing timer
  //Serial.println("Here");
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the reading has been there longer than debounce delay, consider as 
    // if the button state has changed:
    if (reading != buttonState) {
      //Serial.println("Buttonpress");
      buttonState = reading;
      if (buttonState == LOW) {
      //  Serial.println("Break");
	   digitalWrite(en_step, HIGH);
  break;
      }
    }
  }
  lastButtonState = reading;
   
    while (Serial.available()) 
    {
      a = Serial.parseInt();
    
      if (a >= -360 && a <= 360)
      {
          stepper.rotate(a);
          sensorValue1=map(a,-360,360,0,255);
          
          //Serial.print("A ");
          //if(!(millis()%100)) {
          Serial.write('A');
          Serial.write('k');
          Serial.write('0');
          Serial.write('0');
          Serial.write(char(a));
          Serial.write('\n');
          
      }
      
      delay(20);
    }

      }
	
}

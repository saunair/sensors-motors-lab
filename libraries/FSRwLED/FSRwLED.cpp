#include <Arduino.h>
#include <FSRwLED.h>

FSRwLED::FSRwLED()
{
 pinMode(led, OUTPUT); 
 pinMode(buttonPin, INPUT);
 digitalWrite(buttonPin, HIGH);
}

void FSRwLED::fsrwLED()
{
 while(1)
  {
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
     // Serial.println("Buttonpress");
      buttonState = reading;
      if (buttonState == LOW) {
      //  Serial.println("Break");
	break;
      }
    }
  }
  lastButtonState = reading;
  FSR_Read=analogRead(FSR);//Read and save analog FSR
  //Serial.print("Analog Reading:");
  //Serial.println(FSR_Read);
  FSR_Read=map(FSR_Read, 0, 1023, 0, 255);//Map for LED illuminations
  analogWrite(led,FSR_Read);
  FSR_Read=map(FSR_Read, 0, 255, 0, 5000);
  if (FSR_Read == 0) {
    //Serial.println("Force in Newtons= 0");
    fsrForce=FSR_Read;  
  } 
  else {
    //Vfsr = Vcc*R/(R+FSR) where R=10K and Vcc=5V so FSR=((Vcc-V)*R)/V
    fsrResistance = 5000 - FSR_Read;     // fsrVoltage is in millivolts so 5V = 5000mV
    fsrResistance *= 10000;                // 10K resistor
    fsrResistance /= FSR_Read;
    fsrConductance = 1000000;           //measure in micromhos 
    fsrConductance /= fsrResistance;
    if (fsrConductance <= 1000) {
      fsrForce = fsrConductance/80;
      //Serial.print("Force in Newtons: ");
      //Serial.println(fsrForce);      
    } 
    else {
      fsrForce = fsrConductance - 1000;
      fsrForce /= 30;
      //Serial.print("Force in Newtons: ");
      //Serial.println(fsrForce);            
    }
  }
  Serial.write('A');
  Serial.write('f');
  Serial.write(char(0));
  Serial.write(char(fsrForce));
  Serial.write(char(0));
  Serial.write('\n');
  delay(30);
  }
}
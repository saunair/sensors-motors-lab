#include <posit.h>
#include <Arduino.h>
#include <Encoder.h>

#define pin_e1 2
#define pin_e2 3
int count = 0;

Posit::Posit()
{
pinMode(enable_pin, OUTPUT);
  pinMode(pin_l1, OUTPUT);
  pinMode(pin_l2, OUTPUT);


  
}

void Posit::posit_pid() {
	Encoder enc_pos(pin_e1, pin_e2);


  digitalWrite(12, HIGH);
  //From IR to Encoder units through mapping for pid setpoint
  while(1){
  //Data to gui
  Serial.write('A');
  Serial.write('c');
  Serial.write(char(new_pos_val));
  Serial.write(char(0));
  Serial.write(char(pid_out));
  Serial.write('\n');
    delay(10);
int reading = digitalRead(buttonPin);//Read State Switch
  //Serial.println(reading);
  if (reading != lastButtonState) 
  {
  lastDebounceTime = millis();// reset the debouncing timer
 // Serial.println("Reset");
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the reading has been there longer than debounce delay, consider as 
    // if the button state has changed:
    if (reading != buttonState) {
      Serial.println("Buttonpress");
      buttonState = reading;
      if (buttonState == LOW) {
        Serial.println("Break");
  break;
      }
    }
  }
  lastButtonState = reading;

    if (Serial.available()) {
      temp = Serial.parseInt();
      if (temp > 179)
        temp = temp - 360;
      else if (temp < -180)
      	temp = 360 + temp;
      
      loop_check = 1;
      enc_pos.write(0);
      while (loop_check) {
        pid_set = temp;


       // Serial.print("setpoint (from IR) is ");
        Serial.println(pid_set);
  //delay(70);
        
delay(45);
new_pos_val = ((int(enc_pos.read())/2) %360 );


       // Serial.print("Position from encoder = ");
        Serial.println(new_pos_val);
        //PID stuff

        pid_in = new_pos_val;
        error = pid_set - pid_in;
        error_d = error - error_last;
        error_last = error;
       // Serial.print("Error = ");
        Serial.println(pid_set - pid_in);
        if ((error > 2) || (error < -2) && pid_set != 0) {
          count++;


          error_i = error_i + error;
          pid_out = pid_p * error + pid_i * error_i +  pid_d * error_d;


          if (pid_out > 0) {
            //   low on 2 and high on 1
            digitalWrite(pin_l1, HIGH);
            digitalWrite(pin_l2, LOW);
          } else {
            //   low on 1 and high on 2
            digitalWrite(pin_l1, LOW);
            digitalWrite(pin_l2, HIGH);
          }

          if (pid_out > 255)
            pid_out = 255;
          else if (pid_out < -255)
            pid_out = -255;


          analogWrite(enable_pin, abs(pid_out));
         // Serial.print("Val from PID (PWM) = ");
          Serial.println(pid_out);
        }
        else
        {
          analogWrite(enable_pin, 0);
          digitalWrite(pin_l1, HIGH);
          digitalWrite(pin_l2, HIGH);
          // pid_set = 0;
          error_i = 0;
          error_d = 0;
          error = 0;
          loop_check = 0;
          enc_pos.write(0);
        }

       
      }
    }
  }
}


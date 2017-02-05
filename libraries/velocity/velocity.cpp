//Code for deomonstrating velocity control of a DC motor(SPG30-60K) using PID

#include<velocity.h>
#include<Encoder.h>
#define pin_e1 2
#define pin_e2 3

Velocity::Velocity() {

  pinMode(pin_e1, INPUT); 
  pinMode(pin_e2, INPUT); 
 
}

void Velocity::vel_pid(){
  Encoder enc_pos2(pin_e1, pin_e2);
//Serial.println("ok");
//Check each second for change in position
while(1) {

  Serial.write('A');
  Serial.write('b');
  Serial.write(char(ang_vel));
  Serial.write(char(0));
  Serial.write(char(pid_out));
  Serial.write('\n');

int reading = digitalRead(buttonPin);//Read State Switch

  if (reading != lastButtonState) 
  {
  lastDebounceTime = millis();// reset the debouncing timer
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

if(Serial.available())
  {
   
    temp = Serial.parseInt();
    
  
     
  }

    error_i =0;
   pid_set = temp;    

  tmp_Pos = int(((enc_pos2.read()/2)%360));
    ang_vel = float(-1000*(tmp_Pos - init_pos) )/ ((millis() - time_int)*6 );
   

   time_int = millis();
    init_pos = tmp_Pos;

    if((ang_vel <72) && (ang_vel >-72))
      pid_in = ang_vel;
    error = pid_set - pid_in;
    
    if(error > 1)
    error_d = error - error_last;
    error_last = error;
 
    if(abs(error)>2){
      error_i = error_i + error;
      pid_out = pid_p*error + pid_i*error_i +  pid_d*error_d;

      if(pid_out<0) {
        //   low on 2 and high on 1
        digitalWrite(pin_l1, HIGH); 
        digitalWrite(pin_l2, LOW); 
      } else {
        //   low on 1 and high on 2
        digitalWrite(pin_l1, LOW); 
        digitalWrite(pin_l2, HIGH); 
      }

       if(pid_out > 255)
        pid_out = 255;
      else if(pid_out < -255)
        pid_out = -255; 
  
      analogWrite(enable_pin, abs(pid_out));
  } 
}
  }

   

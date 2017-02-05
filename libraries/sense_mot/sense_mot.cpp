
#include <SharpIR.h>
#include<Encoder.h>
#include<sense_mot.h>
#define pin_e1 2
#define pin_e2 3

SharpIR sensor(GP2Y0A21YK0F, A1);

Sense_mot::Sense_mot() {

  pinMode(pin_e1, INPUT); 
  pinMode(pin_e2, INPUT); 
 
}

Encoder enc_pos3(pin_e1, pin_e2);


void Sense_mot::inte() {
  int g = 0;
  //Check each second for change in position
while(1) {
    error_i = 0;
 Serial.write('A');
  Serial.write('a');
  Serial.write(char(ang_vel));
  Serial.write(char(distance));
  Serial.write(char(pid_out));
  Serial.write('\n');

count = 10;
g++;
int reading = digitalRead(buttonPin);//Read State Switch
 // Serial.println(reading);
  if (reading != lastButtonState) 
  {
  lastDebounceTime = millis();// reset the debouncing timer
 // Serial.println("Reset");
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the reading has been there longer than debounce delay, consider as 
    // if the button state has changed:
    if (reading != buttonState) {
    //  Serial.println("Buttonpress");
      buttonState = reading;
      if (buttonState == LOW) {
     //   Serial.println("Break");
	break;
      }
    }
  }
  lastButtonState = reading;

  // analogWrite(enable_pin, 100);
  if(count ==10) {
    distance = 0;
  for (j = 0; j < 5; j++) {
    float distance_current = sensor.getDistance();
    distance += distance_current;
  }
  distance /= (j);
  count = 0;
  }
  
  if(g ==100) {
    error_i = 0;
    g =0;
  }
  //distance = distance_current;
  //Serial.print("distance = ");
  //Serial.println(distance);


  temp = (float(84 - distance)/84);
  //Serial.print("temp = ");
  //Serial.println(temp);

  temp = temp*75;
  if (temp<0)
    temp=0;
  //Serial.print("temp2 = ");
  //Serial.println(temp);

  
  //error_d = 0;
  //delay(10);

  //count++;
  pid_set =  temp;

  
    tmp_Pos = (((enc_pos3.read())/2) %360 );
  
 
  
  //tmp_Pos = (((enc_pos3.read())/2) %360 );


  //Serial.print("pt = ");
  //Serial.println(tmp_Pos);
  //Serial.println(float(1000 * (tmp_Pos - init_pos)) / ((millis() - time_int) * 360));
  //ang_vel = float(-1000 * (tmp_Pos - init_pos)) / ((millis() - time_int)*360);
    ang_vel = float(-1000*(tmp_Pos - init_pos))/((millis() - time_int)*6);
  //Serial.print("ang_vel = ");
 //Serial.println(ang_vel);


  time_int = millis();
  init_pos = tmp_Pos;

  if ((ang_vel < 7.5) && (ang_vel > -7.5))
    pid_in = ang_vel;
  error = pid_set - pid_in;

  //if (error > 1)
  error_d = error - error_last;
  error_last = error;
 // Serial.print("pid_set = ");
 // Serial.println(pid_set);
//if(error < 0)
 // error = 0;

  //Serial.print("Error = ");
  //Serial.println(pid_set - pid_in);
  //Serial.print("pid_in = ");
  //Serial.println(pid_in);

  if (abs(error) > 10) {
    //error_i = error_i + error;
    pid_out = (pid_p * error + pid_i * error_i +  pid_d * error_d);

   // Serial.print("error_i = ");
   // Serial.println(error_i);

   // Serial.print("error_d = ");
   // Serial.println(error_d);

   //Serial.print("PID out = ");
   //Serial.println(pid_out);

    if (pid_out < 0) {
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
    else if (pid_out < 255)
      pid_out = -255;

    //analogWrite(enable_pin, 255);
    analogWrite(enable_pin, abs(pid_out));

 
   //Serial.print("Val from PID (PWM) = ");
   //Serial.println(pid_out);
  } 
 }
}
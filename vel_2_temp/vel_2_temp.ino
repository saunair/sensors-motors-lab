//Code for deomonstrating velocity control of a DC motor(SPG30-60K) using PID
#include "Arduino.h"
#include "velocity.h"
#define encoder0PinA 2
#define encoder0PinB 3

volatile unsigned int encoder0Pos = 0;
unsigned int tmp_Pos = 1;
unsigned int valx;
unsigned int valy;
unsigned int valz;
double temp;
double pid_set = 0;
double ang_vel;
int enable_pin = 11;
int pin_l1 = 7;  //pin l3 for now
int pin_l2 = 8;  //pin l4 for now
boolean A_set;
boolean B_set;
long time_int = 0;
long init_pos = 0;
double pid_in = 0, pid_out = 0;
unsigned int count = 0;
double error = 0;
double error_last = 0, error_d = 0, error_i = 0;
double pid_p = 80;
double pid_i = 15;
double pid_d = 45;


Velocity::Velocity()
{
}

void Velocity::vel_pid() {
 //setup values for velocity pwm 
  pinMode(encoder0PinA, INPUT); 
  pinMode(encoder0PinB, INPUT); 

  //encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);

// encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);
 
  Serial.begin (9600);
  while (1) {
    //Check each second for change in position

    if (Serial.available())
    {
      analogWrite(enable_pin, 100);
      temp = Serial.parseInt();
      temp = temp / 100;
      delay(10);
    }
    else
    {
      count++;
      pid_set = temp;
      tmp_Pos = encoder0Pos;
      Serial.print("pt = ");
      Serial.println(float(1000 * (tmp_Pos - init_pos)) / ((millis() - time_int) * 360));
      ang_vel = float(1000 * (tmp_Pos - init_pos)) / ((millis() - time_int) * 360);

      time_int = millis();
      init_pos = tmp_Pos;

      if ((ang_vel < 0.6) && (ang_vel > -0.6))
        pid_in = ang_vel;
      error = pid_set - pid_in;

      if (error > 0.01)
        error_d = error - error_last;
      error_last = error;
      Serial.print("pid_set = ");
      Serial.println(pid_set);


      Serial.print("Error = ");
      Serial.println(pid_set - pid_in);
      Serial.print("pid_in = ");
      Serial.println(pid_in);

      if (abs(error) > 0.02) {
        error_i = error_i + error;
        pid_out = pid_p * error + pid_i * error_i +  pid_d * error_d;

        Serial.print("error_i = ");
        Serial.println(error_i);

        Serial.print("error_d = ");
        Serial.println(error_d);

        Serial.print("PID out = ");
        Serial.println(pid_out);

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
        else if (pid_out < -255)
          pid_out = -255;


        analogWrite(enable_pin, abs(pid_out));
        Serial.print("Val from PID (PWM) = ");
        Serial.println(pid_out);

      
    }
  }

}
}
// Interrupt on A changing state
void doEncoderA() {

  // Low to High transition?
  if (digitalRead(encoder0PinA) == HIGH) {
    A_set = true;
    if (!B_set) {
      encoder0Pos = encoder0Pos + 1;

    }
  }

  // High-to-low transition?
  if (digitalRead(encoder0PinA) == LOW) {
    A_set = false;
  }
}

// Interrupt on B changing state
void doEncoderB() {

  // Low-to-high transition?
  if (digitalRead(encoder0PinB) == HIGH) {
    B_set = true;
    if (!A_set) {
      encoder0Pos = encoder0Pos - 1;
    }
  }

  // High-to-low transition?
  if (digitalRead(encoder0PinB) == LOW) {
    B_set = false;
  }
}







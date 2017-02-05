
#include <Encoder.h>

//Global vars
int enable_pin = 11;
int pin_l1 = 7;  //pin l3 for now
int pin_l2 = 8;  //pin l4 for now
int pin_e1 = 2;
int pin_e2 = 3;
const int irSense = A0;          // Connect sensor to analog pin A0
int distance = 0;
int sample = 0;
double temp = 0;
unsigned long i = 0, j = 0;
double error = 0;
double error_last = 0, error_d = 0, error_i = 0;
//PID vars
double pid_in = 0;    //encoder value
double pid_out = 0;   //PWM from 0-255
double pid_set = 0;   //encoder value from IR through mapping
int count = 0;
double pid_p = 0.65;
double pid_i = 0.07;
double pid_d = 2;

//double pid_p = 0.43;
//double pid_i = 0.11;
//double pid_d = 1.3;

double new_pos_val;
//Encoder vars
Encoder enc_pos(pin_e1, pin_e2);
long pos_val  = -999;
int loop_check = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  digitalWrite(12, HIGH);

}


void loop() {
  //From IR to Encoder units through mapping for pid setpoint

  if (Serial.available()) {
    temp = Serial.parseInt();
    if(temp > 179)
      temp = temp - 360;
    
    
    loop_check = 1;
    enc_pos.write(0);
    while (loop_check) {
      pid_set = temp;


      Serial.print("setpoint (from IR) is ");
      Serial.println(pid_set);
delay(8);
      new_pos_val = ((int(enc_pos.read())/2)%360);


      Serial.print("Position from encoder = ");
      Serial.println(new_pos_val);
      //PID stuff

      pid_in = new_pos_val;
      error = pid_set - pid_in;
      error_d = error - error_last;
      error_last = error;
      Serial.print("Error = ");
      Serial.println(pid_set - pid_in);
      if ((error > 5) || (error < -5) && pid_set != 0) {
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
        Serial.print("Val from PID (PWM) = ");
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


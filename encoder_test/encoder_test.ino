#include <PID_v1.h>
#include <Encoder.h>

//Global vars
  int enable_pin = 11;
  int pin_l1 = 7;  //pin l3 for now
  int pin_l2 = 8;  //pin l4 for now
  int pin_e1 = 2; 
  int pin_e2 = 4; 
  const int irSense = A0;          // Connect sensor to analog pin A0
  int distance = 0;
  int sample = 0;
  int temp = 0;
  unsigned long j=0;
  int count = 0;



//Encoder vars  
  Encoder enc_pos(pin_e1, pin_e2);
  long pos_val  = -999;



void setup() {
  // put your setup code here, to run once:
  pinMode(enable_pin, OUTPUT); 
  pinMode(pin_l1, OUTPUT); 
  pinMode(pin_l2, OUTPUT); 
  Serial.begin(9600); 

  
}

int i = 0;
int check = 0;

void loop() {
   // Serial.println("");

  // put your main code here, to run repeatedly:
//  digitalWrite(enable_pin, HIGH); 
  analogWrite(enable_pin, 90);

//   low on 1 and high on 2
  digitalWrite(pin_l1, HIGH); 
  digitalWrite(pin_l2, LOW); 
//  Serial.print("done"); 

    
 

  //Encoder stuff
   check++;
    double new_pos_val;
    new_pos_val = ((int(enc_pos.read()))%720)*float(360)/720;

 

    if(new_pos_val>350 && i==2 ) {
      i = 0;
      count++;
    }
      
      if(check%100 == 0)
      Serial.println(count);

    if(new_pos_val < 20)
      i = 2;
   // Serial.println(new_pos_val);
    
    }
    
    
   

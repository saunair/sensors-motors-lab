#include <SharpIR.h>
#define irSense A0     
#define model 20150

//Global vars
  int enable_pin = 11;
  int pin_l1 = 7;  //pin l3 for now
  int pin_l2 = 8;  //pin l4 for now
  int pin_e1 = 2; 
  int pin_e2 = 4; 
      // Connect sensor to analog pin A0
  int dist = 0;
  int sample = 0;
  unsigned long x;
  
  

SharpIR sharp(irSense, 25, 93, model);



void setup() {
  // put your setup code here, to run once:

  
  pinMode(enable_pin, OUTPUT); 
  pinMode(pin_l1, OUTPUT); 
  pinMode(pin_l2, OUTPUT); 
  Serial.begin(9600); 

  //initialize the variables we're linked to
  


}

void loop() {
  // put your main code here, to run repeatedly:
    x = irRead();
    Serial.print("setpoint (from IR) is ");
    Serial.println(x);
}

// Take multiple readings, and average them out to reduce false readings
int irRead() {


    dist = sharp.distance(); 
    return(dist);
  //}
  //return temp;// Return value
}

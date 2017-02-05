/* read a rotary encoder with interrupts
   Encoder hooked up with common to GROUND,
   encoder0PinA to pin 2, encoder0PinB to pin 4 (or pin 3 see below)
   it doesn't matter which encoder pin you use for A or B  

   uses Arduino pullups on A & B channel outputs
   turning on the pullups saves having to hook up resistors 
   to the A & B channel outputs 

*/ 

int enable_pin = 11;
  int pin_l1 = 7;  //pin l3 for now
  int pin_l2 = 8;  //pin l4 for now
  int pin_e1 = 2; 
  int pin_e2 = 4;

volatile long encoder0Pos = 1000;

void setup() { 
  pinMode(pin_e1, INPUT); 
  digitalWrite(pin_e1, HIGH);       // turn on pullup resistor
  pinMode(pin_e2, INPUT); 
  digitalWrite(pin_e2, HIGH);       // turn on pullup resistor
  attachInterrupt(0, doEncoder, RISING);  // encoder pin on interrupt 0 - pin 2
  Serial.begin (9600);
  Serial.println("start");                // a personal quirk
} 

void loop(){
   analogWrite(enable_pin, 130);
   digitalWrite(pin_l1, LOW); 
   digitalWrite(pin_l2, HIGH); 
   Serial.println (encoder0Pos, DEC);
// do some stuff here - the joy of interrupts is that they take care of themselves
}

void doEncoder() {
   
  if (digitalRead(pin_e1==1)) {
    if()
    encoder0Pos++;
  } else {
    encoder0Pos--;
  }  
}


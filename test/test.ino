enum PinAssignments {
  encoderPinA = 7,
  encoderPinB = 6,
  clearButton = 8
};

volatile unsigned int encoderPos = 0;
unsigned int lastReportedPos = 1;

int motor_pin = 2;
boolean A_set = false;
boolean B_set = false;


void setup() {

  pinMode(encoderPinA, INPUT); 
  pinMode(encoderPinB, INPUT); 
  pinMode(clearButton, INPUT);
  digitalWrite(encoderPinA, HIGH);  // turn on pullup resistor
  digitalWrite(encoderPinB, HIGH);  // turn on pullup resistor
  digitalWrite(clearButton, HIGH);

// encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
// encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);

  Serial.begin(9600);
}


void loop(){ 
  
  analogWrite(motor_pin, 100);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
  
  if (lastReportedPos != encoderPos) {
    Serial.print("Index:");
    Serial.print(encoderPos, DEC);
    Serial.println();
    lastReportedPos = encoderPos;
  }
  if (digitalRead(clearButton) == LOW)  {
    encoderPos = 0;
  }
}

// Interrupt on A changing state
void doEncoderA(){
  // Test transition
  A_set = digitalRead(encoderPinA) == HIGH;
  // and adjust counter + if A leads B
  encoderPos += (A_set != B_set) ? +1 : -1;
}

// Interrupt on B changing state
void doEncoderB(){
  // Test transition
  B_set = digitalRead(encoderPinB) == HIGH;
  // and adjust counter + if B follows A
  encoderPos += (A_set == B_set) ? +1 : -1;
}

int pin = 13;
void setup() {
Serial.begin(9600); 
pinMode(pin, INPUT);           // set pin to input
digitalWrite(pin, HIGH);  
}

void loop() {
  // put your main code here, to run repeatedly:
 // code = 0;
 //Serial.println(millis());
//Serial.print(" ");
 Serial.println(digitalRead(13));
}

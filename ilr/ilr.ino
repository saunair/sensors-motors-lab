void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}
int a; 
void loop() {
  // put your main code here, to run repeatedly:

a =   analogRead(A0);
Serial.println(a);

}

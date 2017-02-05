#include <posit.h>

Posit posit;
int code = 0;
void setup() {
 Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  code = 0;
  switch(code){
    case 0: {
      posit.posit_pid();
      break;
    }
//    case 1: {
//      posit::posit_pid();
//      break;
//    }
   }
}

/*
 * getDistance
 *
 * Example of using SharpIR library to calculate the distance beetween the sharp sensor and an obstacle
 *
 * Created by Giuseppe Masino, 15 June 2016
 * Author URL http://www.facebook.com/peppe.masino1
 *
 * This example and the SharpIR library are released under the license
 * CreativeCommons ShareAlike-Attribution
 *
 * -----------------------------------------------------------------------------------
 *
 * Things that you need:
 * - Arduino
 * - A Sharp IR Sensor
 *
 *
 * The circuit:
 * - Arduino 5V -> Sensor's pin 1 (Vcc)
 * - Arduino GND -> Sensor's pin 2 (GND)
 * - Arduino pin A0 -> Sensor's pin 3 (Output)
 * 
 *
 * See the Sharp sensor datasheet for the pin reference, the pin configuration is the same for all models.
 * There is the datasheet for the model GP2Y0A41SK0F:
 * 
 * http://www.robotstore.it/open2b/var/product-files/78.pdf
 *
 */

//import the library in the sketch
#include <SharpIR.h>

SharpIR sensor(GP2Y0A21YK0F, A0);


void setup()
{
  Serial.begin(9600); //Enable the serial comunication
}

void loop()
{
  int distance = sensor.getDistance(); //Calculate the distance in centimeters and store the value in a variable
  
  Serial.println(distance); //Print the value to the serial monitor
}

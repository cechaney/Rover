
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "Pilot.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(150);
  myMotor->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);

}

void loop() {
  // put your main code here, to run repeatedly:

}

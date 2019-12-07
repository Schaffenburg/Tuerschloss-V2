/*
  stepstick.cpp lib to control one stepper motor with stepstick Driver
  created by Jonas Giesecke July 2018
  released to wiki.schaffenburg.org
*/

#include "Arduino.h"
#include "stepstick.h"

void Stepstick::drivestepper(int time, bool direction){
  digitalWrite(stepper_direction,direction);
  digitalWrite(stepper_step,HIGH);
  delay(time);
  digitalWrite(stepper_step,LOW);
  delay(time);
}
void Stepstick::enablestepper(){
  digitalWrite(stepper_enable,enabled);
}
void Stepstick::disablestepper(){
    digitalWrite(stepper_enable,disabled);
}
void Stepstick::initstepper(){
  // Schrittmotor Treiber Ausgänge
  pinMode(stepper_enable, OUTPUT);
  pinMode(stepper_step, OUTPUT);
  pinMode(stepper_direction, OUTPUT);
}

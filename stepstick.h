/*
  stepstick.h  lib to control a stepstick stepper Driver
  createt by Jonas Giesecke July 2018
  released to wiki.schaffenburg.org
*/
#ifndef stepstick_h
#define stepstick_h

#include "Arduino.h"
#include "config.h"

//Config
// vorzugsweise in der config.h
/*
#define stepper_step        4  // D4
#define stepper_direction   3  // D3
#define stepper_enable      10 // D10
*/

#define enabled             LOW
#define disabled            HIGH

class Stepstick{
  public:
    void drivestepper(int time, bool direction);
    void enablestepper();
    void disablestepper();
    void initstepper();

  private:

};

#endif

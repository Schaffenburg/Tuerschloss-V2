/*
  spacedoor.h Doorcontrol schaffenburg e.V.
  created by Jonas Giesecke  July 2018
  released to wiki.schaffenburg.org
*/
#ifndef spacedoor_h
#define spacedoor_h

#include "Arduino.h"
#include "config.h"
#include "stepstick.h"
#include <FastLED.h>

class Spacedoor{
  public:
    void initdoor();
    void checkButton();
    int lock_door();
    int unlock_door();
    int readButton();
    int readRefPoti();
    void waitForButtonPress();
    void waitForButtonRelease();
    void getDoorStatus();
  //  int getstatus();
    void setLED(char color);

    int unlocked_pos;
    int middle_pos;
    int half_locked_pos;
    int locked_pos;

    int wiggle_unlocked;
    int wiggle_middle;
    int wiggle_half_locked;
    int wiggle_locked;

    //int Flags;
    int riegel_status;
    int blatt_status;


  private:

};


#endif

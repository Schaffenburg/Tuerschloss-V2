/*
  spacedoor.cpp Doorcontrol Schaffenburg e.V.
  created by Jonas Giesecke  July 2018
  released to wiki.schaffenburg.org
*/

#include "Arduino.h"
#include "spacedoor.h"
/*
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
*/
CRGB leds[number_leds];
Stepstick motor;

 //int tuer_status = 0xFF;

void Spacedoor::initdoor(){
  FastLED.addLeds<NEOPIXEL, led_data_pin >(leds, number_leds);

  // Eingänge mit Pullups
  pinMode(limitswitch_locked, INPUT_PULLUP);
  //pinMode(limitswitch_unlocked, INPUT_PULLUP);
  pinMode(door_hallsensor, INPUT_PULLUP);
  pinMode(userbutton, INPUT_PULLUP);

  //ANalogpin muss nicht init werden

  wiggle_unlocked     = 5;
  wiggle_middle       = 15;
  wiggle_half_locked  = 20;
  wiggle_locked       = 20;

  motor.initstepper();
  motor.disablestepper();
}

void Spacedoor::checkButton(){
  Spacedoor spdoor;
  if (digitalRead(userbutton) == LOW){
    Serial.println("button pressed");
    //spdoor.getDoorStatus();
    Serial.println(spdoor.blatt_status,HEX);
    if(blatt_status== blatt_offen){
      //leds[0] = CRGB::Blue;
      //FastLED.show();
      spdoor.setLED('b');
      Serial.println("LED");
      while(blatt_status == blatt_offen){}//warte bis blatt geschlossen
      delay(500);// dann 2sec warten
      spdoor.lock_door();// verschliesse riegel
      // LED rot
    }
    if(blatt_status==blatt_zu){
      //LED
      //entriegle
      //LEd grün
    }

     //Serial.println(door.riegel_status,HEX)
  }
}

int Spacedoor::readButton(){
  return digitalRead(userbutton);
}

int Spacedoor::readRefPoti(){
  return analogRead(door_poti);
}

void Spacedoor::waitForButtonPress(){  // warten bis der Taster gedrückt wird
  while (digitalRead(userbutton) == HIGH) {}
}

void Spacedoor::waitForButtonRelease(){   //warten bis der Taster losgelassen wird
  while (digitalRead(userbutton) == LOW) {}
}

void Spacedoor::getDoorStatus(){
  // Türblatt
  blatt_status =  digitalRead(door_hallsensor);

  // Riegel
  if((analogRead(door_poti) > (unlocked_pos - (wiggle_unlocked*1)))&&(analogRead(door_poti) < (unlocked_pos + (wiggle_unlocked*1)))){
    riegel_status = falle_offen;
  }

  if((analogRead(door_poti) > (middle_pos - (wiggle_middle*2)))&&(analogRead(door_poti) < (middle_pos + (wiggle_middle*2)))){
    riegel_status = riegel_offen;
  }
                      //826 > 680-20    &&  400 <260+20
  if((analogRead(door_poti) < (half_locked_pos + wiggle_half_locked))&&(analogRead(door_poti) > (locked_pos - wiggle_locked))){
    riegel_status = riegel_geschlossen;
  }

}

void Spacedoor::setLED(char color){
  switch (color){
    case '0':
      leds[0] = CRGB::Black;
      break;
    case 'r':
      leds[0] = CRGB::Red;
      break;
    case 'g':
      leds[0] = CRGB::Green;
      break;
    case 'b':
      leds[0] = CRGB::Blue;
      break;
  }
  FastLED.show();
}

int Spacedoor::lock_door(){

  if(digitalRead(door_hallsensor) == blatt_zu){
    motor.enablestepper();
    leds[0] = CRGB::Blue;
    FastLED.show();

    while (!((analogRead(door_poti) < (locked_pos + wiggle_locked))&&(analogRead(door_poti) > (locked_pos - wiggle_locked)))) {   //todo fenster einbauen
      motor.drivestepper(1,dir_lock);
    }

    leds[0] = CRGB::Red;
    FastLED.show();

    delay(5000);

    leds[0] = CRGB::Black;
    FastLED.show();
    motor.disablestepper();
    return 1;
  }else{
    return 0;
  }
}

int Spacedoor::unlock_door(){
  motor.enablestepper();
  leds[0] = CRGB::Blue;
  FastLED.show();
  while (!((analogRead(door_poti) < (unlocked_pos + wiggle_unlocked))&&(analogRead(door_poti) > (unlocked_pos - wiggle_unlocked)))) {   //todo fenster einbauen
    motor.drivestepper(1,dir_unlock);
  }

  leds[0] = CRGB::Green;
  FastLED.show();

  delay(5000);

  leds[0] = CRGB::Red;
  FastLED.show();

  while (!((analogRead(door_poti) < (middle_pos + wiggle_middle))&&(analogRead(door_poti) > (middle_pos - wiggle_middle)))) {   //todo fenster einbauen
    motor.drivestepper(1,dir_lock);
  }
  leds[0] = CRGB::Black;
  FastLED.show();
  motor.disablestepper();
  return 1;
}

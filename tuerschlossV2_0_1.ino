#include <Arduino.h>
/* Türschloß V2
 *  by elektronik133| Jonas Giesecke
 * on 15.4.2018
 * for Schaffenburg e.V.
 * https://wiki.schaffenburg.org/Projekt:TuerschlossV2
 */

#include "config.h"
#include <EEPROM.h>
//#include "stepstick.h"
#include "spacedoor.h"
//#include "spacedoor.cpp"

Spacedoor door;

int incomingByteArray[30];
int bytecounter = 0;
byte data_received[30];

int lock_timer = 0;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

uint8_t eestart_h     = 1;
uint8_t eestart_l     = 2;
uint8_t eemiddle_h    = 3;
uint8_t eemiddle_l    = 4;
uint8_t eehalfstop_h  = 5;
uint8_t eehalfstop_l  = 6;
uint8_t eestop_h      = 7;
uint8_t eestop_l      = 8;


void setup()
{
  Serial.begin(9600);
  door.initdoor();
  if (door.readButton() == LOW){
    calibrate();
  }
  inputString.reserve(30);  // reserve 30 bytes for the inputString:

// Kalibrier werte aus eeprom laden
  door.unlocked_pos = (EEPROM.read(eestart_h))<<8;
  door.unlocked_pos |= (EEPROM.read(eestart_l));
  door.middle_pos = (EEPROM.read(eemiddle_h))<<8;
  door.middle_pos |= (EEPROM.read(eemiddle_l));
  door.half_locked_pos = (EEPROM.read(eehalfstop_h))<<8;
  door.half_locked_pos |= (EEPROM.read(eehalfstop_l));
  door.locked_pos   = (EEPROM.read(eestop_h))<<8;
  door.locked_pos |= (EEPROM.read(eestop_l));

  Serial.println("Arduino Tuer Steuerung V0.1");
}

void loop()
{
  serialEvent(); //call the function
  door.getDoorStatus();
  door.checkButton();
//  test_fct();

  delay(10);
}


void test_fct(){
  static int testcounter = 0;
  door.lock_door();
  delay(1000);
  door.unlock_door();
  delay(1000);
  testcounter ++;
  Serial.println(testcounter);
}



void decode_comand(){
  if(inputString == "lock"){
        Serial.println(door.lock_door(),HEX);
  }
  if (inputString == "unlock")  {
        Serial.println(door.unlock_door(),HEX);
  }
  if(inputString == "info"){
    Serial.println("Arduino Tuer Steuerung");
  }
  if(inputString == "version"){
    Serial.println("Arduino Tuer Steuerung V0.1");
  }
  if(inputString == "status"){
    door.getDoorStatus();
    Serial.println(door.blatt_status,HEX);
    Serial.println(door.riegel_status,HEX);

    //Debug:
    Serial.println(analogRead(door_poti),DEC);
    Serial.println(door.unlocked_pos,DEC);
    Serial.println(door.middle_pos,DEC);
    Serial.println(door.half_locked_pos,DEC);
    Serial.println(door.locked_pos,DEC);

  }
}

void serialEvent() {

  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    //Serial.print(inChar);
    // add it to the inputString:

    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
  //    leds[0] = CRGB::Black;
  //    FastLED.show();
    }else{
        inputString += inChar;
    }
  }
  if (stringComplete) {
    //door.getstatus();
    decode_comand();
    inputString = "";
    stringComplete = false;
  }
}

void calibrate(){
  int val  = 0;
  door.setLED('b');
  Serial.println("konfiguration gestartet");
  //wait til the button is released
  door.waitForButtonRelease();

  // Unlock_pos einspeichern
  Serial.println("Knauf gegen den Uhrzeigersinn drehen, bis Türfalle geöffnet. Dann Taster drücken.");
  door.setLED('r');
  delay(100);

  while (door.readButton() == HIGH) {
    val = door.readRefPoti();    //einlesen der Start Position
  }
  Serial.print("wert fuer --unlocked_pos-- ist: ");
  Serial.println(val,DEC);
  EEPROM.update(eestart_h, val>>8); //Abspeichern im EEPROM
  EEPROM.update(eestart_l, val);
  delay(50);
  door.waitForButtonRelease();

  //middle_pos einspeichern
  Serial.println("Knauf im Uhrzeigersinn drehen, bis zur 12 Uhr stellung. Dann Taster drücken.");
  door.setLED('r');
  delay(100);

  while (door.readButton() == HIGH) {
    val = door.readRefPoti();    //einlesen der  Position
  }
  Serial.print("wert fuer --middle_pos-- ist: ");
  Serial.println(val,DEC);
  EEPROM.update(eemiddle_h, val>>8); //Abspeichern im EEPROM
  EEPROM.update(eemiddle_l, val);
  delay(50);
  door.waitForButtonRelease();

  //half_locked_pos einspeichern
  Serial.println("Knauf im Uhrzeigersinn drehen, bis zur naechsten 12 Uhr Stellung. Dann Taster drücken.");
  door.setLED('r');
  delay(100);

  while (door.readButton() == HIGH) {
    val = door.readRefPoti();    //einlesen der  Position
  }
  Serial.print("wert fuer --half_locked_pos-- ist: ");
  Serial.println(val,DEC);
  EEPROM.update(eehalfstop_h, val>>8); //Abspeichern im EEPROM
  EEPROM.update(eehalfstop_l, val);
  delay(50);
  door.waitForButtonRelease();

  //locked_pos einspeichern
  Serial.println("Knauf im Uhrzeigersinn drehen, bis zur naechsten 12 Uhr stellung. Dann Taster drücken.");
  door.setLED('r');
  delay(100);

  while (door.readButton() == HIGH) {
    val = door.readRefPoti();    //einlesen der  Position
  }
  Serial.print("wert fuer --locked_pos-- ist: ");
  Serial.println(val,DEC);
  EEPROM.update(eestop_h, val>>8); //Abspeichern im EEPROM
  EEPROM.update(eestop_l, val);
  delay(50);

  door.setLED('b');
  Serial.println("Kalibrierung abgeschlossen");
  delay(1000);
  door.setLED('0');
}

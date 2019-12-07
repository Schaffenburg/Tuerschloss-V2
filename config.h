#ifndef config_h
#define config_h

#define stepper_step          4   // D4
#define stepper_direction     3   // D3
#define stepper_enable        10  // D10

#define led_data_pin          14  // A0
#define number_leds           1

#define limitswitch_locked    17  // A3
#define limitswitch_unlocked  16  // A2
#define door_hallsensor       18  // A4
#define userbutton            19  // A5

#define door_poti             2   //Analog pin 2

#define steps_max_lock        1600
#define steps_max_unlock      1600
#define steps_reopen          200
#define dir_unlock            HIGH
#define dir_lock              LOW
#define enabled               LOW
#define disabled              HIGH

#define time_stepper 1

#define lockwaittime          5000

/*Mögliche Zustände:
1. Blatt offen, Verriegelt
2. Blatt offen, entriegelt
3. Blatt offen, unbekannt(Schlüssel wurde manuell bewegt)
4. Blatt geschlossen, Verriegelt
5. Blatt geschlossen, entriegelt
6. Blatt geschlossen, unbekannt(Schlüssel wurde manuell bewegt)
*/
/*
#define tuer_status_closed    0x00  //"door closed"
#define tuer_status_open      0x01  //"door open"
#define tuer_status_locked    0x02
#define tuer_status_unlocked  0x03
#define limit_unlock_not      0xF1
#define limit_lock_not        0xF2
#define door_closed_not       0xF3
*/

#define blatt_zu            0x00
#define blatt_offen         0x01

#define falle_offen         0x01
#define riegel_offen        0x02
#define riegel_geschlossen  0x03


/*Aktionen:
1. Blatt zu, verriegelt, soll von innen entriegelt werden                 --> unlock über taster 2
2. Blatt zu, entriegelt, soll von innen verriegelt werden                 --> lock über taster 1
3. Blatt zu, verriegelt, soll von außen entriegelt werden                 --> unlock über serial comand
4. Blatt offen, verriegelt, soll von innen entriegelt werden              --> unlock über taster 2
5. Blatt offen, entriegelt, soll geschlossen und auto verriegelt werden   --> taster 1 & wenn blatt geschlossen + 5sec + lock

1. Blatt zu, 'locked' aktiv                     OK
2. Blatt zu, kein taster aktiv                  unbekannt
3. Blatt zu, 'locked' und 'unlocked' aktiv      Störung
4. Blatt offen, 'unlocked' aktiv                OK
5. Blatt offen, 'locked' aktiv                  OK
6. Blatt offen, kein taster aktiv               unbekannt
7. Blatt offen, 'locked' und 'unlocked' aktiv   Störung


wenn blatt geöffnet wir ist zwangsläufig entriegelt
2 hallsensoren + magnet in der riehmenscheibe um schließbewegung von außen zu erkennen

10turn Poti:
https://www.elfa.se/en/wirewound-potentiometer-kohm-soldering-lugs-bi-technologies-7286-r1k-25/p/16484737






*/





#endif

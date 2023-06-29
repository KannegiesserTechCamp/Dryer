/*
  _  __                                         _                                      _____                 _                ____                             
 | |/ /   __ _   _ __    _ __     ___    __ _  (_)   ___   ___   ___    ___   _ __    |_   _|   ___    ___  | |__            / ___|   __ _   _ __ ___    _ __  
 | ' /   / _` | | '_ \  | '_ \   / _ \  / _` | | |  / _ \ / __| / __|  / _ \ | '__|     | |    / _ \  / __| | '_ \   _____  | |      / _` | | '_ ` _ \  | '_ \ 
 | . \  | (_| | | | | | | | | | |  __/ | (_| | | | |  __/ \__ \ \__ \ |  __/ | |        | |   |  __/ | (__  | | | | |_____| | |___  | (_| | | | | | | | | |_) |
 |_|\_\  \__,_| |_| |_| |_| |_|  \___|  \__, | |_|  \___| |___/ |___/  \___| |_|        |_|    \___|  \___| |_| |_|          \____|  \__,_| |_| |_| |_| | .__/ 
                                        |___/                                                                                                           |_|    

###############################################################################################################################################################

Includes: Schaue dir die Dateien "LED.h", "Motor.h" und "Zeit.h" an, indem du mit <STRG + Mausklick> darauf klickst.
Du siehst die sogenannten Header-Dateien, sie zeigen dir die zur Verfügung stehenden Funktionen, Variablen und Farben.
Ändere nichts in den Dateien, nur in dieser "main.cpp".

- <Arduino.h>: 
  - Bei der Arduino.h handelt es sich um eine Standard-Bibliothek, du brauchst darin nicht weiter schauen.
  - Die Bibliothek ist projektübergreifend verfügbar, deshalb ist der Name hinter dem #include-Befehl in <> eingebettet. 

- "LED.h":
  - Die LED.h stellt dir Funktionen, Variablen und Farben für die Ansteuerung des RGB-LED-Streifens bereit. 
  - Der Quellcode liegt innerhalb dieses Projekts, deshalb ist der Name hinter dem #include-Befehl in "" eingebettet.

- "Motor.h":
  - Die Motor.h stellt dir Funktionen für die Ansteuerung des Trommel-Motors bereit.

- "Zeit.h"
  - Die Zeit.h stellt dir Funktionen zum Warten im Programmcode bereit. 
*/

#include <Arduino.h>
#include "LED.h"
#include "Motor.h"
#include "Zeit.h"

/*
############################################################################################################################################################### 
Variablen: Hier kannst du deine globalen Variablen definieren.

Beispiele:
  uint32_t Wartezeit = 3;         // Sekunden
  uint8_t Helligkeit = 50;        // %
  uint8_t Geschwindigkeit = 75;   // %
*/ 






/*
############################################################################################################################################################### 

Setup: Dieser Code wird einmalig zum Start des Controllers ausgeführt. Die beiden Funktionen zur Initialisierung müssen hier als erstes ausgeführt werden.
Loop: Dieser Code wird kontinuierlich in einer Schleife durchlaufen. Hier kannst du den sich wiederholenden Ablauf für deinen Trockner programmieren.

Beispiele für Funktionsaufrufe:
  LedLeisteFarbeHelligkeit(blau, Helligkeit);
  MotorGeschwindigkeit(Geschwindigkeit);
  MotorDrehenRechts();
  WarteSekunden(Wartezeit);
  MotorStopp();

Nutze zusätzlich dein Wissen über If-Anweisungen und Schleifen in der loop().
Du kannst die Trommel des Trockners langsam anlaufen und bremsen lassen, LEDs in unterschiedlichen Farben und Helligkeiten blinken lassen - Probier es aus!
*/

void setup() 
{
  // Die beiden Funktionen müssen hier an erster Stelle stehen bleiben.
  MotorInitialisierung();
  LedInitialisierung();
  


}

void loop() 
{





}
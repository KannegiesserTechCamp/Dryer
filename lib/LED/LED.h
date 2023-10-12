#ifndef LED_H
#define LED_H

/*  
Variablen
    - Du kannst die Anzahl der verfügbaren LEDs nutzen, z.B. für Schleifen. 
    - Denk daran, dass von 0 bis AnzahlLeds - 1 gezählt wird. Die erste LED trägt den Index 0.
*/
const uint8_t AnzahlLeds = 7;

/* 
############################################################################################################################################################### 
Diese vordefinierten Farben stehen dir (neben den RGB-Werten) zur Verfügung:
    -Bei einer Enumeration (enum) handelt es sich um einen Aufzählungstyp. Du kannst "Farbe" wie einen Datentyp behandeln. 
    -Beispiel:      LedEinzelFarbeHelligkeit(0, blau, 100);
*/
enum Farbe
{
    schwarz, weiss, rot, orange, gruen, blau, gelb, cyan, magenta
};

/*
############################################################################################################################################################### 
Hier findest du Funktionen, die dir für die Ansteuerung des RGB-LED-Streifens zur Verfügung stehen.
*/

/*  LedInitialisierung:
        - Diese Funktion muss einmalig im Setup-Teil der Main() aufgerufen werden.
        - Initialisiert den RGB Led-Streifen.
*/
void LedInitialisierung();


/*  LedEinzelFarbeHelligkeit:
        - Durch den Aufruf dieser Funktion kannst du eine einzelne LED ansteuern.
        - Bei dem Aufruf musst du drei Funktionparameter übergeben: 
            - Die Nummer der LED, beginnend bei 0.
            - Eine vordefinierte Farbe der LED - Schaue dir das Enum "Farbe" an.
            - Die Helligkeit der LED, zwischen 0 und 100 (%).
        - Die LED bleibt nach Ansteuerung einer anderen LED weiter in Betrieb.
        - Zum Zurücksetzen der LED hat man folgende Möglichkeiten:
            - Steuere die LED mit der Farbe "schwarz" an.
            - Steuere die LED mit der Helligkeit 0 an.
            - Nutze die Funktion "LedLeisteLoeschen()", um alle LEDs zurückzusetzen. 
*/
void LedEinzelFarbeHelligkeit(uint8_t LedNummer, Farbe Farbe, uint8_t Helligkeit);


/*  LedEinzelRGB:
        - Durch den Aufruf dieser Funktion kannst du eine einzelne LED ansteuern.
        - Bei dem Aufruf musst du vier Funktionparameter übergeben: 
            - Die Nummer der LED, beginnend bei 0.
            - Den Anteil der Farbe rot, zwischen 0 und 255.
            - Den Anteil der Farbe gruen, zwischen 0 und 255.
            - Den Anteil der Farbe blau, zwischen 0 und 255.
        - Die LED bleibt nach Ansteuerung einer anderen LED weiter in Betrieb.
        - Zum Zurücksetzen der LED hat man folgende Möglichkeiten:
            - Steuere die LED mit dem RGB-Wert (0, 0, 0) an
            - Nutze die Funktion "LedLeisteLoeschen()", um alle LEDs zurückzusetzen. 
*/
void LedEinzelRGB(uint8_t LedNummer, uint8_t Rot, uint8_t Gruen, uint8_t Blau);


/*  LedLeisteFarbeHelligkeit:
        - Durch den Aufruf dieser Funktion kannst du die gesamte LED-Leiste ansteuern.
        - Bei dem Aufruf musst du zwei Funktionparameter übergeben: 
            - Eine vordefinierte Farbe der LED - Schaue dir das Enum "Farbe" an.
            - Die Helligkeit der LED, zwischen 0 und 100 (%).
        - Die bisherigen LEDs bleiben nach Ansteuerung einer weiteren LED weiter in Betrieb.
        - Zum Zurücksetzen der LEDs hat man folgende Möglichkeiten:
            - Steuere die LED-Leiste mit der Farbe "schwarz" an.
            - Steuere die LED-Leiste mit der Helligkeit 0 an.
            - Nutze die Funktion "LedLeisteLoeschen()", um alle LEDs zurückzusetzen. 
*/
void LedLeisteFarbeHelligkeit(Farbe Farbe, uint8_t Helligkeit);


/*  LedLeisteRGB
        - Durch den Aufruf dieser Funktion kannst du die gesamte LED-Leiste ansteuern.
        - Bei dem Aufruf musst du drei Funktionparameter übergeben: 
            - Den Anteil der Farbe rot, zwischen 0 und 255.
            - Den Anteil der Farbe gruen, zwischen 0 und 255.
            - Den Anteil der Farbe blau, zwischen 0 und 255.
        - Die bisherigen LEDs bleiben nach Ansteuerung einer weiteren LED weiter in Betrieb.
        - Zum Zurücksetzen der LEDs hat man folgende Möglichkeiten:
            - Steuere die LED-Leiste mit dem RGB-Wert (0, 0, 0) an
            - Nutze die Funktion "LedLeisteLoeschen()", um alle LEDs zurückzusetzen. 
*/
void LedLeisteRGB(uint8_t Rot, uint8_t Gruen, uint8_t Blau);


/*  LedLeisteEin
        - Schaltet die LED-Leiste mit der letzten Einstellung ein.
*/
void LedLeisteEin();


/* LedLeisteAus
        - Schaltet die LED-Leiste aus, die letzten Einstellungen bleiben erhalten.
*/
void LedLeisteAus();


/* LedLeisteLoeschen
        - Schaltet die LED-Leiste aus und loescht die letzten Einstellungen.
*/
void LedLeisteLoeschen();

# endif
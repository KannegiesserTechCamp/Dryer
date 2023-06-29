#ifndef MOTOR_H
#define MOTOR_H

// Hier findest du Funktionen, die dir für die Ansteuerung des Trommel-Motors zur Verfügung stehen.

/*  MotorInitialisierung:
        - Diese Funktion muss einmalig im Setup-Teil der Main() aufgerufen werden.
        - Initialisiert den Motor.
*/
void MotorInitialisierung();


/*  MotorDrehrichtungFalsch:
        - Führe diese Funktion einmal im Setup-Teil der Main() aus, sollte der Motor falsch herum drehen.
*/
void MotorDrehrichtungFalsch();


/*  MotorGeschwindikeit:
        - Durch den Aufruf dieser Funktion kannst du die Geschwindigkeit des Motors vorgeben.
        - Bei dem Aufruf musst du einen Funktionparameter übergeben: Die gewünschte Geschwindigkeit
        - Die Funktion akzeptiert einen Wert vom Datentyp "uint8_t". Das heisst, dass du theoretisch Werte zwischen 0 und 255 übergeben kannst.
        - Hier wird die Geschwindigkeit in % angegeben, deshalb sind nur Werte zwischen 0 und 100 sinnvoll.
        - Die Geschwindigkeit gilt für beide Richtungen. Ändere sie rechtzeitig, wenn der Motor in der anderen Richtung langsamer oder schneller drehen soll. 
        - Durch den Aufruf dieser Funktion kann die Geschwindigkeit im laufenden Betrieb des Motors angepasst werden.

    Mit dieser Funktion kannst du auch ein sanftes anlaufen und abbremsen der Trommel erreichen!
    Überlege dir, wie du das mithilfe von Schleifen und Verzögerungszeiten erreichen kannst.
*/
void MotorGeschwindigkeit(uint8_t Geschwindigkeit);


/*  MotorDrehenRechts:
        - Durch den Aufruf dieser Funktion kannst du den Motor im Uhrzeigersinn drehen lassen.
        - Der Motor dreht mit der in "MotorGeschwindigkeit()" vorgegebenen Geschwindigkeit. 
*/
void MotorDrehenRechts();


/*  MotorDrehenLinks:
        - Durch den Aufruf dieser Funktion kannst du den Motor gegen den Uhrzeigersinn drehen lassen.
        - Der Motor dreht mit der in "MotorGeschwindigkeit()" vorgegebenen Geschwindigkeit. 
*/
void MotorDrehenLinks();


/*  MotorStopp:
        - Stoppt den Motor aus beiden Drehrichtungen.
        - Die Geschwindigkeitsvorgabe wird dabei nicht zurückgesetzt.
*/
void MotorStopp();

# endif
#ifndef ZEIT_H
#define ZEIT_H

//Hier findest du Funktionen, um an einer Stelle im Programmcode zu warten.

/*  WarteSekunden:
        - Wartet x Sekunden an dieser Stelle im Programm.
        - Bei dem Aufruf musst du einen Funktionsparameter übergeben: Die Wartezeit in Sekunden.
        - Die Funktion akzeptiert einen Wert vom Datentyp "uint32_t".
        - Die Variable, die du vielleicht in der main() nutzt, sollte auch diesen Datentyp haben.
*/
void WarteSekunden(uint32_t Sekunden);


/*  WarteMillisekunden:
        - Wartet x Millisekunden an dieser Stelle im Programm (1000 Millisekunden = 1 Sekunde).
        - Bei dem Aufruf musst du einen Funktionsparameter übergeben: Die Wartezeit in Millisekunden.
        - Die Funktion akzeptiert einen Wert vom Datentyp "uint32_t".
        - Die Variable, die du vielleicht in der main() nutzt, sollte auch diesen Datentyp haben.
*/
void WarteMillisekunden(uint32_t Millisekunden);


/*  WarteMikrosekunden:
        - Wartet x Mikrosekunden an dieser Stelle im Programm (1000 Mikrosekunden = 1 Millisekunde).
        - Bei dem Aufruf musst du einen Funktionsparameter übergeben: Die Wartezeit in Mikrosekunden.
        - Die Funktion akzeptiert einen Wert vom Datentyp "uint32_t".
        - Die Variable, die du vielleicht in der main() nutzt, sollte auch diesen Datentyp haben.
*/
void WarteMikrosekunden(uint32_t Mikrosekunden);

#endif

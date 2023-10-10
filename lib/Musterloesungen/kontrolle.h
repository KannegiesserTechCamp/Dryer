#ifndef KONTROLLE_H
#define KONTROLLE_H

#include <Arduino.h>
#include "Motor.h"
#include "Zeit.h"
#include "LED.h"


/*  Eins_MotorBeschleunigenUndStoppen(), Eins_LedFeedback():
        Schreibe dein Erstes Trockner Programm, lasse die
        Trommel beschleunigen und wieder Stoppen,
        lagere dies in einer Funktion aus.
*/
void Eins_MotorBeschleunigenUndStoppen(uint8_t targetSpeed, int runtime_millis);
void Eins_LedFeedback(uint8_t prozent, Farbe farbe, uint8_t helligkeit);

/*  Zwei_HellerWerdenUndWiederAusgehen:
        Lasse die LED heller werden und wieder ausgehen,
        lagere dies in einer neuen Funktion aus.
*/
void Zwei_HellerWerdenUndWiederAusgehen();

/*  Drei_BlinkenUndFarbeWechseln:
        Lasse die LED blinken und die Farbe wechseln und
        wieder ausgehen.
*/
void Drei_BlinkenUndFarbeWechseln();


/*  Vier_BlinkenUndDrehen:
        Schreibe ein Programm, in dem der Trockner die folgenden Schritte durchführt:
            1. 3x rot blinken
            2. 2x blau blinken
            3. 1x grün blinken
            4. Rotes Licht ist an und die Trommel beschleunigt
            5. Bis auf maximum beschleunigen, dann wieder runterbremsen und die richtung wechseln
            6. Rotes Licht aus
            7. 5x rot blinken
*/
void Vier_BlinkenUndDrehen();


#endif
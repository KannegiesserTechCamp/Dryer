#include "kontrolle.h"


uint8_t eins_geschwindigkeit = 0;

Farbe eins_farbe = rot;
int8_t eins_richtung = 1;
int eins_momentaneLaufzeit = 0;

void Eins_MotorBeschleunigenUndStoppen(
    uint8_t zielGeschwindigkeit,
    int laufzeit_millisekunden
) {

    Eins_LedFeedback(eins_geschwindigkeit, eins_farbe, 10);

    MotorGeschwindigkeit(eins_geschwindigkeit);

    MotorDrehenRechts();

    if (eins_richtung == 1) {
        if (eins_geschwindigkeit < 100){
            eins_farbe = blau;
            eins_geschwindigkeit += eins_richtung;
            WarteMillisekunden(100);
        } else {
            eins_richtung = -1;
            eins_farbe = gruen;
        }
    }

    if (eins_richtung == -1) {
        if (eins_geschwindigkeit == 100) {
            WarteMillisekunden(laufzeit_millisekunden);
            eins_farbe = magenta;
            eins_geschwindigkeit += eins_richtung;
        } else {
            eins_farbe = rot;
            if (eins_geschwindigkeit > 0) {
                Eins_LedFeedback(eins_geschwindigkeit, eins_farbe, 10);
                WarteMillisekunden(100);
                eins_geschwindigkeit += eins_richtung;
            } else {
                MotorStopp();
            }
        }
    }
}

void Eins_LedFeedback(uint8_t prozent, Farbe farbe, uint8_t helligkeit) {
    
    uint8_t anzahl = floor(prozent / (100/7));
    
    for (size_t i = 0; i < anzahl; i++) {
        LedEinzelFarbeHelligkeit(i, farbe, helligkeit);
    }
    for (size_t i = anzahl; i < 7; i++) {
        LedEinzelFarbeHelligkeit(i, schwarz, 0);
    }
    
}

int zwei_helligkeit = 1;
int zwei_richtungHell = 1;

void Zwei_HellerWerdenUndWiederAusgehen() {
    if (zwei_helligkeit == 100) {
        zwei_richtungHell = -1;
    }
    
    if(zwei_helligkeit > 0 && zwei_helligkeit <= 100) {
        zwei_helligkeit += zwei_richtungHell;
    }
    LedLeisteFarbeHelligkeit(magenta, zwei_helligkeit);
    WarteMillisekunden(100);
}

Farbe drei_farben[] = {rot, gelb, gruen};
int drei_index = 0;
void Drei_BlinkenUndFarbeWechseln() {
    
    LedLeisteFarbeHelligkeit(drei_farben[drei_index], 10);
    WarteMillisekunden(300);
    
    LedLeisteFarbeHelligkeit(schwarz, 10);
    WarteMillisekunden(300);

    if(drei_index < 3) {
        drei_index++;
    }
}

bool vier_istFertig = false;
void Vier_BlinkenUndDrehen() {
    if(vier_istFertig) return;
    vier_istFertig = true;
    int blinklaenge = 300;

    // 3x rot blinken
    for (size_t i = 0; i < 3; i++) {
        LedLeisteFarbeHelligkeit(rot, 10);
        WarteMillisekunden(blinklaenge);

        LedLeisteFarbeHelligkeit(schwarz, 10);
        WarteMillisekunden(blinklaenge);
    }
    
    // 2x blau blinken
    for (size_t i = 0; i < 2; i++) {
        LedLeisteFarbeHelligkeit(blau, 10);
        WarteMillisekunden(blinklaenge);

        LedLeisteFarbeHelligkeit(schwarz, 10);
        WarteMillisekunden(blinklaenge);
    }

    // 1x gruen blinken
    LedLeisteFarbeHelligkeit(gruen, 10);
    WarteMillisekunden(blinklaenge);

    LedLeisteFarbeHelligkeit(schwarz, 10);
    WarteMillisekunden(blinklaenge);
    
    // rot an, trommel beschleunigt bis max
    LedLeisteFarbeHelligkeit(rot, 10);
    for (size_t i = 0; i < 100; i++) {
        MotorGeschwindigkeit(i);
        MotorDrehenRechts();
        WarteMillisekunden(100);
    }

    // entschleunigen
    for (size_t i = 100; i > 0; i--) {
        MotorGeschwindigkeit(i);
        WarteMillisekunden(100);
    }

    // richtung wechseln
    for (size_t i = 0; i < 100; i++) {
        MotorGeschwindigkeit(i);
        MotorDrehenLinks();
        WarteMillisekunden(100);
    }
    for (size_t i = 100; i > 0; i--) {
        MotorGeschwindigkeit(i);
        WarteMillisekunden(100);
    }
    MotorStopp();
    
    // rot aus
    LedLeisteFarbeHelligkeit(schwarz, 10);
    WarteMillisekunden(blinklaenge);

    // 5x rot blinken
    for (size_t i = 0; i < 5; i++) {
        LedLeisteFarbeHelligkeit(rot, 10);
        WarteMillisekunden(blinklaenge);

        LedLeisteFarbeHelligkeit(schwarz, 10);
        WarteMillisekunden(blinklaenge);
    }
}
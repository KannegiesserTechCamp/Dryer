
#include "animated_rainbow.h"

// ANIMIERTER REGENBOGEN

/*
    Wendet die Farben in farben an, mit einem Versatz. Die Farben, die rechts abgeschnitten werden, werden links wieder hinzugefügt.
*/
void FarbenAnwendenUndUmbrechen(int anzahl, int versatz, Farbe farben[7], uint8_t helligkeit) {

    for (size_t i = versatz; i < anzahl; i++) {
        LedEinzelFarbeHelligkeit(i, farben[i-versatz], helligkeit);
    }

    for (size_t i = 0; i < versatz; i++) {
        LedEinzelFarbeHelligkeit(i, farben[i - versatz + anzahl], helligkeit);
    }
    

}

int versatz = 0;

void AnimierterRegenbogen(uint8_t helligkeit) {
    Farbe farben[7] = {rot, orange, gelb, gruen, blau, magenta, schwarz};
    FarbenAnwendenUndUmbrechen(6, versatz, farben, helligkeit);

    WarteMillisekunden(250);
    if (versatz == 5) {
        versatz = 0;
    } else {
        versatz += 1;
    }

}
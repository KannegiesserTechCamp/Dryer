#ifndef ANIMATED_RAINBOW_H
#define ANIMATED_RAINBOW_H

#include <Arduino.h>
#include "LED.h"
#include "Zeit.h"


/*
    Wendet die Farben in farben an, mit einem Versatz. Die Farben, die rechts abgeschnitten werden, werden links wieder hinzugefügt.
*/
void FarbenAnwendenUndUmbrechen(int anzahl, int versatz, Farbe farben[7], uint8_t helligkeit);

void AnimierterRegenbogen(uint8_t helligkeit);

# endif
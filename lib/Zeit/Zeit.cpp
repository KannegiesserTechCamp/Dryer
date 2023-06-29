#include <Arduino.h>
#include "Zeit.h"

void WarteSekunden(uint32_t Sekunden)
{
    delayMicroseconds(Sekunden * 1000000);
}

void WarteMillisekunden(uint32_t Millisekunden)
{
    delayMicroseconds(Millisekunden * 1000);
}

void WarteMikrosekunden(uint32_t Mikrosekunden)
{
    delayMicroseconds(Mikrosekunden);
}
#ifndef MORSE_CODE_H
#define MORSE_CODE_H

#include <Arduino.h>
#include "LED.h"
#include "Zeit.h"

void dot();

void dash();

void gap_dot();

void gap_char();

void gap_word();

void letter(char letter);

void sos();

void morse_code(Farbe color, int unit, uint8_t brightness);

# endif
#include "morse_code.h"

/*
    1 unit = 300 ms
    dot: 1 unit
    dash: 3 units
    gap: 1 unit
    gap between characters: 3 units
    gap between words: 7 units
*/

Farbe _color;
uint8_t _brightness;
int _unit;

void dot() {
    LedLeisteFarbeHelligkeit(_color, _brightness);
    WarteMillisekunden(_unit);
}

void dash() {
    LedLeisteFarbeHelligkeit(_color, _brightness);
    WarteMillisekunden(_unit * 3);
}

void gap_dot() {
    LedLeisteFarbeHelligkeit(schwarz, _brightness);
    WarteMillisekunden(_unit);
}

void gap_char() {
    LedLeisteFarbeHelligkeit(schwarz, _brightness);
    WarteMillisekunden(_unit * 3);
}

void gap_word() {
    LedLeisteFarbeHelligkeit(schwarz, _brightness);
    WarteMillisekunden(_unit * 7);
}

void letter(char letter) {
    switch (letter)
    {
    case 's':
        dot();
        gap_dot();
        dot();
        gap_dot();
        dot();
        break;

    case 'o':
        dash();
        gap_dot();
        dash();
        gap_dot();
        dash();
        break;

    default:
        break;
    }
}

void sos() {
    letter('s');
    gap_char();
    letter('o');
    gap_char();
    letter('s');
    gap_word();
}


void morse_code(Farbe color, int unit, uint8_t brightness) {
    _color = color;
    _brightness = brightness;
    _unit = unit;


    sos();
}
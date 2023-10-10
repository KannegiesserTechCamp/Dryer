#include "bouncing_pixel.h"

int direction = 1;
int pixel_index = 0;

void bouncing_pixel(Farbe pixel_color, Farbe background_color, int delay, uint8_t brightness) {

    // reset colors back to black
    for (size_t i = 0; i <= 6; i++)
    {
        LedEinzelFarbeHelligkeit(i, background_color, brightness);
    }
    
    // apply pixel color to indexed pixel
    LedEinzelFarbeHelligkeit(pixel_index, pixel_color, brightness);

    // change direction when right edge is reached
    if (pixel_index == 6 && direction == 1) {
        direction = -1;
    }

    // change direction when left edge is reached
    if (pixel_index == 0 && direction == -1) {
        direction = 1;
    }

    // increment index for animation
    pixel_index += direction;

    // delay of 250 miliseconds
    WarteMillisekunden(delay);
}
// externe Libraries 
#include <NeoPixelBus.h>
#include <NeoPixelBrightnessBus.h>
 
#include "LED.h"

#define LED_DATA_PIN 26
#define COLOR_SATURATION 255  // set color to 128, this can be between 0 (black, regardless of hue or saturation) and 255 (maximum brightness).
#define PIXEL_COUNT 7 // count of LEDs in the strip
const unsigned long timeout_led_brighten= 50; //time for each ledbrightenstadium
unsigned int step_led = 0; // steps in the ledbrightenprozess, first it must set to step 0, because we start counting with 0 not with 1 
unsigned long step_led_start_millis = 0; // ms have set to 0, start timer at time 0

NeoPixelBus<NeoGrbFeature, NeoWs2811Method> strip(PIXEL_COUNT, LED_DATA_PIN);

const uint8_t c_MinBrightness = 8; // min Brightness for LED Loop is 8, value can be between 0 and 255
const uint8_t c_MaxBrightness = 96; // max Brightness for LED Loop is 96,  value can be between 0 and 255  
int8_t direction = -1;
uint8_t brightness = c_MaxBrightness;

// definitions of the colors red, green, blue and black 
const RgbColor red(COLOR_SATURATION, 0, 0);
const RgbColor green(0, COLOR_SATURATION, 0);
const RgbColor blue(0, 0, COLOR_SATURATION);
const RgbColor black(0);

// setup 
void ledsetup()
{
    // set PIN to Output
    pinMode(LED_DATA_PIN, OUTPUT);

    // this resets all the neopixels to an off state
    strip.Begin();
    strip.Show();
}

// loop 
void led_loop()
{
    // ### LED LOOP ###
    switch (step_led)
    {
        case 0:
            // If the brightness is lower than the min brightness, it should be increased again by 1
            if (brightness <= c_MinBrightness)
            {
                direction = 1;
            }
            // If the brightness is greater than the max. brightness, it should be reduced by 1 again.
            else if (brightness >= c_MaxBrightness)
            {
                direction = -1;
            }

            // apply dimming
            brightness += direction;

            for (size_t i = 0; i < PIXEL_COUNT; i++)
            {
                strip.SetPixelColor(i, RgbColor(0,0,brightness));
            }

            // show the results
            strip.Show();
            step_led_start_millis = millis();
            step_led = 1;
        break; 

        case 1:
          // after 50 ms the prozess will start again - it will beginn with case 0
          if (millis() > step_led_start_millis + timeout_led_brighten)
          {
              step_led = 0;
          }
        break;      
    }
}

// ### LED off ### 
void led_off()
{
  // Set LEDPixelColor to black
  strip.ClearTo(black);
  strip.Show();
}
    

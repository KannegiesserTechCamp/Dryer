#include <NeoPixelBus.h>
#include <NeoPixelBrightnessBus.h>
#include "LED.h"

const int LED_DATA_PIN = 26;

const uint16_t PixelCount = 7; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 26;  // make sure to set this to the correct pin, ignored for Esp8266

#define colorSaturation 128

const unsigned long timeout_led_brighten= 50;
const unsigned long timeout_led_darken = 1000;
unsigned int step_led = 0;
unsigned long step_led_start_millis = 0;
uint8_t ramp_led_counter = 0;
unsigned int ramp_led_step_time = 0;

NeoPixelBus<NeoGrbFeature, NeoWs2811Method> strip(PixelCount, PixelPin);

const uint8_t c_MinBrightness = 8; 
const uint8_t c_MaxBrightness = 96;
int8_t direction = -1;
uint8_t brightness = c_MaxBrightness;

const RgbColor red(colorSaturation, 0, 0);
const RgbColor green(0, colorSaturation, 0);
const RgbColor blue(0, 0, colorSaturation);
const RgbColor black(0);

// setup 
void ledsetup() {
  pinMode(LED_DATA_PIN, OUTPUT);

  // this resets all the neopixels to an off state
  strip.Begin();
  strip.Show();

  for (size_t i = 0; i < PixelCount; i++)
  {
    strip.SetPixelColor(i, RgbColor(0,0,brightness));
  }

  strip.Show();

  Serial.println();
  Serial.println("Running...");
}

// loop 
void led_loop() {
  
  // ### LED LOOP ###
  switch (step_led) {

    case 0:
      
      if (brightness <= c_MinBrightness)
    {
      direction = 1;
    }
    else if (brightness >= c_MaxBrightness)
    {
      direction = -1;
    }
    // apply dimming
    brightness += direction;

    for (size_t i = 0; i < PixelCount; i++)
    {
      strip.SetPixelColor(i, RgbColor(0,0,brightness));
    }

    // show the results
    strip.Show();

      step_led_start_millis = millis();
      step_led = 1;
      break;

    case 1:
      if (millis() > step_led_start_millis + timeout_led_brighten)
      {
        step_led = 0;
      }
      break;
      
  }
}

  void led_off(){
    strip.SetPixelColor(0, RgbColor(0));
  }
    

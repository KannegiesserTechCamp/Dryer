#include <Arduino.h>

#include "LED.h"
#include "Trockner.h"

void setup(){
  ledsetup();
  Motorsetup();
}

void loop(){
  led_loop();
  Motorloop();
}
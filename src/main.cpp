#include <Arduino.h>

#include "LED.h"
#include "Dryer.h"

void setup(){
    ledsetup();
    Motorsetup();
}

void loop(){
    led_loop();
    Motorloop();
}

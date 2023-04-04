#include <Arduino.h>
#include "Dryer.h"

const int MOTOR_PIN_1 = 13;
const int MOTOR_PIN_2 = 12;
const int MOTOR_PIN_3 = 14;
const int MOTOR_PIN_4 = 27;

const unsigned long timeout_run_motor = 5000;
const unsigned long timeout_stop_motor = 1000;
const unsigned long timeout_step_ramp = 500;
unsigned int step_motor = 0;  
unsigned long step_start_millis = 0;
uint8_t ramp_counter = 0;
unsigned int ramp_step_time = 0;

void Motorsetup() {
  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);
  pinMode(MOTOR_PIN_3, OUTPUT);
  pinMode(MOTOR_PIN_4, OUTPUT);
}

void Motorloop(){
    switch(step_motor)
  {
    case 0:
      step_start_millis = millis();
      ramp_step_time = millis();
      ramp_counter = 2;
      step_motor = 1;
      break;

    case 1:
      if (millis() > ramp_step_time + timeout_step_ramp)
      {
        ramp_step_time = millis();
        ramp_counter++;
      }
      
      analogWrite(MOTOR_PIN_1, min(255, 32*ramp_counter-1));
      
      if(ramp_counter >= 8) {
        analogWrite(MOTOR_PIN_1, 255);
        ramp_counter = 0;
        step_start_millis = millis();
        step_motor = 2;
      }
      break;

    case 2:
      if (millis() > step_start_millis + timeout_run_motor)
      {
        step_start_millis = millis();
        ramp_step_time = millis();
        ramp_counter = 8;
        step_motor = 3;
      }
      break;

    case 3:
      if (millis() > ramp_step_time + timeout_step_ramp)
      {
        ramp_step_time = millis();
        ramp_counter--;
      }
      
      analogWrite(MOTOR_PIN_1, min(255, 32*ramp_counter-1));
      
      if(ramp_counter < 2) {
        analogWrite(MOTOR_PIN_1, 0);
        ramp_counter = 0;
        step_start_millis = millis();
        step_motor = 4;
      }
      break;

    case 4:
      step_start_millis = millis();
      ramp_step_time = millis();
      ramp_counter = 2;
      step_motor = 5;
      break;

    case 5:
      if (millis() > ramp_step_time + timeout_step_ramp)
      {
        ramp_step_time = millis();
        ramp_counter++;
      }
      
      analogWrite(MOTOR_PIN_2, min(255, 32*ramp_counter-1));
      
      if(ramp_counter >= 8) {
        analogWrite(MOTOR_PIN_2, 255);
        ramp_counter = 0;
        step_start_millis = millis();
        step_motor = 6;
      }
      break;

    case 6:
      if (millis() > step_start_millis + timeout_run_motor)
      {
        step_start_millis = millis();
        ramp_step_time = millis();
        ramp_counter = 8;
        step_motor = 7;
      }
      break;

    case 7:
      if (millis() > ramp_step_time + timeout_step_ramp)
      {
        ramp_step_time = millis();
        ramp_counter--;
      }
      
      analogWrite(MOTOR_PIN_2, min(255, 32*ramp_counter-1));
      
      if(ramp_counter < 2) {
        analogWrite(MOTOR_PIN_2, 0);
        ramp_counter = 0;
        step_start_millis = millis();
        step_motor = 0;
      }
      break;

  }
}

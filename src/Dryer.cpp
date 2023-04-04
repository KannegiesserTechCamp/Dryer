#include <Arduino.h>
#include "Dryer.h"

// Hardware pins for motoroutputs
#define MOTOR_PIN_1 13
#define MOTOR_PIN_2 12
#define MOTOR_PIN_3 14
#define MOTOR_PIN_4 27

// time and step values
#define TIMEOUT_STEP_RAMP 500
#define MIN_RAMP_STEP 2
#define MAX_RAMP_STEP 8

unsigned int step_motor = 0;  // begin motor step with 0
unsigned long step_start_millis = 0; // start timer at 0 ms 
uint8_t ramp_counter = 0;  // counter to increase or decrease motorspeed
unsigned int ramp_step_time = 0; // to save time in millis in the ramp

void Motorsetup() 
{
    // set PINS to Output
    pinMode(MOTOR_PIN_1, OUTPUT);
    pinMode(MOTOR_PIN_2, OUTPUT);
    pinMode(MOTOR_PIN_3, OUTPUT);
    pinMode(MOTOR_PIN_4, OUTPUT);
}

// ### RUNFUNCTIONS MOTOR ###
// ## motor will be run to the left ##
void MotorLeft()
{
    switch(step_motor)
    {
        case 0:
            step_start_millis = millis();
            ramp_step_time = millis();
            ramp_counter = MIN_RAMP_STEP;
            step_motor = 1;
        break;

        case 1:
        // motor is accelerated 
            if (millis() > (ramp_step_time + TIMEOUT_STEP_RAMP))
            {
                ramp_step_time = millis();
                ramp_counter++;
            }
            
            SetMotorSpeed(MOTOR_LEFT, ramp_counter);
            
            // if the ramp counter reaches its max value, motor will run with the highest speed
            // motor endurance run left
            if(ramp_counter >= MAX_RAMP_STEP)
            {
                ramp_counter = 0;
                step_start_millis = millis();
                step_motor = 2;
            }
        break;

        case 2:
            step_start_millis = millis();
            ramp_step_time = millis();
            ramp_counter = MAX_RAMP_STEP;
            step_motor = 3;
        break;
    }
}

// ## motor will be run to the right ## 
void MotorRight()
{
    switch(step_motor)
    {
      case 0:
          step_start_millis = millis();
          ramp_step_time = millis();
          ramp_counter = MIN_RAMP_STEP;
          step_motor = 1;
      break;

      case 1:
          if (millis() > (ramp_step_time + TIMEOUT_STEP_RAMP))
          {
              ramp_step_time = millis();
              ramp_counter++;
          }
          
          SetMotorSpeed(MOTOR_RIGHT, ramp_counter);

          // if the highest ramp counter is reached, motor will run with the highest speed
          // Motor Endurance run right

          if(ramp_counter >= MAX_RAMP_STEP)
          {
              ramp_counter = 0;
              step_start_millis = millis();
              step_motor = 2;
          }
      break;

      case 2:
          step_start_millis = millis();
          ramp_step_time = millis();
          ramp_counter = MAX_RAMP_STEP;
          step_motor = 3;
      break;
    }
}


// ### STOPFUNKTIONS MOTOR ###
// ## Motor will be stop run in the right directions ## 
void MotorStopRight()
{
    if (step_motor == 3)
    {
        // Motor is slowed down 
        if (millis() > (ramp_step_time + TIMEOUT_STEP_RAMP))
        {
            ramp_step_time = millis();
            ramp_counter--;
        }
        
        SetMotorSpeed(MOTOR_RIGHT, ramp_counter);
        
        // Motor stop
        if(ramp_counter < MIN_RAMP_STEP)
        {
            ramp_counter = 0;
            step_start_millis = millis();
            step_motor = 0;
            SetMotorSpeed(MOTOR_OFF, MIN_RAMP_STEP);
        }
    }
}

// ## Motor will be stop run in the left direction ##
void MotorStopLeft()
{
    if (step_motor == 3)
    {
        // Motor is slowed down
        if (millis() > (ramp_step_time + TIMEOUT_STEP_RAMP))
        {
            ramp_step_time = millis();
            ramp_counter--;
        }
          
        SetMotorSpeed(MOTOR_LEFT, ramp_counter);
        
        // Motor stop
        if(ramp_counter < MIN_RAMP_STEP)
        {
            ramp_counter = 0;
            step_start_millis = millis();
            step_motor = 0;
            SetMotorSpeed(MOTOR_OFF, MIN_RAMP_STEP);
        }
    }
}

void SetMotorSpeed(int direction, int rampStep)
{
    // keep speed multiplier in bounds
    rampStep = max(1, rampStep);
    rampStep = min(MAX_RAMP_STEP, rampStep);
    
    // set motor speed in given direction
    switch (direction)
    {
        case MOTOR_LEFT:
            analogWrite(MOTOR_PIN_1, LOW);
            analogWrite(MOTOR_PIN_2, min(255, (32 * rampStep - 1)));
        break;

        case MOTOR_RIGHT:
            analogWrite(MOTOR_PIN_1, min(255, (32 * rampStep - 1)));
            analogWrite(MOTOR_PIN_2, LOW);
        break;

        default:
            MotorOff();
        break;
    }
}

void MotorOff()
{
    analogWrite(MOTOR_PIN_1, LOW);
    analogWrite(MOTOR_PIN_2, LOW);
}
#include <Arduino.h>
#include "Motor.h"

// Defines 
#define MOTOR_PIN_1 13
#define MOTOR_PIN_2 12
#define MOTOR_PIN_3 14
#define MOTOR_PIN_4 27

// Private variables
uint8_t GlMotorGeschwindigkeit = 0;
bool GlMotorDreht = false;
bool GlMotorDrehtRechts = false;
bool GlMotorDrehtFalsch = false;

// Public functions
void MotorInitialisierung()
{
    pinMode(MOTOR_PIN_1, OUTPUT);
    pinMode(MOTOR_PIN_2, OUTPUT);
    pinMode(MOTOR_PIN_3, OUTPUT);
    pinMode(MOTOR_PIN_4, OUTPUT);
}

void MotorDrehrichtungFalsch()
{
    GlMotorDrehtFalsch = true;
}

void MotorGeschwindigkeit(uint8_t Geschwindigkeit)
{
    if (Geschwindigkeit > 100)
    {
        Geschwindigkeit = 100;
    }

    GlMotorGeschwindigkeit = Geschwindigkeit;

    if (GlMotorDreht)
    {
        if (GlMotorDrehtRechts)
        {
            MotorDrehenRechts();
        }
        else
        {
            MotorDrehenLinks();
        }
    }
}

void MotorDrehenRechts()
{
    uint16_t Ui16MotorGeschwindigkeit = (uint16_t)(GlMotorGeschwindigkeit*5)+500;
    uint8_t Ui8MotorAnsteuerung = (uint8_t)(Ui16MotorGeschwindigkeit*2.55/10);

    if(GlMotorDrehtFalsch)
    {
        analogWrite(MOTOR_PIN_1, Ui8MotorAnsteuerung);
        analogWrite(MOTOR_PIN_2, LOW);
    }
    else
    {
        analogWrite(MOTOR_PIN_1, LOW);
        analogWrite(MOTOR_PIN_2, Ui8MotorAnsteuerung);
    }
    GlMotorDreht = true;
    GlMotorDrehtRechts = true;
}

void MotorDrehenLinks()
{
    uint16_t Ui16MotorGeschwindigkeit = (uint16_t)(GlMotorGeschwindigkeit*5)+500;
    uint8_t Ui8MotorAnsteuerung = (uint8_t)(Ui16MotorGeschwindigkeit*2.55/10);

    if(GlMotorDrehtFalsch)
    {
        analogWrite(MOTOR_PIN_1, LOW);
        analogWrite(MOTOR_PIN_2, Ui8MotorAnsteuerung);
    }
    else
    {
        analogWrite(MOTOR_PIN_1, Ui8MotorAnsteuerung);
        analogWrite(MOTOR_PIN_2, LOW);
    }

    GlMotorDreht = true;
    GlMotorDrehtRechts = false;
}

void MotorStopp()
{
    if (GlMotorDreht)
    {
        GlMotorDreht = false;
        analogWrite(MOTOR_PIN_1, LOW);
        analogWrite(MOTOR_PIN_2, LOW);
    }
}
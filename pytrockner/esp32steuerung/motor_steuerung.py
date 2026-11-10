from machine import Pin, PWM
from esp32steuerung.DCMotor import DCMotor

# Hinweis: Bitte diese Pins an deine Verkabelung anpassen.
# IN1/IN2 = Richtung, ENABLE = PWM-Geschwindigkeit (separater Pin am Motortreiber)
MOTOR_PIN_IN1 = 13
MOTOR_PIN_IN2 = 12
MOTOR_ENABLE_PIN = 27  # Anpassen: Der Enable/ENA-Pin deines Treibers

M_IN1 = Pin(MOTOR_PIN_IN1, Pin.OUT)
M_IN2 = Pin(MOTOR_PIN_IN2, Pin.OUT)

frequency = 400
enable_pwm = PWM(Pin(MOTOR_ENABLE_PIN, Pin.OUT), frequency)

# Einzelnes Motor-Objekt, Richtung über IN1/IN2, Geschwindigkeit über ENABLE
dc_motor = DCMotor(M_IN1, M_IN2, enable_pwm)

# Sicherer Ausgangszustand: Motor steht nach Import
M_IN1.value(0)
M_IN2.value(0)
enable_pwm.duty(0)

def _clamp_speed(speed: int) -> int:
    if speed is None:
        return 0
    if speed < 0:
        return 0
    if speed > 100:
        return 100
    return speed

def motor_links_drehen(speed: int):
    dc_motor.backwards(_clamp_speed(speed))
   	
def motor_rechts_drehen(speed: int):
    dc_motor.forward(_clamp_speed(speed))

def motor_stop():
    dc_motor.stop()
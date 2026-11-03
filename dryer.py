from machine import Pin, PWM
import time
import config

# PWM objects for the four H-bridge pins
_pwm1 = PWM(Pin(config.MOTOR_PIN_1))
_pwm2 = PWM(Pin(config.MOTOR_PIN_2))
_pwm3 = PWM(Pin(config.MOTOR_PIN_3))
_pwm4 = PWM(Pin(config.MOTOR_PIN_4))

for _p in (_pwm1, _pwm2, _pwm3, _pwm4):
    _p.freq(5000)
    _p.duty(0)

# Internal state variables (replace global variables from original C++ code)
step_motor = 0
step_start_millis = 0
ramp_counter = 0
ramp_step_time = 0


def _duty_0_255(value):
    """Convert Arduino analogWrite (0-255) to ESP32 PWM duty (0-1023)."""
    return max(0, min(1023, int(value / 255 * 1023)))


def _set_motor_pins(direction, ramp_step):
    ramp_step = max(1, min(config.MAX_RAMP_STEP, ramp_step))
    speed = _duty_0_255(32 * ramp_step - 1)

    if direction == config.MOTOR_LEFT:
        _pwm1.duty(0)
        _pwm2.duty(speed)
        _pwm3.duty(0)
        _pwm4.duty(0)
    elif direction == config.MOTOR_RIGHT:
        _pwm1.duty(speed)
        _pwm2.duty(0)
        _pwm3.duty(0)
        _pwm4.duty(0)
    else:
        MotorOff()


def Motorsetup():
    # Set all motor PWM outputs to zero
    for _p in (_pwm1, _pwm2, _pwm3, _pwm4):
        _p.duty(0)


def MotorLeft():
    global step_motor, step_start_millis, ramp_step_time, ramp_counter
    now = time.ticks_ms()

    if step_motor == 0:
        step_start_millis = now
        ramp_step_time = now
        ramp_counter = config.MIN_RAMP_STEP
        step_motor = 1

    elif step_motor == 1:
        if time.ticks_diff(now, ramp_step_time) > config.TIMEOUT_STEP_RAMP:
            ramp_step_time = now
            ramp_counter += 1
        _set_motor_pins(config.MOTOR_LEFT, ramp_counter)
        if ramp_counter >= config.MAX_RAMP_STEP:
            ramp_counter = 0
            step_start_millis = now
            step_motor = 2

    elif step_motor == 2:
        step_start_millis = now
        ramp_step_time = now
        ramp_counter = config.MAX_RAMP_STEP
        step_motor = 3


def MotorRight():
    global step_motor, step_start_millis, ramp_step_time, ramp_counter
    now = time.ticks_ms()

    if step_motor == 0:
        step_start_millis = now
        ramp_step_time = now
        ramp_counter = config.MIN_RAMP_STEP
        step_motor = 1

    elif step_motor == 1:
        if time.ticks_diff(now, ramp_step_time) > config.TIMEOUT_STEP_RAMP:
            ramp_step_time = now
            ramp_counter += 1
        _set_motor_pins(config.MOTOR_RIGHT, ramp_counter)
        if ramp_counter >= config.MAX_RAMP_STEP:
            ramp_counter = 0
            step_start_millis = now
            step_motor = 2

    elif step_motor == 2:
        step_start_millis = now
        ramp_step_time = now
        ramp_counter = config.MAX_RAMP_STEP
        step_motor = 3


def MotorStopRight():
    global step_motor, ramp_step_time, ramp_counter
    now = time.ticks_ms()
    if step_motor == 3:
        if time.ticks_diff(now, ramp_step_time) > config.TIMEOUT_STEP_RAMP:
            ramp_step_time = now
            ramp_counter -= 1
        _set_motor_pins(config.MOTOR_RIGHT, ramp_counter)
        if ramp_counter < config.MIN_RAMP_STEP:
            ramp_counter = 0
            step_motor = 0
            MotorOff()


def MotorStopLeft():
    global step_motor, ramp_step_time, ramp_counter
    now = time.ticks_ms()
    if step_motor == 3:
        if time.ticks_diff(now, ramp_step_time) > config.TIMEOUT_STEP_RAMP:
            ramp_step_time = now
            ramp_counter -= 1
        _set_motor_pins(config.MOTOR_LEFT, ramp_counter)
        if ramp_counter < config.MIN_RAMP_STEP:
            ramp_counter = 0
            step_motor = 0
            MotorOff()


def MotorOff():
    _pwm1.duty(0)
    _pwm2.duty(0)
    _pwm3.duty(0)
    _pwm4.duty(0)

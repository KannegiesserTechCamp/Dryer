from machine import Pin
import time
import neopixel
import config

# NeoPixel strip on LED_DATA_PIN with PIXEL_COUNT LEDs
_strip = neopixel.NeoPixel(Pin(config.LED_DATA_PIN), config.PIXEL_COUNT)

step_led = 0
step_led_start_millis = 0
brightness = config.LED_MAX_BRIGHTNESS
direction = -1
_led_status = False

BLACK = (0, 0, 0)


def ledsetup():
    # Initialize LED strip (turn off all pixels)
    _strip.fill(BLACK)
    _strip.write()


def get_status():
    return _led_status


def set_led_status(status):
    global _led_status
    _led_status = status


def led_loop():
    global step_led, step_led_start_millis, brightness, direction
    now = time.ticks_ms()

    if step_led == 0:
        if brightness <= config.LED_MIN_BRIGHTNESS:
            direction = 1
        elif brightness >= config.LED_MAX_BRIGHTNESS:
            direction = -1

        brightness += direction

        for i in range(config.PIXEL_COUNT):
            _strip[i] = (0, 0, brightness)
        _strip.write()

        step_led_start_millis = now
        step_led = 1

    elif step_led == 1:
        if time.ticks_diff(now, step_led_start_millis) > config.LED_TIMEOUT_BRIGHTEN:
            step_led = 0


def led_off():
    # Turn all LEDs off
    _strip.fill(BLACK)
    _strip.write()

import uasyncio as asyncio
import network
import time
import config
import dryer
import led
import web_server

# --- Start WiFi Access Point ---
ap = network.WLAN(network.AP_IF)
ap.active(True)
ap.config(essid=config.AP_SSID, password=config.AP_PASSWORD)

# Motor state
motor_mode = "stop"
motor_pending = None
motor_transition_until = 0
TRANSITION_DELAY_MS = 4000


def on_movement(direction):
    # Movement handler called by web server
    global motor_mode, motor_pending, motor_transition_until
    print("Movement:", direction)

    now = time.ticks_ms()

    if direction == "left":
        if motor_mode == "motorRight":
            # Motor runs right - brake first, then switch to left
            motor_mode = "stopright"
            motor_pending = "motorLeft"
            motor_transition_until = time.ticks_add(now, TRANSITION_DELAY_MS)
        elif motor_mode in ("stop", "stopleft", "stopright"):
            # Already stopped or running left - do nothing
            pass

    elif direction == "right":
        if motor_mode == "motorLeft":
            # Motor runs left - brake first, then switch to right
            motor_mode = "stopleft"
            motor_pending = "motorRight"
            motor_transition_until = time.ticks_add(now, TRANSITION_DELAY_MS)
        elif motor_mode in ("stop", "stopleft", "stopright"):
            # Already stopped or running right - do nothing
            pass

    elif direction == "stop":
        if motor_mode == "motorRight":
            motor_mode = "stopright"
        elif motor_mode == "motorLeft":
            motor_mode = "stopleft"
        else:
            motor_mode = "stop"
        motor_pending = None


def on_light():
    led.set_led_status(not led.get_status())
    print("LED toggled")


# Bind handlers to web server
web_server.movement_handler = on_movement
web_server.light_handler = on_light


async def hardware_loop():
    global motor_mode, motor_pending
    while True:
        now = time.ticks_ms()

        # Check if a pending direction change needs to be processed
        if motor_pending is not None:
            # Wait time elapsed?
            if time.ticks_diff(now, motor_transition_until) >= 0:
                # Motor must have actually stopped
                if dryer.motor_stopped():
                    motor_mode = motor_pending
                    motor_pending = None
                else:
                    # Motor still braking, wait a bit longer
                    await asyncio.sleep_ms(100)
                    continue
            else:
                # Wait time not elapsed yet
                await asyncio.sleep_ms(100)
                continue

        # LED
        if led.get_status():
            led.led_loop()
        else:
            led.led_off()

        # Motor
        if motor_mode == "motorRight":
            dryer.MotorRight()
        elif motor_mode == "motorLeft":
            dryer.MotorLeft()
        elif motor_mode == "stopleft":
            dryer.MotorStopLeft()
        elif motor_mode == "stopright":
            dryer.MotorStopRight()
        elif motor_mode == "stop":
            dryer.MotorOff()

        await asyncio.sleep_ms(20)


async def main():
    print("Starting Access Point:", config.AP_SSID)
    while not ap.active():
        await asyncio.sleep_ms(100)

    ip = ap.ifconfig()[0]
    print("AP-IP:", ip)
    print("Open in browser: http://{}".format(ip))

    # Initialize hardware
    dryer.Motorsetup()
    led.ledsetup()

    # Start web server
    await web_server.start_server()

    # Main loop
    await hardware_loop()


try:
    asyncio.run(main())
except KeyboardInterrupt:
    print("Stopped")

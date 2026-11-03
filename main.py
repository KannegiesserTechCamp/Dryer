import uasyncio as asyncio
import network
import config
import dryer
import led
import web_server

# --- Start WiFi Access Point ---
ap = network.WLAN(network.AP_IF)
ap.active(True)
ap.config(essid=config.AP_SSID, password=config.AP_PASSWORD)

# Current motor mode (replaces the String "Motor" from the original C++ code)
motor_mode = "stop"


def on_movement(direction):
    # Movement handler called by web server
    global motor_mode
    print("Movement:", direction)
    if direction == "left":
        if motor_mode in ("stop", "stopleft", "stopright"):
            motor_mode = "motorLeft"
        elif motor_mode == "motorRight":
            motor_mode = "stopleft"  # brake first, then change direction
    elif direction == "right":
        if motor_mode in ("stop", "stopleft", "stopright"):
            motor_mode = "motorRight"
        elif motor_mode == "motorLeft":
            motor_mode = "stopright"
    elif direction == "stop":
        if motor_mode == "motorRight":
            motor_mode = "stopright"
        elif motor_mode == "motorLeft":
            motor_mode = "stopleft"
        else:
            motor_mode = "stop"


def on_light():
    # Light toggle handler called by web server
    led.set_led_status(not led.get_status())
    print("LED toggled")


# Bind handlers to web server
web_server.movement_handler = on_movement
web_server.light_handler = on_light


async def hardware_loop():
    # Non-blocking loop for LED and motor state machines
    while True:
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

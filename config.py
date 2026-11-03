# Configuration for the Dryer (Micropython)

# --- WiFi Access Point --- 
AP_SSID = "Trockner-01"
AP_PASSWORD = "Kannegiesser"

# --- Hardware Pins --- 
MOTOR_PIN_1 = 13
MOTOR_PIN_2 = 12
MOTOR_PIN_3 = 14
MOTOR_PIN_4 = 27
LED_DATA_PIN = 26
PIXEL_COUNT = 7

# --- Motor Ramps --- 
TIMEOUT_STEP_RAMP = 500
MIN_RAMP_STEP = 2
MAX_RAMP_STEP = 8

# --- LED Breathing --- 
LED_MIN_BRIGHTNESS = 8
LED_MAX_BRIGHTNESS = 96 
LED_TIMEOUT_BRIGHTEN = 50

# --- PWM  Direction Constants ---
MOTOR_OFF = 0
MOTOR_LEFT = 1
MOTOR_RIGHT = 2

# ---  Web ---
WEB_ROOT = "web"
PORT = 80
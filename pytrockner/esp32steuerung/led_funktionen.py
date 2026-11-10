from machine import Pin
from neopixel import NeoPixel
import time

'''  
    Variablen
        - Du kannst die Anzahl der verfügbaren LEDs nutzen, z.B. für Schleifen. 
        - Denk daran, dass von 0 bis AnzahlLeds - 1 gezählt wird. Die erste LED trägt den Index 0.
'''

# In der Variable wird die Anzahl der LEDs im LED-Streifen gespeichert.
# Wichtig, in der Programmierung wird ab
LED_STRIP_LENGTH = 7
LED_STRIP_PIN = 26

LED_STRIP_PIN = Pin(LED_STRIP_PIN, Pin.OUT)
NEO_PIXEL_LED = NeoPixel(LED_STRIP_PIN, LED_STRIP_LENGTH)

def __get_color(selection: str, brightness):
    # Helligkeit prüfen und auf 0..100 begrenzen
    if brightness > 100:
        brightness = 100
    elif brightness < 0:
        brightness = 0

    # in 0..255 umrechnen
    brightness = int(brightness * 2.55)

    sel = (selection or "").lower()
    if sel == 'weiss':
        return brightness, brightness, brightness
    elif sel == 'schwarz':
        return 0, 0, 0
    elif sel == 'rot':
        return brightness, 0, 0
    elif sel == 'blau':
        return 0, 0, brightness
    elif sel == 'gruen':
        return 0, brightness, 0
    elif sel == 'gelb':
        return brightness, brightness, 0
    elif sel == 'cyan':
        return 0, brightness, brightness
    elif sel == 'magenta':
        return brightness, 0, brightness
    else:
        return 0, 0, 0
        
def led_einzeln_einfach(index, farbe, helligkeit):
    if 0 <= index < LED_STRIP_LENGTH:
        NEO_PIXEL_LED[index] = __get_color(farbe, helligkeit)
        NEO_PIXEL_LED.write()
        
def led_eine_aus(index):
    if 0 <= index < LED_STRIP_LENGTH:
        NEO_PIXEL_LED[index] = (0, 0, 0)
        NEO_PIXEL_LED.write()
        
def led_leiste_einfach(farbe, helligkeit):
    for i in range(LED_STRIP_LENGTH):
        NEO_PIXEL_LED[i] = __get_color(farbe, helligkeit)
    NEO_PIXEL_LED.write()
    
def led_alle_aus():
    for i in range(LED_STRIP_LENGTH):
        NEO_PIXEL_LED[i] = (0, 0, 0)
    NEO_PIXEL_LED.write()

def __clamp_rgb(value):
    try:
        v = int(value)
    except (TypeError, ValueError):
        return 0
    if v < 0:
        return 0
    if v > 255:
        return 255
    return v


def __to_rgb_tuple(color):
    # Accepts '#rrggbb' hex strings (from Blockly) as well as (r, g, b) tuples/lists.
    if isinstance(color, str):
        s = color
        if s.startswith('#'):
            s = s[1:]
        if len(s) == 6:
            try:
                return (int(s[0:2], 16), int(s[2:4], 16), int(s[4:6], 16))
            except ValueError:
                return (0, 0, 0)
        return (0, 0, 0)
    if isinstance(color, (tuple, list)) and len(color) == 3:
        return (__clamp_rgb(color[0]), __clamp_rgb(color[1]), __clamp_rgb(color[2]))
    return (0, 0, 0)


def led_einzeln_rgb(index, color):
    # color: '#rrggbb' hex string or (r, g, b) tuple/list with 0..255 values.
    if 0 <= index < LED_STRIP_LENGTH:
        NEO_PIXEL_LED[index] = __to_rgb_tuple(color)
        NEO_PIXEL_LED.write()


def led_leiste_rgb(color):
    # color: '#rrggbb' hex string or (r, g, b) tuple/list with 0..255 values.
    rgb = __to_rgb_tuple(color)
    for i in range(LED_STRIP_LENGTH):
        NEO_PIXEL_LED[i] = rgb
    NEO_PIXEL_LED.write()



if __name__ == "__main__":											#Zum Testen/Debuggen
    led_leiste_einfach('rot', 50)
    time.sleep(1)
    led_alle_aus()
    time.sleep(1)
    led_leiste_einfach('gruen', 50)
    time.sleep(1)
    led_alle_aus()
    time.sleep(1)
    led_leiste_einfach('blau', 50)
    time.sleep(1)
    led_alle_aus()
    time.sleep(1)
    
    for i in range(LED_STRIP_LENGTH):
        led_einzeln_einfach(i, 'gelb', 100)
        time.sleep(0.5)
        led_eine_aus(i)
        
    time.sleep(1)
    
    led_einzeln_rgb(0, (255, 0, 0))  # Rot
    led_einzeln_rgb(1, (0, 255, 0))  # Grün
    led_einzeln_rgb(2, (0, 0, 255))  # Blau
    led_einzeln_rgb(3, (255, 255, 0))# Gelb
    led_einzeln_rgb(4, (0, 255, 255))# Cyan
    led_einzeln_rgb(5, (255, 0, 255))# Magenta
    led_einzeln_rgb(6, (255, 255, 255))# Weiß
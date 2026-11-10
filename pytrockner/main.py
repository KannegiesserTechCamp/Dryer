#  _  __                                         _                                      _____                 _                ____                             
# | |/ /   __ _   _ __    _ __     ___    __ _  (_)   ___   ___   ___    ___   _ __    |_   _|   ___    ___  | |__            / ___|   __ _   _ __ ___    _ __  
# | ' /   / _` | | '_ \  | '_ \   / _ \  / _` | | |  / _ \ / __| / __|  / _ \ | '__|     | |    / _ \  / __| | '_ \   _____  | |      / _` | | '_ ` _ \  | '_ \ 
# | . \  | (_| | | | | | | | | | |  __/ | (_| | | | |  __/ \__ \ \__ \ |  __/ | |        | |   |  __/ | (__  | | | | |_____| | |___  | (_| | | | | | | | | |_) |
# |_|\_\  \__,_| |_| |_| |_| |_|  \___|  \__, | |_|  \___| |___/ |___/  \___| |_|        |_|    \___|  \___| |_| |_|          \____|  \__,_| |_| |_| |_| | .__/ 
#                                        |___/                                                                                                           |_|   
#----------------------------------------------------------------------------------------------------------------------------------------------------------------

# IMPORTS: Schaue dir die Imports "led_funktionen" und "motor_steuerung" indem du mit <STRG + Mausklick> darauf klickst.
'''
 - "led_funktionen":
    - Die "led_funktionen" stellt dir Funktionen und Farben für die Steuerung der LED-Streifens zur Verfügung.

 - "motor_steuerung":
    - Die "motor_steuerung" stellt dir Funktionen zur Steuerung der Motoren zur Verfügung.
'''


from esp32steuerung.led_funktionen         import led_alle_aus, led_einzeln_einfach, led_einzeln_rgb, led_leiste_einfach, led_leiste_rgb
from esp32steuerung.motor_steuerung        import motor_rechts_drehen, motor_links_drehen, motor_stop
from time                                  import sleep as warte_sekunde
from misk.misk                             import warte_millisekunde

#
#
#   LEDs – Erklärung:
#   - led_leiste_einfach(farbe, helligkeit):
#       Stellt ALLE LEDs auf eine Farbe. Helligkeit von 0 bis 100.
#       Beispiele: led_leiste_einfach("rot", 100)  |  led_leiste_einfach("gruen", 30)
#       Mögliche Farben: "rot", "gruen", "blau", "gelb", "weiss", "cyan", "magenta".
#
#   - led_einzeln_einfach(index, farbe, helligkeit):
#       Schaltet EINE LED an der Position index an. Index zählt ab 0! (0 bis 6 bei 7 LEDs)
#       Beispiel: led_einzeln_einfach(0, "rot", 100)
#
#   - led_einzeln_rgb(index, (r, g, b)):
#       Farben ganz genau einstellen. r/g/b sind Zahlen von 0 bis 255.
#       Beispiele: led_einzeln_rgb(1, (0, 255, 0))  |  led_einzeln_rgb(1, "#00ff00")
#
#   - led_leiste_rgb((r, g, b)):
#       Stellt ALLE LEDs auf eine genaue Farbe. r/g/b sind Zahlen von 0 bis 255.
#       Beispiele: led_leiste_rgb((255, 0, 0))  |  led_leiste_rgb("#ff0000")
#
#   - led_alle_aus():
#       Schaltet alle LEDs aus.
#

#
#   Motoren – Erklärung:
#   - motor_rechts_drehen(geschwindigkeit):
#       Dreht den Motor nach rechts. geschwindigkeit von 0 bis 100.
#       Beispiel: motor_rechts_drehen(50)
#
#   - motor_links_drehen(geschwindigkeit):
#       Dreht den Motor nach links. geschwindigkeit von 0 bis 100.
#       Beispiel: motor_links_drehen(80)
#
#   - motor_stop():
#       Stoppt den Motor.
#

# Ab hier kannst du deinen eigenen Code schreiben.
#
# Beispiel – so kannst du starten:
#
#   while True:
#     led_leiste_einfach("rot", 100)  # Alle LEDs rot leuchten lassen
#     warte_sekunde(1)                # 1 Sekunde warten
#     led_alle_aus()                  # Alle LEDs ausschalten
#     warte_sekunde(1)                # 1 Sekunde warten
#
#   Das Beispiel lässt alle LEDs 1 Sekunde rot leuchten, dann 1 Sekunde aus – immer im Wechsel.
#  
# <vvvvvvvvvvvvvvvvvvvvvvvvvv DEIN CODE HIER DRUNTER vvvvvvvvvvvvvvvvvvvvvvvv>

while True:
   warte_sekunde(2)
   motor_rechts_drehen(50)  # Motor dreht nach rechts mit halber Geschwindigkeit
   warte_sekunde(2)
   motor_links_drehen(50)   # Motor dreht nach links mit halber Geschwindigkeit
   motor_stop()              # Motor anhalten
   warte_sekunde(2)
   motor_links_drehen(50)   # Motor dreht nach links mit halber Geschwindigkeit
   warte_sekunde(2)
   motor_stop()              # Motor anhalten
   led_leiste_einfach("blau", 100)  # Alle LEDs blau leuchten lassen
   warte_sekunde(1)                # 1 Sekunde warten
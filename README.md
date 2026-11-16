<img src="web/logo.svg" alt="Logo" width="1000"/>

# Tech-Camp: Kannegiesser

Herzlich willkommen zum Tech-Camp bei Kannegiesser! Nachdem du in den ersten beiden Tagen in Zusammenarbeit mit der Ausbildungs- und Elektrowerkstatt deinen Trockner gebaut hast, werden wir uns auf eine Reise in die faszinierende Welt der Programmierung begeben und uns einem ganz besonderen Projekt widmen - der Programmierung deines Trockners. 

Gemeinsam werden wir den Prozess durchlaufen, von der Einrichtung der notwendigen Software und Treiber auf deinem Windows-System bis hin zur Implementierung des Codes, der unseren Trockner zum Leben erweckt. Du wirst lernen, wie man Visual Studio Code einrichtet, die notwendigen Plugins installiert und die Treiber konfiguriert, die für unser Projekt benötigt werden. 

Egal, ob du ein erfahrener Programmierer bist oder gerade erst anfängst, das Tech-Camp bietet eine großartige Gelegenheit, praktische Erfahrungen zu sammeln und deine Fähigkeiten zu erweitern. Wir freuen uns darauf, dich bei dieser spannenden Reise zu begleiten! 

# Anleitung zur Einrichtung von Visual Studio Code unter Windows

In dieser Anleitung werden wir Schritt für Schritt durch den Prozess der Einrichtung und Konfiguration von Visual Studio Code gehen, einschließlich der Installation der notwendigen Tools für die Python-Programmierung. Diese Anleitung ist sowohl für Anfänger als auch für erfahrene Benutzer gedacht und soll dazu beitragen, dass du schnell mit deiner Programmierarbeit beginnen kannst. Lass uns anfangen! 

### Bauteile

- Trockner
  - ESP32 WROOM 32 240MHz, 320KB RAM, 4MB Flash
  - Batteriefach mit 3x AA
  - H-Brücke
  - LED-Streifen

#### Zusätzlich wirst du zum Erstellen des Programms benötigen:

- USB-A Kabel mit USB-Micro-B (alte Ladekabel für z.B. Android-Handys)
- Laptop mit [Visual Studio Code](https://code.visualstudio.com/)
- [Python](https://www.python.org/downloads/) (mit `pip` zum Installieren von Paketen)
- MicroPython-Tool `mpremote` (installierbar via `pip install mpremote`)

### Wichtiger Benutzerhinweis

**Stecke den ESP niemals mit dem USB-Kabel an Spannung an, wenn das Batteriefach auf AN steht!**

## Visual Studio Code

### Installation

1. Öffne deinen Webbrowser und besuche die offizielle Visual Studio Code-Website:  

    [https://code.visualstudio.com/](https://code.visualstudio.com/)

2. Klicke auf den Download-Button, um das Installationspaket für Windows herunterzuladen.

3. Nach dem Download öffne die Installationsdatei und folge den Anweisungen des Installationsassistenten, um Visual Studio Code auf deinem Gerät zu installieren.

### Starten

1. Nach der Installation von Visual Studio Code kannst du dieses über das Startmenü öffnen. 

2. Bei der ersten Verwendung wirst du aufgefordert, deine Einstellungen anzupassen. Du kannst die Standardeinstellungen beibehalten oder sie nach deinen Wünschen anpassen.
   
3. Um die Sprache anzupassen, öffnest du den Reiter “Extensions” und suchst nach “German Language Pack for Visual Studio Code” und installierst das Paket.

4. Nachdem du die Erweiterung erfolgreich installiert hast, starte das Programm neu, um alle
Änderung wirksam zu machen.

## Python und MicroPython einrichten

### Python installieren

1. Lade Python von der offiziellen Website herunter: [https://www.python.org/downloads/](https://www.python.org/downloads/)

2. Während der Installation **wichtig**: Hake “Add Python to PATH” an, damit Python über die Kommandozeile erreichbar ist.

3. Nach der Installation öffne eine Eingabeaufforderung (cmd) oder PowerShell und prüfe die Installation mit:

   ```powershell
   python --version
   ```

### MicroPython-Tool mpremote installieren

Das Tool `mpremote` wird benötigt, um die Python-Dateien auf den ESP32 zu übertragen. Installiere es mit:

```powershell
pip install mpremote
```

### MicroPython-Firmware auf den ESP32 flashen

Die passende MicroPython-Firmware ist bereits in `fw\installation.exe` enthalten. Beim Ausführen der Datei wird der ESP32 vollständig gelöscht und die Firmware aufgespielt. PyInstaller, das Python-Paket `esptool` und eine manuelle Firmware-Datei werden für die normale Installation nicht benötigt. Das mitgelieferte `ESPTool\esptool.exe` wird nur verwendet, wenn zusätzlich `fs\spiffs.bin` geflasht wird.

1. Schließe den ESP32 per USB an deinen Laptop an und ermittle den COM-Port (im Windows-Geräte-Manager unter „Anschlüsse (COM & LPT)“).

2. Starte die Installation aus dem Projektordner mit dem Deployment-Skript. Ersetze `COM3` durch den COM-Port deines ESP32:

   ```powershell
    .\deploy.ps1 -Port COM3
   ```

Das Deployment flasht zuerst die Firmware über `fw\installation.exe`, schreibt danach optional `fs\spiffs.bin` in den Filesystem-Bereich und überträgt anschließend die Python- und Web-Dateien.

## USB-Treiber NodeMCU CP2102 (ESP 32)

### Installation

1. Lade den USB-Treiber: CP2102 von der offiziellen Silicon Labs-Website für dein Betriebssystem herunter: [Silicon Labs Treiberseite](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)

2. Suche die heruntergeladene Datei in deinem Verzeichnis, klicke diese mit einem Rechtsklick an und wähle „Alle extrahieren“ aus, um die Datei zu entpacken.

3. Navigiere in den entpackten Ordner und suche nach der „silabser.inf“ Datei.

4. Klicke nun mit der rechten Maustaste auf die „silabser.inf“ Datei und wähle „Installieren“ aus.

5. Folge nun dem Installationssetup, bis der Treiber erfolgreich installiert wurde.

### Installation Testen (Optional):

1. Öffne den Windows-Geräte-Manager, indem du in der Windows-Suche "Geräte-Manager" eingibst.

2. In der Kategorie „Anschlüsse (COM & LPT)" findest du nun den "Silicon Labs CP210x USB to UART Bridge". Solltest du diesen nicht sehen, ist bei der Treiberinstallation etwas schiefgelaufen, springe dann zum Abschnitt USB-Treiber installieren und führe die Schritte erneut aus.

## Repository

### Download

1. Öffne deinen Webbrowser und besuche das folgende Github-Repository:

    [https://github.com/KannegiesserTechCamp/Dryer](https://github.com/KannegiesserTechCamp/Dryer)

2. Wenn du einen anderen Branch auswählen willst, klicke auf „main“ und wähle diesen in dem Dropdown-Menü aus.

3. Zum Download drücke auf den grünen Button „Code“ und wähle „Download ZIP“ aus.

### Entpacken

1. Suche die heruntergeladene Datei in deinem Verzeichnis, klicke diese mit einem Rechtsklick an und wähle „Alle extrahieren“ aus, um die Datei zu entpacken.

## Code auf den ESP32 übertragen und starten

Das Standard-Deployment erfolgt mit PowerShell und `deploy.ps1`. Das Skript führt einen Full Build durch. Dabei wird der Flash-Speicher durch `fw\installation.exe` gelöscht, anschließend die Firmware geschrieben, optional das Filesystem übertragen und danach werden die Python- und Web-Dateien kopiert.

> **Wichtiger Hinweis:** Beim Full Build wird der Flash-Speicher gelöscht. Sichere benötigte Daten vorher und führe das Skript nur aus, wenn der richtige COM-Port angeschlossen ist.

Voraussetzungen:

- PowerShell im Projektordner
- Python im PATH
- installiertes `mpremote` (`pip install mpremote`)
- angeschlossener ESP32 mit bekanntem COM-Port
- `ESPTool\esptool.exe` und `fw\installation.exe` im Projektordner
- optional `fs\spiffs.bin` für das Filesystem-Image

1. Schließe den ESP32 per USB an deinen Laptop an.

2. Öffne Visual Studio Code im Projektordner und starte ein Terminal (PowerShell).

3. Führe das Deployment-Skript aus:

   ```powershell
    .\deploy.ps1 -Port COM3
   ```

    Ersetze `COM3` durch den COM-Port deines ESP32. Der Full Build führt die folgenden Schritte aus:

    1. `fw\installation.exe` löscht den Flash und schreibt die MicroPython-Firmware.
    2. `fs\spiffs.bin` wird optional an Adresse `0x290000` geschrieben.
    3. Die Dateien aus `pytrockner/`, die Root-Python-Dateien und die Web-Assets werden übertragen.

    Bei Datei- und Firmware-Schritten werden Fehler begrenzt wiederholt; bei einem endgültigen Fehler bricht das Deployment ab.

### Ablauf von `deploy.ps1`

Das Skript führt die folgenden Schritte automatisch aus:

1. **Firmware installieren:** `fw\installation.exe` erkennt den angeschlossenen ESP32, löscht den Flash vollständig und schreibt die eingebettete MicroPython-Firmware. Der Firmware-Schritt wird bei einem Fehler bis zu dreimal versucht.
2. **Filesystem übertragen:** Wenn `fs\spiffs.bin` vorhanden ist, wird das Image mit `ESPTool\esptool.exe` an die Adresse `0x290000` geschrieben. Fehlt die Datei, wird dieser Schritt übersprungen.
3. **Ältere Python-Struktur übertragen:** Die Dateien aus `pytrockner/` werden rekursiv auf den ESP32 kopiert. Übertragen werden Python-, JSON-, TXT- und MPY-Dateien.
4. **Verbindung mit `mpremote` prüfen:** Das Skript testet, ob der ESP32 am angegebenen COM-Port erreichbar ist.
5. **Aktive Root-Python-Dateien übertragen:** `config.py`, `dryer.py`, `led.py`, `web_server.py` und `main.py` werden in das Hauptverzeichnis des ESP32 kopiert. Jeder Datei-Upload wird bei einem Fehler bis zu dreimal versucht.
6. **Weboberfläche übertragen:** Das Verzeichnis `web` wird angelegt. Danach werden `index.html`, `style.css`, `logo.png`, `Trocknerbutton.png` und `LEDbutton.png` kopiert.
7. **ESP32 neu starten:** Nach einem Soft Reset startet der ESP32 mit den übertragenen Dateien. Anschließend kann die Weboberfläche über die ausgegebene IP-Adresse geöffnet werden.

Schlägt ein notwendiger Schritt endgültig fehl, beendet `deploy.ps1` das Deployment mit einer Fehlermeldung. Der richtige COM-Port muss deshalb angeschlossen sein. Beim Firmware-Schritt wird der vollständige Flash gelöscht; vorhandene Daten auf dem ESP32 gehen dabei verloren.

4. Nach dem Neustart startet `main.py` automatisch. Die serielle Ausgabe zeigt die IP-Adresse des Access Points an, z. B.:

   ```
   Starting Access Point: Trockner-01
   AP-IP: 192.168.4.1
   Open in browser: http://192.168.4.1
   ```

5. Verbinde dein Smartphone oder deinen Laptop mit dem in `config.py` festgelegten WLAN und öffne im Browser die angezeigte IP-Adresse (standardmäßig `http://192.168.4.1`).

### Backup-Deployment

`deploy_backup.ps1` ist eine ältere Minimalvariante. Sie löscht den Flash nicht, flasht keine Firmware und kopiert nur die Root-Python-Dateien sowie die Web-Assets. Verwende sie nur, wenn der bestehende Firmware- und Filesystem-Stand erhalten bleiben soll.

## Projektstruktur

Der aktive Webbetrieb verwendet die Python-Dateien im Projektstamm:

| Datei | Beschreibung |
|-------|--------------|
| `main.py` | Einstiegspunkt. Startet den WiFi Access Point, den Webserver und die Hardware-Schleife (LED und Motor) mit `uasyncio`. |
| `config.py` | Konfiguration (WLAN-SSID/Passwort, GPIO-Pins, Motor-Rampen, LED-Helligkeit, Webserver-Port). |
| `dryer.py` | Motorsteuerung über die H-Brücke mit PWM und sanften Anfahrts-/Bremsrampen. |
| `led.py` | Steuerung des NeoPixel-LED-Streifens mit Atmungseffekt (Helligkeit auf und ab). |
| `web_server.py` | Kleiner asynchroner HTTP-Server. Liefert die Weboberfläche aus (`web/`) und verarbeitet POST-Anfragen für Bewegung und Licht. |
| `web/` | HTML-, CSS- und Bilddateien für die Weboberfläche. |
| `deploy.ps1` | PowerShell-Full-Build: Firmware installieren, optionales Filesystem und Dateien übertragen sowie den ESP32 zurücksetzen. |
| `deploy_backup.ps1` | Ältere Minimalvariante ohne Flash-Löschung und Firmware-Installation. |

Zusätzliche Verzeichnisse:

| Verzeichnis | Beschreibung |
|-------------|--------------|
| `pytrockner/` | Ältere bzw. lehrorientierte Steuerungsstruktur mit eigenen Motor- und LED-Modulen. Sie enthält eine andere Motoransteuerung als `dryer.py`; für den dokumentierten Webbetrieb ist der Root-Pfad maßgeblich. |
| `fs/` | Binäres Filesystem-Image `spiffs.bin`, das vom Full Build optional geflasht wird. |
| `fw/` | Mitgelieferte Firmware-Installation `installation.exe`. Die EXE enthält den Flasher und die passende MicroPython-Firmware. |

Die Weboberfläche in `web/` bietet Tasten für die Bewegung nach links, die Bewegung nach rechts und Stopp sowie einen Lichtschalter. Der ESP32 verarbeitet dafür unter anderem `POST /movement/left`, `POST /movement/right`, `POST /movement/stop` und `POST /light`.

## WLAN-Verbindung (Access Point)

Das Programm richtet auf dem ESP32 einen eigenen **WiFi Access Point** ein. Du verbindest dich direkt mit dem Trockner, keine Router- oder FritzBox-Konfiguration ist nötig.

- WLAN-Name: `Trockner-01` als Beispielwert aus `config.py`
- Passwort: `Kannegiesser` als Beispielwert aus `config.py`
- Standard-IP: `192.168.4.1` (wird im Terminal nach dem Start angezeigt)

### Eigenen WLAN-Namen und eigenes Passwort wählen

Ändere vor dem Deployment in `config.py` die beiden Werte `AP_SSID` und `AP_PASSWORD`:

```python
AP_SSID = "Mein-Trockner"
AP_PASSWORD = "EigenesPasswort123"
```

Wähle einen eindeutigen WLAN-Namen und ein eigenes, ausreichend langes Passwort. Verwende die Beispielwerte nicht dauerhaft. Nach dem Deployment verbindest du dein Smartphone oder deinen Laptop mit diesen eigenen Zugangsdaten. Das WLAN ist ein lokaler Access Point ohne Benutzeranmeldung am Webserver; die Verbindung läuft unverschlüsselt über HTTP.

Die IP-Adresse wird beim Start über `ap.ifconfig()[0]` ausgegeben. `192.168.4.1` ist der erwartete Standardwert, kann aber je nach Firmware- oder Netzwerkkonfiguration abweichen. Die Motorsteuerung setzt Richtungswechsel zunächst über einen Bremsvorgang um. Für den Betrieb müssen H-Brücke, Motor und sieben LEDs entsprechend der Pinbelegung in `config.py` angeschlossen sein.

### Überprüfe die Serielle Ausgabe (optional)

Wenn du während der Programmierung die serielle Ausgabe für Debugging-Zwecke aktiviert hast, kannst du sie über ein Terminal-Programm (z. B. den Serial Monitor in VS Code oder `mpremote repl`) überwachen. Wenn der ESP32 erfolgreich den Access Point gestartet hat, wird die IP-Adresse angezeigt.

Die folgenden Beispiele sind eigenständige Konsolenbeispiele für den Python-Unterricht. Sie werden nicht von `main.py` auf dem ESP32 ausgeführt.

# Python Programmierung:
Die folgenden Beispiele können mit Hilfe des Online-Compilers von [Programiz](https://www.programiz.com/python-programming/online-compiler/) getestet werden.


## Digitaler Trockner

### Code

```Python
# in 'startup' wird die Startoption des Benutzers (0, 1 oder 2) gespeichert
# in 'prog' wird die Programmoption des Benutzers (0, 1 oder 2) gespeichert
# in 'progname' wird der Name vom gewählten, oder des neuen Programmes gespeichert
startup = 0
prog = 0
progname = ""

# Ausgabe der Optionen für den Benutzer
print("Tippe:\n\t\t (0) zum Beenden \n\t\t (1) zum starten \n\t\t (2) für neues Programm")

# Einlesen der Benutzereingabe
startup = int(input())

# Überprüfung der Benutzereingabe und Ausführung des entsprechenden Codes
if startup == 0:
    print("Du hast dich für das Beenden des Trockners entschieden")

elif startup == 1:
    print("Der Trockner wird hochgefahren")
    print("\t\t3\n\t\t2\n\t\t1\n\t\t0")
    print("Trockner gestartet")
    print("bereit zum Trocknen")

    print("Waehle eines der folgenden Programme zum Trocknen aus:")
    print("\t(1) \t schnelles Trocknen")
    print("\t(2) \t Schleudertrauma")
    print("\t(3) \t Presskuchen")

    prog = int(input())
    print("Du hast dich für das folgenden Programm entschieden", end="")

    if prog == 1:
        # Zuweisung des Programmnamens an die Variable 'progname'
        progname = "schnelles Trocknen"
    elif prog == 2:
        progname = "Schleudertrauma"
    elif prog == 3:
        progname = "Presskuchen"

elif startup == 2:
    print("Du hast dich für das neue Programm entschieden")
    print("Gebe im Folgenden den Namen deines neuen Programms ein:")
    # Einlesen des neuen Programmnamens
    progname = input()

    print(f"Das Programm mit dem Namen: \n\t {progname} \nwurde erstellt")

else:
    print("Du hast leider keine der möglichen Eingaben (0), (1) gemacht")

print("Der Trockner wird heruntergefahren und beendet", end="")
```
Dieser Code stellt ein einfaches Menü zur Verfügung, mit dem der Benutzer verschiedene Optionen für einen digitalen Trockner auswählen kann. Der Benutzer kann den Trockner starten und ein Trockenprogramm auswählen, ein neues Programm erstellen oder den Trockner beenden. Die Auswahl des Benutzers wird über die Standard-Eingabe eingelesen und entsprechend verarbeitet. Der Code verwendet grundlegende Konzepte der Programmierung wie Variableninitialisierung, Ein- und Ausgabe, Kontrollstrukturen (if-else-Anweisungen) und Zeichenkettenoperationen.

Zum Testen: in den Online-Compilers von [Programiz](https://www.programiz.com/python-programming/online-compiler/) kopieren.

## Ausführliche Einführung

Dieses Programm stellt ein einfaches Menü zur Verfügung, mit dem der Benutzer verschiedene Optionen für einen digitalen Trockner auswählen kann. Es verwendet grundlegende Konzepte der Python-Programmierung wie Variableninitialisierung, Ein- und Ausgabe, Kontrollstrukturen (if-else-Anweisungen) und Zeichenkettenoperationen.

### Variableninitialisierung

In Python können Variablen direkt bei der ersten Zuweisung erstellt werden, ohne vorher einen Typ anzugeben. Zum Beispiel:
```python
startup = 0
prog = 0
progname = ""
```
In diesem Code werden zwei Ganzzahlvariablen (`startup` und `prog`) mit dem Startwert `0` 
und eine Zeichenkettenvariable (`progname`) mit einem leeren String `""` initialisiert.

### Ein- und Ausgabe

Die Funktionen `print` und `input` werden für die Ein- und Ausgabe verwendet. `print` wird 
verwendet, um Text auf dem Bildschirm auszugeben, und `input` wird verwendet, um die Eingabe 
des Benutzers zu lesen.

### Kontrollstrukturen

Die if-else-Anweisungen werden verwendet, um zu überprüfen, ob eine Bedingung erfüllt ist, 
und um den entsprechenden Codeblock auszuführen. Zum Beispiel:
```python
if startup == 0:
    print("Du hast dich für das Beenden des Trockners entschieden")
elif startup == 1:
    # Code für den Fall, dass 'startup' gleich 1 ist
else:
    # Code für den Fall, dass keine der vorherigen Bedingungen erfüllt ist
```

## Wäscheverwaltung
Zum Testen: in den Online-Compilers von [Programiz](https://www.programiz.com/python-programming/online-compiler/) kopieren.

### Code

```python
# Die Funktion 'waschen' nimmt einen String 'farbe' als Parameter an. Dieser String
# repräsentiert die Farbe der Wäsche, die gewaschen werden soll.
def waschen(farbe):
    # Die if-else-if-Anweisung überprüft, welche Farbe die Wäsche hat, und gibt eine
    # entsprechende Nachricht aus.
    if farbe == 'b':
        print("Blaue Waesche wird gewaschen")
    elif farbe == 'r':
        print("Rote Waesche wird gewaschen")
    elif farbe == 'g':
        print("Gruene Waesche wird gewaschen")
    elif farbe == 'w':
        print("Weisse Wasche wird gewaschen")
    elif farbe == 's':
        print("Schwarze Wasche wird gewaschen")
    else:
        # Wenn keine der obigen Bedingungen erfüllt ist (d.h., die Farbe ist nicht
        # blau, rot, grün, weiß oder schwarz), wird angenommen, dass die Wäsche bunt ist.
        print("\t\t Diese Farbe ist unbekannt")
        print("\t\t Die bunte Waesche wird gewaschen")


# Deklaration der Variablen
# 'exit' ist eine boolesche Variable, die bestimmt, ob die Hauptschleife des Programms weiterlaufen soll.
# 'anzahl' ist eine Ganzzahlvariable, die die Anzahl der Wäschestapel speichert.
# 'fertig' ist eine Ganzzahlvariable, die verwendet wird, um zu überprüfen, ob der Benutzer weitere Stapel hinzufügen möchte.
# 'farbe' ist eine Zeichenkettenvariable (str), die die Farbe der Wäsche speichert.
exit = True
anzahl = 0
fertig = 0
farbe = ""

# Ausgabe der Einführungsnachricht
print("Dies ist eine Aufnahmestelle fuer die Verwaltung von Waesche")

# Hauptschleife des Programms. Sie läuft so lange, bis der Benutzer entscheidet,
# dass keine weiteren Stapel hinzugefügt werden sollen.
while exit:
    # Aufforderung zur Eingabe der Anzahl und Farbe der Wäschestapel
    print("Gebe im folgenden Format: Anzahl(int) Farbe(char) an, was fuer Waesche angeliefert wurde")
    eingabe = input().split()
    anzahl = int(eingabe[0])
    farbe = eingabe[1]

    # Schleife zum Waschen jedes Wäschestapels
    for i in range(anzahl):
        print(f"Stapel-Nr. {i + 1}  ", end="")
        waschen(farbe)

    # Aufforderung zur Eingabe, ob weitere Stapel verteilt werden sollen
    print("Sollen weitere Stapel verteilt werden? Nein (0), Ja (1)")
    fertig = int(input())
    if fertig == 0:
        exit = False

# Ausgabe der Abschlussnachricht
print("Wir haben es geschafft, alle Stapel konnten sortiert werden", end="")
```

Dieser Code stellt ein einfaches Menü zur Verfügung, mit dem der Benutzer die Anzahl und Farbe von Wäschestapeln eingeben kann, die gewaschen werden sollen. Der Benutzer kann dann angeben, ob weitere Stapel verteilt werden sollen oder nicht. Der Code verwendet grundlegende Konzepte der Programmierung wie Variablendeklaration, Ein- und Ausgabe, Kontrollstrukturen (if-else-Anweisungen und Schleifen) und Funktionen.

## Ausführliche Einführung

### Variableninitialisierung

In Python werden Variablen direkt mit einem Startwert initialisiert. Der Datentyp wird 
dabei automatisch aus dem zugewiesenen Wert abgeleitet. Zum Beispiel:
```python
exit = True
anzahl = 0
fertig = 0
farbe = ""
```

In diesem Code werden eine boolesche Variable (`exit`), zwei Ganzzahlvariablen (`anzahl` und `fertig`) mit dem Startwert `0` 
und eine Zeichenkettenvariable (`farbe`) mit einem ``leeren String `""` initialisiert.

### Ein- und Ausgabe

Die Funktionen `print` und `input` werden für die Ein- und Ausgabe verwendet. `print` wird 
verwendet, um Text auf dem Bildschirm auszugeben, und `input` wird verwendet, um die Eingabe 
des Benutzers zu lesen.

### Kontrollstrukturen

Die if-else-Anweisungen werden verwendet, um zu überprüfen, ob eine Bedingung erfüllt ist, 
und um den entsprechenden Codeblock auszuführen. Zum Beispiel:
```python
if farbe == 'b':
    print("Blaue Waesche wird gewaschen")
elif farbe == 'r':
    print("Rote Waesche wird gewaschen")
elif farbe == 'g':
    print("Gruene Waesche wird gewaschen")
else:
    print("\t\t Diese Farbe ist unbekannt")
    print("\t\t Die bunte Waesche wird gewaschen")
```

### Funktionen

Eine Funktion ist ein Block von Code, der eine bestimmte Aufgabe ausführt. In diesem Programm 
gibt es eine Funktion: `waschen`. Die `waschen`-Funktion dient dazu, die Wäsche basierend auf 
ihrer Farbe zu waschen. In Python werden Funktionen mit dem Schlüsselwort `def` definiert.

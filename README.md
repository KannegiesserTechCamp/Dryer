# Tech-Camp ESP32 - Trockner mit LED-Stripes 

## Bauteile
- Trockner 
- ESP32 WROOM 32 240MHz, 320KB RAM, 4MB Flash
- Batteriefach mit 3x AA 
- H-Brücke 

zusätzlich wird zum Erstellen des Programms benötigt: 
- USB-A Kabel mit USB-Micro-B (alte Ladekabel für z.B. Android-Handys)
- Laptop mit Arduino IDE oder Visual Studio Code und PlatformIO-Erweiterung 

## Wichtige Benutzerhinweise
- Stecke den ESP niemals mit dem USB-Kabel an Spannung an, wenn das Batteriefach auf **AN** steht!

## Software für Programm-Code
Es gibt 2 möglichen Programme den Programm-Code für den ESP zu schreiben: 
1. Arduino IDE
    Vorteile: 
    - Farbige Darstellung bestimmter Variablen, vor allem auch Arduino/ESP Spezifisch 
    - Einfache Handhabung 
    - übersichtliche Oberfläche
    - Einfache Einrichtung des Programms

    Nachteile:
    - Nicht so praktisch, wenn man mehrere Dateien gleichzeitig anlegen möchte 
    - Nicht so einfach bestimmte Bibliotheken zu finden
    - kein Automatisches Einrücken 
    - Evtl. nicht so viele Boards zum auswählen verfügbar 
    - Kein einfaches auskommentieren/ ein kommentieren
    - Im Großen und Ganzen für eine .ino Datei gedacht 


2. Visual Studio Code mit PlatformIO
    Vorteile: 
    - Einfacheres suchen nach Bibliotheken
    - Überprüfung von C
    - Markieren aller gleichen Wörter bei Doppelklick 
    - Einfaches aus-/ein kommentieren
    - Einfaches auswählen des richtigen Boards
    - Serieller Monitor kann nach dem Kompilieren automatisch geöffnet werden 

    Nachteile: 
    - Durch mehr Funktionen, Handhabung nicht ganz so leicht, evtl. etwas unübersichtlicher (Ordnerstruktur)
    - andere Ordnerstruktur (benötigt .ini, im src den Programmcode, data-Ordner ist gleich)
    - Filesystem hochladen sind mehrere Schritte nötig 
    - Zum Einrichten mehrere Schritte nötig 

#### Download-links und Einrichtung 
1. Arduino IDE:
    https://www.arduino.cc/en/software

2. Visual Studio Code mit PlatformIO: 
    https://code.visualstudio.com/
    - auf die Bausteine (Erweiterungen) -> PlatformIO IDE -> Installieren


#### Richtiges Board auswählen 
1. Arduino IDE: 
- Werkzeuge -> Board -> ESP32 Bzw. Arduino auswählen 

2. PlatformIO: 
Bei "New Project" -> Board auswählen;
Framework -> Arduino 
Bzw. im Nachhinein: -> PIO Home -> Boards -> Suchen und Auswählen (-> platform.ini wird das Board eingetragen)

#### Bibliotheken hinzufügen 
1. Arduino IDE: 
- Werkzeuge -> Bibliotheken verwalten .. -> Suchen und installieren 
2. Platform IO: 
- PIO Home -> Libraries -> Suchen -> Add to Project -> Projektnamen auswählen -> Add

#### Richtigen Port auswählen 
1. Arduino IDE: 
- Werkzeuge -> Port 
2. PlatformIO:
- Mittiges Symbol mit Stecker -> Klicken -> Port evtl. ändern

#### Serieller Monitor öffnen 
1. Arduino IDE: 
- Werkzeuge -> Serieller Monitor 
2. PlatformIO: 
- General -> Monitor bzw. Upload und Monitor (Code wird hochgeladen und der Monitor wird geöffnet)

#### Hochladen Programmcode 
Arduino IDE: 
- mit dem Pfeil -> kannst du das Programm hochladen bzw. Sketch -> hochladen 

Visual Studio Code: 
- PlatformIO-Icon -> Project Tasks -> General -> Upload 

## Code aus dem GitLab wieder auf den ESP laden 
Du benötigst:
- USB-Kabel, PC, Programmcode (GitLab)

Zuerst musst du den Code herunterladen und in einem Ordner speichern.
Achtung! Nutzt du die Arduino IDE, so brauchst du den Code aus dem "Arduino IDE"-Pfad (Eine Datei davon ist eine .ino-Datei). Bei Visual Studio mit PlatformIO den Code aus dem Pfad "PlatformIO"(Eine Daei davon ist eine platformio.ini-Datei)
Danach musst du sicherstellen, dass du eine geeignete Software besitzt (Arduino IDE bzw. Visual Studio Code mit PlatformIO).
Wenn du diese nicht hast, dann schau in "Software für Programm-Code" nach, wie und wo du diese findest. 
Als dritten Schritt öffnest du nun dein Programm und öffnest den Ordner mit dem Code. 

Arduino IDE: 
- Datei -> Öffnen .. 
- Arduinoprogramm "DeinProgramm".ino -> öffnen

Visual Studio Code: 
- PlatformIO-Icon -> PIO Home -> Open -> Open Project 
- Ordner suchen, auswählen -> open 


Nun das hochladen auf den ESP32
- Stelle fest, dass der ESP32 an deinem PC angeschlossen ist und das Batteriefach aus ist 
Hochladen funktioniert folgend: 
Arduino IDE: 
- mit dem Pfeil -> kannst du das Programm hochladen bzw. Sketch -> hochladen 

Visual Studio Code: 
- PlatformIO-Icon -> Project Tasks -> General -> Upload

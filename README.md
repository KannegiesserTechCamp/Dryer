<img src="images/logo.svg" alt="Logo" width="1000"/>

# Tech-Camp: Kannegiesser

Herzlich willkommen zum Tech-Camp bei Kannegiesser! Nachdem du in den ersten beiden Tagen in Zusammenarbeit mit der Ausbildungs- und Elektrowerkstadt deinen Trockner gebaut hast, werden wir uns auf eine Reise in die faszinierende Welt der Programmierung begeben und uns einem ganz besonderen Projekt widmen - der Programmierung deines Trockners. 

Gemeinsam werden wir den Prozess durchlaufen, von der Einrichtung der notwendigen Software und Treiber auf deinem Windows-System bis hin zur Implementierung des Codes, der unseren Trockner zum Leben erweckt. Du wirst lernen, wie man Visual Studio Code einrichtet, die notwendigen Plugins installiert und die Treiber konfiguriert, die für unser Projekt benötigt werden. 

Egal, ob du ein erfahrener Programmierer bist oder gerade erst anfängst, das Tech-Camp bietet eine großartige Gelegenheit, praktische Erfahrungen zu sammeln und deine Fähigkeiten zu erweitern. Wir freuen uns darauf, dich bei dieser spannenden Reise zu begleiten! 

# Anleitung zur Einrichtung von Visual Studio Code, Plugins und Treibern unter Windows
In dieser Anleitung werden wir Schritt für Schritt durch den Prozess der Einrichtung und Konfiguration von Visual Studio Code gehen, einschließlich der Installation der notwendigen Plugins und Treiber. Diese Anleitung ist sowohl für Anfänger als auch für erfahrene Benutzer gedacht und soll dazu beitragen, dass du schnell mit deiner Programmierarbeit beginnen kannst. Lass uns anfangen! 

### Bauteile

- Trockner
  - ESP32 WROOM 32 240MHz, 320KB RAM, 4MB Flash
  - Batteriefach mit 3x AA
  - H-Brücke
  - LED-Streifen

#### Zusätzlich wirst du zum Erstellen des Programms benötigen:

- USB-A Kabel mit USB-Micro-B (alte Ladekabel für z.B. Android-Handys)
- Laptop mit [Visual Studio](https://code.visualstudio.com/) Code mit [PlatformIO](https://platformio.org/)-Erweiterung

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

## PlatformIO Plugin

### Installation

1. Öffne Visual Studio Code.

2. Klicke auf das quadratische Symbol in der linken Seitenleiste, um den "Extensions"-Bereich zu öffnen.

3. Gib in das Suchfeld "PlatformIO" ein und suche nach dem entsprechenden Plugin.

4. Klicke auf "Installieren", um das PlatformIO-Plugin zu installieren.

5. Nachdem die Installation erfolgreich abgeschlossen wurde, starte Visual Studio Code neu.

6. Warte, bis alles automatisch konfiguriert worden ist.

## USB-Treiber NodeMCU CP2102 (ESP 32)

### Installation

1. Lade den USB-Treiber: CP2102 von der offiziellen Silicon Labs-Website für dein Betriebssystem herunter: [Silicon Labs Treiberseite](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)

2. Suche die heruntergeladene Datei in deinem Verzeichnis, klicke diese mit einem Rechtsklick an und wähle „Alle extrahieren“ aus, um die Datei zu entpacken.

3. Navigiere in den entpackten Ordner und suche nach der „silabser.inf“ Datei.

4. Klicke nun mit der rechten Maustaste auf die „silabser.inf“ Datei und wähle „Installieren“ aus.

5. Folge nun dem Installationssetup, bis die Treiber erfolgreich installiert wurde.

### Installation Testen (Optional):

1. Öffne den Windows Geräte-Manager, indem du in der Windows-Suche "Geräte-Manager" eingibst.

2. In der Kategorie „Anschlüsse (COM & LPT)" findest du nun den "Silicon Labs CP210x USB to UART Bridge". Solltest du diesen nicht sehen, ist bei der Treiberinstallation etwas schiefgelaufen, springe dann Abschnitt USB-Treiber installieren und führe die Schritte erneut aus.

## Repository

### Download

1. Öffne deinen Webbrowser und besuche das folgende Github Repository:

    [https://github.com/KannegiesserTechCamp/Dryer](https://github.com/KannegiesserTechCamp/Dryer)

2. Wenn du einen anderen Branch auswählen willst, klicke auf „main“ und wähle diesen in dem Dropdown Menü aus.

3. Zum Download drücke auf den grünen Button „Code“ und wähle „Download ZIP“ aus.

### Entpacken

1. Suche die heruntergeladene Datei in deinem Verzeichnis, klicke diese mit einem Rechtsklick an und wähle „Alle extrahieren“ aus, um die Datei zu entpacken.

## Funktionstest des ESP32 (Mikro Controller)

1. Starte Visual Studio Code und öffne das PlatformIO Plugin (Seitenleiste Links).

2. Wähle unter Quick Access „Open“ aus, klicke auf „Open Project“ und wähle deinen Projektordner (z.B. “Dryer-main”) aus. (Standartmäßig ist das Projekt im Downloadordner zu finden.)
   Diese Einrichtung kann einen Moment dauern.

3. Öffne nun wieder das PlatformIO Plugin und führe links im Reiter einen „Full Clean“ durch.

4. Optional für den Main Branch:

   Daraufhin wähle links im Reiter „PROJECT TASKS“ den Punkt „Build Filesystem Image“ aus.

   Nachdem erfolgreichen beenden des Schrittes wähle links im Reiter „Upload Filesystem Image“ aus und warte bis im Terminal „SUCCESS“ steht.

   Nun wähle links im Reiter „Build“ aus und warte sie ebenfalls bis im Terminal „SUCCESS“ steht.

   Nun wähle links im Reiter „Upload and Monitor“ aus und warte sie ebenfalls bis im Terminal „SUCCESS“ steht.

## Ein tieferer Einblick in den Code

Unser Code besteht hauptsächlich aus einer "Main"-Datei. Diese Datei enthält immer ein Setup, in dem die Outputs/Inputs definiert werden, und eine Schleife (Loop), die ständig durchlaufen wird, solange Spannung anliegt. Im Setup können auch Methoden und Funktionen aufgerufen werden, die nicht ständig wiederholt werden müssen.

Die .h und .cpp Dateien spielen eine wichtige Rolle in unserer Code-Struktur. Wir haben die Funktionen und den Setup-Code des Trockners sowie der LED in separate .cpp Dateien ausgelagert, um die "Main"-Datei übersichtlicher zu gestalten. Die .h Datei ist eine Besonderheit in der C-Programmierung und stellt sicher, dass die "Main"-Datei weiß, welche Funktionen sie aus den .cpp Dateien verwenden darf.

In der "main.cpp" legen wir im Setup einen sogenannten Async-Webserver an. Dieser Webserver stellt unseren Server für die Website dar, die wir später aufrufen können. Er erhält zusätzlich Informationen zu unserem HTML-Code, CSS und unseren Bilddateien für die Website, sodass der Server diese Website "bauen" kann. Eine weitere Funktion des Webservers ist es, bei Erhalt eines bestimmten Pfades (ausgelöst durch die Buttons der Oberfläche) die entsprechende Funktion unseres Trockners bzw. unserer LED aufzurufen.

Der HTML-Code beschreibt die Elemente der Seite und stellt sicher, dass der richtige Pfad aufgerufen wird, wenn ein Button geklickt wird. Der CSS-Teil ist für das grafische Design der Website zuständig. Beide Dateien sind im "data"-Ordner ausgelagert und befinden sich auf der SD-Karte des ESPs. Dort werden auch alle Bilder gespeichert.

Die bereitgestellte Quelle enthält den Code für die "main.cpp"-Datei, einschließlich der Einbindung externer Bibliotheken, Definition von Konstanten und lokalen Variablen sowie dem Code zum Öffnen des Dateisystems.

## Router Verbindung einrichten

### WLAN-Konfiguration

Trage die richtige SSID (dies ist der Name deines Routers) und das Passwort des Routers in der “src/main.cpp” Datei ein. (Der Abschnitt befindet sich in Zeile 23 bis Zeile 27 in der Datei)

<img src="images/code_snippet.png" alt="code_snippel" width="1000"/>

### FritzBox-Oberfläche (optional)

1. Öffne einen Webbrowser auf deinem Computer oder einem anderen Gerät, das mit dem gleichen Netzwerk wie deine FritzBox verbunden ist.
2. Gib die IP-Adresse deiner FritzBox in die Adressleiste des Browsers ein und drücke die Eingabetaste. Die Standard-IP-Adresse der FritzBox lautet normalerweise "192.168.178.1". Überprüfe die Dokumentation deiner FritzBox, wenn du dir nicht sicher bist. 
3. Gib das FritzBox-Passwort ein, um dich in die FritzBox-Oberfläche einzuloggen. Dieses Passwort findest du normalerweise auf einem Aufkleber auf deiner FritzBox oder in der Dokumentation. 
4. Navigiere in der FritzBox-Oberfläche zu den Heimnetz-Einstellungen und klicke auf den Punkt Netzwerk. Der genaue Pfad kann je nach FritzBox-Modell variieren. Du solltest jedoch eine Option finden, die dir die Liste der aktuell verbundenen Geräte anzeigt. 
5. In der Liste der verbundenen Geräte suche nach dem Eintrag für deinen ESP32. Der Name oder die IP-Adresse des ESP32 sollte dort aufgeführt sein, wenn er erfolgreich mit der FritzBox verbunden ist.
<img src="images/FritzBox_Dashboard.png" alt="Dashboard" width="1000"/>

6. Um eine feste IPv4 Adresse festzulegen, drücke bitte auf den Stift des entsprechenden ESPs und suche nach dem Punkt “Adresse im Heimnetz (IP-Adressen” und wähle „Diesem Netzwerkgerät immer die gleiche IPv4-Adresse zuweisen.“ aus und setze hier bitte den Haken. Hierdurch bekommt das Gerät jedes Mal die gleiche IPv4 Adresse zugewiesen.
<img src="images/FritzBox_IPv4.png" alt="IPv4" width="1000"/>

### Überprüfe die Serielle Ausgabe (optional)

Wenn du während der Programmierung des ESP32 die serielle Ausgabe für Debugging-Zwecke aktiviert hast, kannst du auch die serielle Ausgabe überprüfen, um den Verbindungsstatus zu überprüfen. Wenn der ESP32 erfolgreich eine Verbindung zu deinem WLAN herstellt, sollte dies in der seriellen Ausgabe angezeigt werden.

# C++ Programmierung:
Die folgenden Beispiel können mit hilfe des Online Compilers von [Programiz](https://www.programiz.com/cpp-programming/online-compiler/) getestes werden.
Weitere Materialien zur Programmierung sind in dem folgenden Verzeichniss: [einführung cpp](https://github.com/KannegiesserTechCamp/einfuerung_cpp) verfügbar.


## Digitaler Trockner

### Code

```cpp
// Einbinden der Standardbibliotheken für Ein-/Ausgabe und Zeichenkettenverarbeitung
// Einbinden der Standardbibliotheken für Ein-/Ausgabe und Zeichenkettenverarbeitung
// 'stdio.h' ist für grundlegende Ein- und Ausgabeoperationen wie printf und scanf.
// 'string.h' ist für Operationen auf Zeichenketten (Strings) wie strcpy.
#include <stdio.h>
#include <string.h>

// Die main-Funktion ist der Einstiegspunkt für das Programm.
int main() {
    // Deklaration der Variablen
    // 'startup' und 'prog' sind Ganzzahlvariablen (int), 'progname' 
    //ist ein Zeichenkettenarray (char array).
    int startup;
    int prog;
    char progname[124];
    
    // Ausgabe der Optionen für den Benutzer
    // printf wird verwendet, um Text auf dem Bildschirm auszugeben.
    printf("Tippe:\n\t\t (0) zum Beenden \n\t\t (1) zum starten \n\t\t (2) für neues Programm \n");
    
    // Einlesen der Benutzereingabe
    // scanf wird verwendet, um die Eingabe des Benutzers zu lesen. '%i' bedeutet, 
    //dass eine Ganzzahl erwartet wird.
    scanf("%i", &startup);
    
    // Überprüfung der Benutzereingabe und Ausführung des entsprechenden Codes
    // Die if-else-Anweisungen überprüfen den Wert von 'startup' und 
    //führen den entsprechenden Codeblock aus.
    if(startup == 0){
        printf("Du hast dich für das Beenden des Trockners entschieden\n");
    }
    else if(startup == 1){
        printf("Der Trockner wird hochgefahren\n");
        printf("\t\t3\n\t\t2\n\t\t1\n\t\t0\n");
        printf("Trockner gestartet\n");
        printf("bereit zum Trocknen\n");
        
        printf("Waele eines der folden Programme zum Trocknen aus:\n");
        printf("\t(1) \t schnelles Trocknen\n");
        printf("\t(2) \t schleuder Trauma\n");
        printf("\t(3) \t Presskuchen\n");
        
        scanf("%i", &prog);
        printf("Du hast dich für das Folgenden Programm entschieden");
        if(prog == 1){
            // Kopieren des Programmnamens in die Variable 'progname'
            strcpy(progname, "schnelles Trocknen");  
        } else if(prog == 2){
            strcpy(progname, "schleuder Trauma");
        }else if(prog == 3){
            strcpy(progname, "Presskuchen");
        }
    }
    else if(startup == 2){
        printf("Du hast dich für das neue Programm entschieden\n");
        printf("gebe im folgenden den namen deines neuen Programms ein\n");
        // Einlesen des neuen Programmnamens
        scanf("%s", &progname);  
        
        printf("Das Programm mit dem Namen: \n\t %s \nwurde erstellt\n", progname);
    }
    else{
        printf("Der hast leider keine der Möglichen Eingaben (0), (1) gemacht \n");
    }
    
    printf("Der Trockner wird herruntergefahren und beendet");
    return 0;  // Beendet die main-Funktion und gibt den Wert 0 zurück.
}
```
Dieser Code stellt ein einfaches Menü zur Verfügung, mit dem der Benutzer verschiedene Optionen für einen digitalen Trockner auswählen kann. Der Benutzer kann den Trockner starten und ein Trockenprogramm auswählen, ein neues Programm erstellen oder den Trockner beenden. Die Auswahl des Benutzers wird über die Standard-Eingabe eingelesen und entsprechend verarbeitet. Der Code verwendet grundlegende Konzepte der C-Programmierung wie Variablendeklaration, Ein- und Ausgabe, Kontrollstrukturen (if-else-Anweisungen) und Zeichenkettenoperationen.

Zum Testen: in den Online Compilers von [Programiz](https://www.programiz.com/cpp-programming/online-compiler/) kopieren.

## Ausführliche Einführung

Dieses Programm stellt ein einfaches Menü zur Verfügung, mit dem der Benutzer verschiedene Optionen für einen digitalen Trockner auswählen kann. Es verwendet grundlegende Konzepte der C-Programmierung wie Variablendeklaration, Ein- und Ausgabe, Kontrollstrukturen (if-else-Anweisungen) und Zeichenkettenoperationen.

### Variablendeklaration

In C müssen alle Variablen vor ihrer Verwendung deklariert werden. Eine Variablendeklaration gibt den Variablennamen und den Typ an. Zum Beispiel:

```cpp
int startup;
int prog;
char progname[124];
```

In diesem Code werden zwei Ganzzahlvariablen (`startup` und `prog`) und ein Zeichenkettenarray (`progname`) deklariert.

### Ein- und Ausgabe

Die Funktionen `printf` und `scanf` werden für die Ein- und Ausgabe verwendet. `printf` wird verwendet, um Text auf dem Bildschirm auszugeben, und `scanf` wird verwendet, um die Eingabe des Benutzers zu lesen.

### Kontrollstrukturen

Die if-else-Anweisungen werden verwendet, um zu überprüfen, ob eine Bedingung erfüllt ist, und um den entsprechenden Codeblock auszuführen. Zum Beispiel:

```cpp
if(startup == 0){
    printf("Du hast dich für das Beenden des Trockners entschieden\n");
}
else if(startup == 1){
    // Code für den Fall, dass 'startup' gleich 1 ist
}
else{
    // Code für den Fall, dass keine der vorherigen Bedingungen erfüllt ist
}
```

### Zeichenkettenoperationen

Die Funktion `strcpy` wird verwendet, um eine Zeichenkette in eine andere zu kopieren. Zum Beispiel:

```cpp
strcpy(progname, "schnelles Trocknen");
```

In diesem Code wird der Text "schnelles Trocknen" in die Variable `progname` kopiert.

## Wäscheverwaltung
Zum Testen: in den Online Compilers von [Programiz](https://www.programiz.com/cpp-programming/online-compiler/) kopieren.

### Code

```cpp
// Die Standardbibliothek 'stdio.h' wird eingebunden, um grundlegende Ein-/Ausgabeoperationen wie printf und scanf zu ermöglichen.
#include <stdio.h>

// Die Funktion 'waschen' nimmt einen Charakter 'farbe' als Parameter an. Dieser Charakter repräsentiert die Farbe der Wäsche, die gewaschen werden soll.
void waschen(char farbe){
    // Die if-else-if-Anweisung überprüft, welche Farbe die Wäsche hat, und gibt eine entsprechende Nachricht aus.
    if(farbe == 'b'){
        printf("Blaue Waesche wird gewaschen\n");
    }else if(farbe == 'r'){
        printf("Rote Waesche wird gewaschen\n");
    }else if(farbe == 'g'){
        printf("Gruene Waesche wird gewaschen\n");
    }else if(farbe == 'w'){
        printf("Weisse Wasche wird gewaschen\n");
    }else if(farbe == 's'){
        printf("Schwarze Wasche wird gewaschen\n");
    }else{
        // Wenn keine der obigen Bedingungen erfüllt ist (d.h., die Farbe ist nicht blau, rot, grün, weiß oder schwarz), wird angenommen, dass die Wäsche bunt ist.
        printf("\t\t Diese Farbe ist unbekannt\n");
        printf("\t\t Die Bunte Waesche wird gewaschen\n");
    }
}

// Die main-Funktion ist der Einstiegspunkt für das Programm. In C-Programmen muss es immer eine main-Funktion geben.
int main() {
    // Deklaration der Variablen
    // 'exit' ist eine boolsche Variable, die bestimmt, ob die Hauptschleife des Programms weiterlaufen soll.
    // 'anzahl' ist eine Ganzzahlvariable, die die Anzahl der Wäschestapel speichert.
    // 'fertig' ist eine Ganzzahlvariable, die verwendet wird, um zu überprüfen, ob der Benutzer weitere Stapel hinzufügen möchte.
    // 'farbe' ist eine Zeichenvariable (char), die die Farbe der Wäsche speichert.
    bool exit = true;
    int anzahl;
    int fertig;
    char farbe;
    
    // Ausgabe der Einführungsnachricht
    printf("Dies ist eine Aufnahme Stelle fuer die Verwaltung von Waesche\n");
    
    // Hauptschleife des Programms. Sie läuft so lange, bis der Benutzer entscheidet, dass keine weiteren Stapel hinzugefügt werden sollen.
    while(exit){
        // Aufforderung zur Eingabe der Anzahl und Farbe der Wäschestapel
        printf("Gebe im folgenden Format: Anzahl(int) Farbe(char) an, was fuer Waesche angeliefert wurde\n");
        scanf("%i %c", &anzahl, &farbe);
        
        // Schleife zum Waschen jedes Wäschestapels
        for(int i=0; i< anzahl; i++){
            printf("Stapel Nr. %i  ", i+1);
            waschen(farbe);
        }
        
        // Aufforderung zur Eingabe, ob weitere Stapel verteilt werden sollen
        printf("Sollen weitere Stapel verteilt werden ? Nein (0), Ja (1)\n");
        scanf("%i", &fertig);
        if(fertig == 0){
            exit = false;
        }
    }
    
    // Ausgabe der Abschlussnachricht
    printf("Wir haben es geschafft, alle Stapel konnten sortiert werden");
    
    return 0;  // Beendet die main-Funktion und gibt den Wert 0 zurück. In C bedeutet ein Rückgabewert von 0 in der main-Funktion, dass das Programm erfolgreich ausgeführt wurde.
}
```

Dieser Code stellt ein einfaches Menü zur Verfügung, mit dem der Benutzer die Anzahl und Farbe von Wäschestapeln eingeben kann, die gewaschen werden sollen. Der Benutzer kann dann angeben, ob weitere Stapel verteilt werden sollen oder nicht. Der Code verwendet grundlegende Konzepte der C-Programmierung wie Variablendeklaration, Ein- und Ausgabe, Kontrollstrukturen (if-else-Anweisungen und Schleifen) und Funktionen.

## Ausführliche Einführung

Dieses Programm stellt ein einfaches Menü zur Verfügung, mit dem der Benutzer verschiedene Optionen für einen digitalen Trockner auswählen kann. Es verwendet grundlegende Konzepte der C-Programmierung wie Variablendeklaration, Ein- und Ausgabe, Kontrollstrukturen (if-else-Anweisungen) und Funktionen.

### Variablendeklaration

In C müssen alle Variablen vor ihrer Verwendung deklariert werden. Dies gibt den Variablennamen und den Typ an. Zum Beispiel:

```cpp
bool exit = true;
int anzahl;
int fertig;
char farbe;
```

In diesem Code werden eine boolsche Variable (`exit`), zwei Ganzzahlvariablen (`anzahl` und `fertig`) und eine Zeichenvariable (`farbe`) deklariert.

### Ein- und Ausgabe

Die Funktionen `printf` und `scanf` werden für die Ein- und Ausgabe verwendet. `printf` wird verwendet, um Text auf dem Bildschirm auszugeben, und `scanf` wird verwendet, um die Eingabe des Benutzers zu lesen.

### Kontrollstrukturen

Die if-else-Anweisungen werden verwendet, um zu überprüfen, ob eine Bedingung erfüllt ist, und um den entsprechenden Codeblock auszuführen. Zum Beispiel:

```c
if(farbe == 'b'){
    printf("Blaue Waesche wird gewaschen\n");
}else if(farbe == 'r'){
    printf("Rote Waesche wird gewaschen\n");
}else if(farbe == 'g'){
    printf("Gruene Waesche wird gewaschen\n");
}else{
    printf("\t\t Diese Farbe ist unbekannt\n");
    printf("\t\t Die Bunte Waesche wird gewaschen\n");
}
```

### Funktionen

Eine Funktion ist ein Block von Code, der eine bestimmte Aufgabe ausführt. In diesem Programm gibt es zwei Funktionen: `main` und `waschen`. Die `main`-Funktion ist der Einstiegspunkt des Programms, während die `waschen`-Funktion dazu dient, die Wäsche basierend auf ihrer Farbe zu waschen.
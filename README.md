<img src="images/logo.svg" alt="Logo" width="1000"/>

# Tech-Camp: Kannegiesser

Herzlich willkommen zum Tech-Camp bei Kannegiesser! Nachdem du in den ersten beiden Tagen in Zusammenarbeit mit der Ausbildungs- und Elektrowerkstatt deinen Trockner gebaut hast, werden wir uns auf eine Reise in die faszinierende Welt der Programmierung begeben und uns einem ganz besonderen Projekt widmen - der Programmierung deines Trockners. 

Gemeinsam werden wir den Prozess durchlaufen, von der Einrichtung der notwendigen Software und Treiber auf deinem Windows-System bis hin zur Implementierung des Codes, der unseren Trockner zum Leben erweckt. Du wirst lernen, wie man Visual Studio Code einrichtet, die notwendigen Plugins installiert und die Treiber konfiguriert, die für unser Projekt benötigt werden. 

Egal, ob du ein erfahrener Programmierer bist oder gerade erst anfängst, das Tech-Camp bietet eine großartige Gelegenheit, praktische Erfahrungen zu sammeln und deine Fähigkeiten zu erweitern. Wir freuen uns darauf, dich bei dieser spannenden Reise zu begleiten!

# WithoutUI
In diesem Zweig findest du eine Testsoftware, die dir hilft zu überprüfen, ob dein Trockner richtig funktioniert. Lass uns kurz erklären, warum es so wichtig ist, in der Softwareentwicklung Testumgebungen zu haben und Tests durchzuführen.

Das Testen in sogenannten “abgespeckten” Umgebungen, die man auch als “Staging” oder “Pre-Production” Umgebungen bezeichnet, ist ein super wichtiger Teil beim Entwickeln von Software. Hier sind ein paar Gründe, warum das so ist:

1. Fehler finden: Wenn du die Software in einer Umgebung testest, die so ähnlich wie möglich zur echten Umgebung ist, in der die Software später laufen soll, kannst du Fehler und Probleme finden und beheben, bevor die Software wirklich benutzt wird. Das hilft dabei, dass die Software nicht plötzlich stehen bleibt und die Leute, die sie benutzen, zufriedener sind.

2. Sicherheitstests: In abgespeckten Umgebungen kannst du Tests durchführen, um sicherzustellen, dass die Software sicher vor Angriffen aus dem Internet ist. Das ist besonders wichtig für Programme, die mit sensiblen Daten arbeiten.

3. Qualität sichern: Wenn du in einer abgespeckten Umgebung testest, können Teams, die sich um die Qualität der Software kümmern, die Software genau unter die Lupe nehmen. So können sie sicherstellen, dass alles so funktioniert wie es soll und dass die Software das macht, was sie machen soll.

Zusammengefasst hilft das Testen in abgespeckten Umgebungen dabei, dass die Qualität der Software besser wird, Risiken kleiner werden und am Ende ein besseres Produkt für die Leute entsteht, die es benutzen.

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
- Laptop mit [Visual Studio Code](https://code.visualstudio.com/) mit [PlatformIO](https://platformio.org/)-Erweiterung

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

## Funktionstest des ESP32 (Mikro Controller)

1. Starte Visual Studio Code und öffne das PlatformIO Plugin (Seitenleiste links).

2. Wähle unter Quick Access „Open“ aus, klicke auf „Open Project“ und wähle deinen Projektordner (z.B. “Dryer-main”) aus (standardmäßig ist das Projekt im Downloadordner zu finden).
   Diese Einrichtung kann einen Moment dauern.

3. Öffne nun wieder das PlatformIO Plugin und führe links im Reiter einen „Full Clean“ durch.

4. Optional für den Main Branch:

   Daraufhin wähle links im Reiter „PROJECT TASKS“ den Punkt „Build Filesystem Image“ aus.

   Nach dem erfolgreichen Beenden des Schrittes wähle links im Reiter „Upload Filesystem Image“ aus und warte bis im Terminal „SUCCESS“ steht.

   Nun wähle links im Reiter „Build“ aus und warte ebenfalls bis im Terminal „SUCCESS“ steht.

   Nun wähle links im Reiter „Upload and Monitor“ aus und warte ebenfalls bis im Terminal „SUCCESS“ steht.

## Ein tieferer Einblick in den Code

Unser Code besteht hauptsächlich aus einer "Main"-Datei. Diese Datei enthält immer ein Setup, in dem die Outputs/Inputs definiert werden, und eine Schleife (Loop), die ständig durchlaufen wird, solange Spannung anliegt. Im Setup können auch Methoden und Funktionen aufgerufen werden, die nicht ständig wiederholt werden müssen.

Die .h und .cpp Dateien spielen eine wichtige Rolle in unserer Code-Struktur. Wir haben die Funktionen und den Setup-Code des Trockners sowie der LED in separate .cpp Dateien ausgelagert, um die "Main"-Datei übersichtlicher zu gestalten. Die .h Datei ist eine Besonderheit in der C-Programmierung und stellt sicher, dass die "Main"-Datei weiß, welche Funktionen sie aus den .cpp Dateien verwenden darf.

In der "main.cpp" legen wir im Setup einen sogenannten Async-Webserver an. Dieser Webserver stellt unseren Server für die Website dar, die wir später aufrufen können. Er erhält zusätzlich Informationen zu unserem HTML-Code, CSS und unseren Bilddateien für die Website, sodass der Server diese Website "bauen" kann. Eine weitere Funktion des Webservers ist es, bei Erhalt eines bestimmten Pfades (ausgelöst durch die Buttons der Oberfläche) die entsprechende Funktion unseres Trockners bzw. unserer LED aufzurufen.

Der HTML-Code beschreibt die Elemente der Seite und stellt sicher, dass der richtige Pfad aufgerufen wird, wenn ein Button geklickt wird. Der CSS-Teil ist für das grafische Design der Website zuständig. Beide Dateien sind im "data"-Ordner ausgelagert und befinden sich auf der SD-Karte des ESPs. Dort werden auch alle Bilder gespeichert.

Die bereitgestellte Quelle enthält den Code für die "main.cpp"-Datei, einschließlich der Einbindung externer Bibliotheken, Definitionen von Konstanten und lokalen Variablen sowie dem Code zum Öffnen des Dateisystems.

## Router Verbindung einrichten

### WLAN-Konfiguration

Trage die richtige SSID (dies ist der Name deines Routers) und das Passwort des Routers in der “src/main.cpp” Datei ein. (Der Abschnitt befindet sich in Zeile 23 bis Zeile 27 in der Datei)

<img src="images/code_snippet.png" alt="code_snippel" width="1000"/>

### FritzBox-Oberfläche (optional)

1. Öffne einen Webbrowser auf deinem Computer oder einem anderen Gerät, das mit dem gleichen Netzwerk wie deine FritzBox verbunden ist.
2. Gib die IP-Adresse deiner FritzBox in die Adressleiste des Browsers ein und drücke die Eingabetaste. Die Standard-IP-Adresse der FritzBox lautet normalerweise "192.168.178.1". Überprüfe die Dokumentation deiner FritzBox, wenn du dir nicht sicher bist. 
3. Gib das FritzBox-Passwort ein, um dich in die FritzBox-Oberfläche einzuloggen. Dieses Passwort findest du normalerweise auf einem Aufkleber auf deiner FritzBox oder in der Dokumentation. 
4. Navigiere in der FritzBox-Oberfläche zu den Heimnetz-Einstellungen und klicke auf den Punkt "Netzwerk". Der genaue Pfad kann je nach FritzBox-Modell variieren. Du solltest jedoch eine Option finden, die dir die Liste der aktuell verbundenen Geräte anzeigt. 
5. In der Liste der verbundenen Geräte suche nach dem Eintrag für deinen ESP32. Der Name oder die IP-Adresse des ESP32 sollte dort aufgeführt sein, wenn er erfolgreich mit der FritzBox verbunden ist.
<img src="images/FritzBox_Dashboard.png" alt="Dashboard" width="1000"/>

6. Um eine feste IPv4 Adresse festzulegen, drücke bitte auf den Stift des entsprechenden ESPs und suche nach dem Punkt “Adressen im Heimnetz (IP-Adressen)” und wähle „Diesem Netzwerkgerät immer die gleiche IPv4-Adresse zuweisen.“ aus und setze hier bitte den Haken. Hierdurch bekommt das Gerät jedes Mal die gleiche IPv4 Adresse zugewiesen.
<img src="images/FritzBox_IPv4.png" alt="IPv4" width="1000"/>

### Überprüfe die Serielle Ausgabe (optional)

Wenn du während der Programmierung des ESP32 die serielle Ausgabe für Debugging-Zwecke aktiviert hast, kannst du auch die serielle Ausgabe überprüfen, um den Verbindungsstatus zu überprüfen. Wenn der ESP32 erfolgreich eine Verbindung zu deinem WLAN herstellt, sollte dies in der seriellen Ausgabe angezeigt werden.
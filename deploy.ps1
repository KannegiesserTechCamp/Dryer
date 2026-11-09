<#
.SYNOPSIS
  Vollautomatisches Deploy-Skript für MicroPython-Trockner (ESP32)
.DESCRIPTION
  Führt in einer Sequenz aus:
  1. Prüft ob mpremote erreichbar
  2. Flasiert Firmware (falls vorhanden)
  3. Kopiert Python-Quelldateien auf den ESP32
  4. Erstellt Web-Verzeichnis und kopiert Web-Assets
  5. Startet ESP32 neu

  Verwendung: .\deploy.ps1 [-Port COMx]
#>

param(
    [string]$Port = "COM3"
)

$ErrorActionPreference = "Stop"
$projectDir = Get-Location

Write-Host "=== MicroPython Dryer Deploy ===" -ForegroundColor Cyan
Write-Host "Projektordner: $projectDir"
Write-Host "ESP32-Port: $port"
Write-Host ""

# ---------------------------------------------------------------------------
# 1. Prüfen ob mpremote erreichbar ist
# ---------------------------------------------------------------------------
Write-Host "[1/5] Prüfe mpremote..." -ForegroundColor Yellow
try {
    & python -m mpremote connect port:$port fs ls > $null 2>&1
    if ($LASTEXITCODE -ne 0) {
        Write-Host "   FEHLER: mpremote nicht erreichbar auf Port $port!" -ForegroundColor Red
        exit 1
    }
    Write-Host "   mpremote bereit." -ForegroundColor Green
}
catch {
    Write-Host "   FEHLER: $PSItem" -ForegroundColor Red
    exit 1
}

# ---------------------------------------------------------------------------
# 2. MicroPython-Firmware flashen (falls vorhanden)
# ---------------------------------------------------------------------------
# Write-Host "[2/5] Prüfe Firmware..." -ForegroundColor Yellow
# $firmwareFile = Join-Path $projectDir "firmware.bin"
# if (Test-Path $firmwareFile) {
#     Write-Host "   Firmware-Datei gefunden: firmware.bin" -ForegroundColor Cyan
#     Write-Host "   Flashe Firmware (löscht den ESP32 vollständig)..." -ForegroundColor Cyan
#     & python -m esptool --port $port --baud 460800 write_flash -z 0x1000 $firmwareFile
#     if ($LASTEXITCODE -ne 0) {
#         Write-Host "   FEHLER beim Flashen der Firmware!" -ForegroundColor Red
#         exit 1
#     }
#     Write-Host "   Firmware erfolgreich geflasht." -ForegroundColor Green
# }
# else {
#     Write-Host "   Keine firmware.bin im Projektordner – übersprungen." -ForegroundColor Gray
#     Write-Host "   (Falls nötig, lade MicroPython-Firmware von https://micropython.org/download/esp32/ herunter)" -ForegroundColor Gray
# }

# ---------------------------------------------------------------------------
# 3. Python-Quelldateien kopieren
# ---------------------------------------------------------------------------
Write-Host "[3/5] Kopiere Python-Quelldateien..." -ForegroundColor Yellow
$pyFiles = @("config.py", "dryer.py", "led.py", "web_server.py", "main.py")
foreach ($file in $pyFiles) {
    if (-not (Test-Path $file)) {
        Write-Host "   FEHLER: $file nicht gefunden!" -ForegroundColor Red
        exit 1
    }
    & python -m mpremote connect port:$port fs cp $file ":$file"
    if ($LASTEXITCODE -ne 0) {
        Write-Host "   FEHLER beim Kopieren von $file!" -ForegroundColor Red
        exit 1
    }
    Write-Host "   $file kopiert." -ForegroundColor Green
}

# ---------------------------------------------------------------------------
# 4. Web-Verzeichnis und Assets kopieren
# ---------------------------------------------------------------------------
Write-Host "[4/5] Kopiere Web-Assets..." -ForegroundColor Yellow
& python -m mpremote connect port:$port fs mkdir ":web" 2>$null

$webFiles = @("index.html", "style.css", "logo.png", "Trocknerbutton.png", "LEDbutton.png")
$webDir = Join-Path $projectDir "web"
foreach ($file in $webFiles) {
    $localPath = Join-Path $webDir $file
    if (-not (Test-Path $localPath)) {
        Write-Host "   FEHLER: $localPath nicht gefunden!" -ForegroundColor Red
        exit 1
    }
    & python -m mpremote connect port:$port fs cp $localPath ":web/$file"
    if ($LASTEXITCODE -ne 0) {
        Write-Host "   FEHLER beim Kopieren von $file!" -ForegroundColor Red
        exit 1
    }
    Write-Host "   web/$file kopiert." -ForegroundColor Green
}

# ---------------------------------------------------------------------------
# 5. ESP32 neu starten
# ---------------------------------------------------------------------------
Write-Host "[5/5] Starte ESP32 neu..." -ForegroundColor Yellow
& python -m mpremote connect port:$port reset
if ($LASTEXITCODE -ne 0) {
    Write-Host "   Hinweis: Reset-Befehl gesendet (manueller Reset ggf. nötig)." -ForegroundColor Gray
}
else {
    Write-Host "   ESP32 neu gestartet." -ForegroundColor Green
}

Write-Host ""
Write-Host "=== Deploy abgeschlossen! ===" -ForegroundColor Cyan
Write-Host "Verbinde dich mit WiFi: Trockner-01 (Passwort: Kannegiesser)" -ForegroundColor Cyan
Write-Host "Öffne im Browser: http://192.168.4.1/index.html" -ForegroundColor Cyan

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

  Filesystem-, Firmware-, Datei-, Quelldatei- und Web-Asset-Upload werden
  bei Fehlern bis zu 3x versucht (5 Sekunden Pause zwischen den Versuchen).

  Verwendung: .\deploy.ps1 [-Port COMx]
#>

param(
    [string]$Port = "COM3"
)

$ErrorActionPreference = "Stop"
$projectDir = Get-Location
$esptoolPath = Join-Path $projectDir "ESPTool\esptool.exe"

$MaxAttempts = 3
$RetryDelaySeconds = 5

# ---------------------------------------------------------------------------
# Retry-Helper: führt einen Scriptblock aus, der einen nativen Befehl aufruft.
# Erfolg = $LASTEXITCODE -eq 0 und keine Exception.
# Gibt $true bei Erfolg zurück, $false wenn alle Versuche fehlgeschlagen sind.
# ---------------------------------------------------------------------------
function Invoke-WithRetry {
    param(
        [Parameter(Mandatory)][string]$Name,
        [Parameter(Mandatory)][scriptblock]$Action,
        [int]$MaxAttempts = 3,
        [int]$DelaySeconds = 5
    )

    for ($attempt = 1; $attempt -le $MaxAttempts; $attempt++) {
        $success = $false
        try {
            $global:LASTEXITCODE = 0
            & $Action | Out-Host
            $success = ($LASTEXITCODE -eq 0)
        }
        catch {
            Write-Host "   Ausnahme: $PSItem" -ForegroundColor DarkYellow
            $success = $false
        }

        if ($success) {
            return $true
        }

        if ($attempt -lt $MaxAttempts) {
            Write-Host "   $Name fehlgeschlagen (Versuch $attempt/$MaxAttempts). Neuer Versuch in $DelaySeconds s..." -ForegroundColor DarkYellow
            Start-Sleep -Seconds $DelaySeconds
        }
        else {
            Write-Host "   $Name fehlgeschlagen (Versuch $attempt/$MaxAttempts). Keine weiteren Versuche." -ForegroundColor Red
        }
    }
    return $false
}

Write-Host "=== MicroPython Dryer Deploy ===" -ForegroundColor Cyan
Write-Host "Projektordner: $projectDir"
Write-Host "ESP32-Port: $Port"
Write-Host ""

# ---------------------------------------------------------------------------
# Full Build: Erase Flash → Upload Filesystem → Firmware → Upload Files
# ---------------------------------------------------------------------------
Write-Host "" -ForegroundColor Cyan
Write-Host "=== Full Build Sequenz ===" -ForegroundColor Cyan
Write-Host "1. Erase Flash" -ForegroundColor Cyan
Write-Host "2. Upload Filesystem" -ForegroundColor Cyan
Write-Host "3. Firmware" -ForegroundColor Cyan
Write-Host "4. Upload Files" -ForegroundColor Cyan
Write-Host ""

# ---------------------------------------------------------------------------
# 2.1 Erase Flash
# ---------------------------------------------------------------------------
Write-Host "[FB/1] Lösche ESP32 Flash..." -ForegroundColor Yellow
& $esptoolPath --port $Port erase-flash
if ($LASTEXITCODE -ne 0) {
    Write-Host "   FEHLER beim Löschen des Flash! Full Build abgebrochen." -ForegroundColor Red
    exit 1
}
Write-Host "   Flash erfolgreich gelöscht." -ForegroundColor Green
Write-Host "   Warte auf ESP32-Neustart (2s)..." -ForegroundColor Gray
Start-Sleep -Seconds 2

# ---------------------------------------------------------------------------
# 2.2 Upload Filesystem (spiffs.bin)
# ---------------------------------------------------------------------------
$spiffsFile = Join-Path $projectDir "fs\spiffs.bin"
if (-not (Test-Path $spiffsFile)) {
    Write-Host "   HINWEIS: spiffs.bin nicht gefunden – Filesystem-Schritt übersprungen." -ForegroundColor Gray
    Write-Host ""
} else {
    Write-Host "[FB/2] Lade Filesystem (spiffs.bin)..." -ForegroundColor Yellow
    Write-Host "   Datei: $spiffsFile" -ForegroundColor Gray
    & $esptoolPath --port $port write_flash 0x290000 "$spiffsFile"
    if ($LASTEXITCODE -ne 0) {
        Write-Host "   FEHLER beim Filesystem-Upload! Full Build abgebrochen." -ForegroundColor Red
        exit 1
    }
    Write-Host "   Filesystem erfolgreich hochgeladen." -ForegroundColor Green
    Write-Host ""
}
Write-Host "   Filesystem erfolgreich geflasht." -ForegroundColor Green
Write-Host "   Warte auf ESP32-Neustart (5s)..." -ForegroundColor Gray
Start-Sleep -Seconds 5

# ---------------------------------------------------------------------------
# 2.3 Firmware (installation.exe - muss vorhanden sein, sonst Abbruch) - mit Retry
# ---------------------------------------------------------------------------
$firmwareFile = Join-Path $projectDir "fw\installation.exe"
if (-not (Test-Path $firmwareFile)) {
    Write-Host "   FEHLER: installation.exe nicht gefunden! Full Build abgebrochen." -ForegroundColor Red
    exit 1
}
Write-Host "[FB/3] Flashe Firmware (installation.exe)..." -ForegroundColor Yellow
Write-Host "   Datei: $firmwareFile" -ForegroundColor Gray
$ok = Invoke-WithRetry -Name "Firmware-Flash" -MaxAttempts $MaxAttempts -DelaySeconds $RetryDelaySeconds -Action {
    & "$firmwareFile"
}
if (-not $ok) {
    Write-Host "   FEHLER beim Firmware-Flash! Full Build abgebrochen." -ForegroundColor Red
    exit 1
}
Write-Host "   Firmware erfolgreich geflasht." -ForegroundColor Green
Write-Host "   Warte auf ESP32-Neustart (5s)..." -ForegroundColor Gray
Start-Sleep -Seconds 5

# ---------------------------------------------------------------------------
# 2.4 Upload Files (pytrockner/ rekursiv)
# ---------------------------------------------------------------------------
$pyTrocknerDir = Join-Path $projectDir "pytrockner"
if (-not (Test-Path $pyTrocknerDir)) {
    Write-Host "   FEHLER: Verzeichnis pytrockner/ nicht gefunden! Full Build abgebrochen." -ForegroundColor Red
    exit 1
}
Write-Host "[FB/4] Lade Dateien aus pytrockner/ hoch..." -ForegroundColor Yellow

$script:uploadedFiles = @()

function Upload-Recursive {
    param(
        [string]$localDir,
        [string]$remoteDir = ""
    )
    $items = Get-ChildItem -Path $localDir
    foreach ($item in $items) {
        $localPath = Join-Path $localDir $item.Name
        $remotePath = if ($remoteDir) { "/$remoteDir/$($item.Name)" } else { "/$($item.Name)" }

        if ($item.PSIsContainer) {
            & python -m mpremote connect port:$port fs mkdir ":$remotePath" 2>$null
            Upload-Recursive -localDir $localPath -remoteDir $item.Name
        } elseif ($item.Name -match "\.(py|json|txt|mpy)$") {
            & python -m mpremote connect port:$port fs cp "$localPath" ":$remotePath"
            if ($LASTEXITCODE -ne 0) {
                Write-Host "   FEHLER beim Kopieren von $($item.Name)! Full Build abgebrochen." -ForegroundColor Red
                exit 1
            }
            $script:uploadedFiles += $item.Name
            Write-Host "   $remotePath hochgeladen." -ForegroundColor Green
        }
    }
}

Upload-Recursive $pyTrocknerDir
Write-Host "   $($script:uploadedFiles.Count) Dateien hochgeladen." -ForegroundColor Green

# Soft Reset nach Upload
Write-Host "[FB/4] Starte ESP32 neu (Soft Reset)..." -ForegroundColor Yellow
& python -m mpremote connect port:$port reset
if ($LASTEXITCODE -ne 0) {
    Write-Host "   Hinweis: Reset-Befehl gesendet (manueller Reset ggf. nötig)." -ForegroundColor Gray
} else {
    Write-Host "   ESP32 neu gestartet." -ForegroundColor Green
}
Write-Host "   Warte auf ESP32-Neustart (3s)..." -ForegroundColor Gray
Start-Sleep -Seconds 3

Write-Host "=== Full Build Sequenz abgeschlossen ===" -ForegroundColor Cyan
Write-Host ""

# ---------------------------------------------------------------------------
# 5. Prüfen ob mpremote erreichbar ist (nach Full Build, da Firmware jetzt drauf ist)
# ---------------------------------------------------------------------------
Write-Host "[5/8] Prüfe mpremote..." -ForegroundColor Yellow
try {
    & python -m mpremote connect port:$Port fs ls > $null 2>&1
    if ($LASTEXITCODE -ne 0) {
        Write-Host "   FEHLER: mpremote nicht erreichbar auf Port $Port!" -ForegroundColor Red
        exit 1
    }
    Write-Host "   mpremote bereit." -ForegroundColor Green
}
catch {
    Write-Host "   FEHLER: $PSItem" -ForegroundColor Red
    exit 1
}

# ---------------------------------------------------------------------------
# 6. Python-Quelldateien kopieren - mit Retry pro Datei
# ---------------------------------------------------------------------------
Write-Host "[6/8] Kopiere Python-Quelldateien..." -ForegroundColor Yellow
$pyFiles = @("config.py", "dryer.py", "led.py", "web_server.py", "main.py")
foreach ($file in $pyFiles) {
    if (-not (Test-Path $file)) {
        Write-Host "   FEHLER: $file nicht gefunden!" -ForegroundColor Red
        exit 1
    }
    $ok = Invoke-WithRetry -Name "Kopieren von $file" -MaxAttempts $MaxAttempts -DelaySeconds $RetryDelaySeconds -Action {
        & python -m mpremote connect port:$Port fs cp $file ":$file"
    }
    if (-not $ok) {
        Write-Host "   FEHLER beim Kopieren von $file!" -ForegroundColor Red
        exit 1
    }
    Write-Host "   $file kopiert." -ForegroundColor Green
}

# ---------------------------------------------------------------------------
# 7. Web-Verzeichnis und Assets kopieren
# ---------------------------------------------------------------------------
Write-Host "[7/8] Kopiere Web-Assets..." -ForegroundColor Yellow
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
# 8. ESP32 neu starten
# ---------------------------------------------------------------------------
Write-Host "[8/8] Starte ESP32 neu..." -ForegroundColor Yellow
& python -m mpremote connect port:$Port reset
if ($LASTEXITCODE -ne 0) {
    Write-Host "   Hinweis: Reset-Befehl gesendet (manueller Reset ggf. nötig)." -ForegroundColor Gray
}
else {
    Write-Host "   ESP32 neu gestartet." -ForegroundColor Green
}
Write-Host "   Warte auf ESP32-Neustart (2s)..." -ForegroundColor Gray
Start-Sleep -Seconds 2

Write-Host ""
Write-Host "=== Deploy abgeschlossen! ===" -ForegroundColor Cyan
Write-Host "Verbinde dich mit WiFi: Trockner-01 (Passwort: Kannegiesser)" -ForegroundColor Cyan
Write-Host "Öffne im Browser: http://192.168.4.1/index.html" -ForegroundColor Cyan
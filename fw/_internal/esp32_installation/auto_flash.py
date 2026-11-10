import subprocess
import os
import sys
import esptool

local_path = os.path.dirname(os.path.abspath(__file__))
flash_file = os.path.join(local_path, "ESP32_GENERIC-20241129-v1.24.1.bin")

def erase_esp32():
    print("\n" + "="*60)
    print("[CMD] ESP32 Flash löschen (erase)")
    print("="*60)

    # Rufen Sie die esptool Hauptfunktion auf
    # Argumente entsprechen dem esptool CLI
    args = ["--chip", "esp32", "--baud", "460800", "erase_flash"]
    try:
        esptool.main(args)
        print("[OK] ESP32 Flash löschen (erase) erfolgreich abgeschlossen.")
    except Exception as e:
        print(f"[FEHLER] Fehler beim Löschen: {e}")
        raise RuntimeError(f"Befehl fehlgeschlagen: {e}")

def flash_esp32():
    if not os.path.exists(flash_file):
        raise FileNotFoundError(f"Firmware-Datei nicht gefunden: {flash_file}")

    print("\n" + "="*60)
    print("[CMD] ESP32 Firmware flashen")
    print("="*60)

    args = ["--chip", "esp32", "--baud", "460800", "write_flash", "-z", "0x1000", flash_file]
    try:
        esptool.main(args)
        print("[OK] ESP32 Firmware flashen erfolgreich abgeschlossen.")
    except Exception as e:
        print(f"[FEHLER] Fehler beim Flashen: {e}")
        raise RuntimeError(f"Befehl fehlgeschlagen: {e}")

if __name__ == "__main__":
    print("Starting ESP32 flash process...")

    try:
        erase_esp32()
    except Exception:
        sys.exit(1)

    try:
        flash_esp32()
    except Exception:
        sys.exit(1)

    print("ESP32 flash process completed.")

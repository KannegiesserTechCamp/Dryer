import os
import sys
import subprocess
import serial.tools.list_ports

def find_esp32_port():
    print("\n[STEP] Search ESP32 Port...")

    ports = list(serial.tools.list_ports.comports())

    if not ports: 
        raise RuntimeError("No COM-Ports detected")
    
    # Port-search for CP210x (specific)
    for port in ports:
        print(f"[DEBUG] {port.device} - {port.description}")

        desc = port.description.lower()

        if "cp210" in desc or "silicon labs" in desc:
            print(f"[OK] ESP32 (CP210x) found on {port.device}")
            return port.device
    
    # Fallback if we want to use other ESPs one day
    for port in ports:
        desc = port.description.lower()

        if any(keyword in desc for keyword in [
            "ch340",
            "ftdi",
            "usb serial"
        ]):
            print(f"[OK] Möglicher ESP gefunden auf {port.device}")
            return port.device
        
    # Last fallback (first Port)
    print("[Warning] No ESP detected -> Taking first port")
    return ports[0].device

def get_internal_path():
    if getattr(sys, 'frozen', False):
        base = sys._MEIPASS

        # beide Varianten prüfen
        path1 = os.path.join(base, "esp32_installation")
        path2 = os.path.join(base, "_internal", "esp32_installation")

        if os.path.exists(path1):
            return path1
        elif os.path.exists(path2):
            return path2
        else:
            raise RuntimeError("esp32_installation nicht gefunden")
    else:
        return os.path.dirname(__file__)
    
def run(cmd, cwd=None): 
    print(f"\n> {cmd}")
    subprocess.check_call(cmd, shell=True, cwd=cwd)

def setup_environment():
    print("\n" + "="*60)
    print("[STEP] Setup Python Environment")
    print("="*60)

    project_root = os.getcwd()
    internal_path = get_internal_path()

    venv_path = os.path.join(project_root, "esp32_installation", ".venv")

    os.makedirs(os.path.dirname(venv_path), exist_ok=True)

    # venv
    if not os.path.exists(venv_path):
        run(f"py -m venv {venv_path}", cwd=project_root)
    else: 
        print("[INFO] venv is already existing")

    pip_path = os.path.join(venv_path, "Scripts", "pip.exe")
    python_path = os.path.join(venv_path, "Scripts", "python.exe")

    # Install requirements
    requirements = os.path.join(internal_path, "requirements.txt")
    run(f"{pip_path} install -r \"{requirements}\"", cwd=project_root)

    # Test connection
    run(f"{python_path} -m mpremote connect COM4 fs ls", cwd=project_root)

    def get_base_path():
        if getattr(sys, 'frozen', False):
            return sys._MEIPASS
        return os.getcwd()

    base_path = get_base_path()

    upload_dir = os.path.join(base_path, "upload-scripts")
    upload_script = os.path.join(upload_dir, "upload_script.py")

    print("### UPLOAD STEP START ###")
    print(f"UPLOAD DIR: {upload_dir}")
    print(f"SCRIPT: {upload_script}")

    run(
        f"{python_path} \"{upload_script}\"",
        cwd=upload_dir
    )

    print("\n[OK] Setup completed")
# Deploy MicroPython files to ESP32 via mpremote
# Run this from the project root directory

# --- 1. Copy Python source files ---
python -m mpremote cp config.py :config.py
python -m mpremote cp dryer.py :dryer.py
python -m mpremote cp led.py :led.py
python -m mpremote cp web_server.py :web_server.py
python -m mpremote cp main.py :main.py

# --- 2. Create web directory on device ---
python -m mpremote mkdir :web 2>$null

# --- 3. Copy web assets ---
python -m mpremote cp web/index.html :web/index.html
python -m mpremote cp web/style.css :web/style.css
python -m mpremote cp web/logo.png :web/logo.png
python -m mpremote cp web/Trocknerbutton.png :web/Trocknerbutton.png
python -m mpremote cp web/LEDbutton.png :web/LEDbutton.png

# --- 4. Restart device to run main.py ---
python -m mpremote reset

Write-Host "Deployment complete. ESP32 should be running main.py" -ForegroundColor Green
Write-Host "Connect to WiFi AP: Trockner-01 (password: Kannegiesser)" -ForegroundColor Cyan
Write-Host "Open browser: http://192.168.4.1" -ForegroundColor Cyan

// Steps to configure the Arduino IDE, install the ESP32 board package, select the AI Thinker ESP32-CAM board, load the CameraWebServer example, and upload it to verify camera and Wi‑Fi streaming.
//
// Buy this module: https://shillehtek.com/products/esp32-cam-4wd-robot-car-kit
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-cam-4wd-robot-car-kit-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

Arduino IDE setup for the ESP32-CAM:
1. File > Preferences > Additional Boards Manager URLs:
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
2. Tools > Board > Boards Manager > install "esp32"
3. Tools > Board > "AI Thinker ESP32-CAM"
4. File > Examples > ESP32 > Camera > CameraWebServer
   - select CAMERA_MODEL_AI_THINKER in the sketch
   - enter your Wi-Fi SSID and password
5. GPIO 0 jumper ON, reset, Upload; jumper OFF, reset
6. Open Serial Monitor (115200) - it prints the stream URL
7. Visit that URL in a browser: live video confirms the
   board, camera, and Wi-Fi all work before the car does

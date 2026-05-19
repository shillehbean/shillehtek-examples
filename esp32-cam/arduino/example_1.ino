// Step-by-step instructions to load and run the Arduino CameraWebServer example on an AI Thinker / Kuongshun ESP32-CAM to get a live MJPEG web stream.
//
// Buy this module: https://shillehtek.com/products/kuongshun-esp32-cam-development-board-wifi-bluetooth-module-with-ov3660-camera-with-soldering-and-foam
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/kuongshun-esp32-cam-development-board-wifi-bluetooth-module-with-ov3660-camera-with-soldering-and-foam-manual
// More examples: https://github.com/shillehtek/examples
//

// Easiest way to get a live web stream:
//
// 1. Tools -> Board -> AI Thinker ESP32-CAM
// 2. File -> Examples -> ESP32 -> Camera -> CameraWebServer
// 3. Edit ssid / password near the top of the sketch
// 4. Find the line "#define CAMERA_MODEL_AI_THINKER" and leave it uncommented
// 5. Upload (hold BOOT button if upload errors)
// 6. Open Serial Monitor at 115200 baud, reset the board
// 7. It prints an IP address - open it in your browser
// 8. Click "Start Stream" - live video appears!

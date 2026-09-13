// Example Arduino-framework sketch for an ESP32-CAM that triggers a camera capture on PIR motion, posts the image (placeholder), and reads seed weight from an HX711 load cell amplifier.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-cam-hx711-pir-bird-feeder-dashboard
// Parts used: https://shillehtek.com/products/kuongshun-esp32-cam-development-board-wifi-bluetooth-module-with-ov3660-camera-with-soldering-and-foam
//             https://shillehtek.com/products/hx711-weighing-pressure-sensor-module-large-presoldered
//             https://shillehtek.com/products/shillehtek-hc-sr501-pir-motion-sensor-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <esp_camera.h>
#include <WiFi.h>
#include <HX711.h>
const int PIR = 13;
HX711 scale;
void setup() {
  pinMode(PIR, INPUT);
  WiFi.begin("SSID", "PASS");
  scale.begin(14, 15); scale.set_scale(420.0); scale.tare();
  // camera_config + esp_camera_init(&config)
}
void snapAndPost() {
  camera_fb_t *fb = esp_camera_fb_get();
  // POST fb->buf to your server / Telegram / S3
  esp_camera_fb_return(fb);
}
void loop() {
  if (digitalRead(PIR) == HIGH) {
    snapAndPost();
    float seedGrams = scale.get_units(5);
    Serial.printf("Bird detected. Seed left: %.0fg\n", seedGrams);
    delay(30000);   // 30s cooldown
  }
  delay(200);
}

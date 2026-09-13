// Initializes the ESP32-CAM camera, connects to WiFi, captures a photo and POSTS it to Telegram, then configures an RTC GPIO wakeup from a PIR sensor and enters deep sleep.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-cam-pir-solar-off-grid-motion-camera
// Parts used: https://shillehtek.com/products/110-x-136mm-6v-2w-solar-panel
//             https://shillehtek.com/products/cn3791-6v-mppt-solar-charger-module
//             https://shillehtek.com/products/1s-3-7v-3a-2mos-bms-li-ion-18650-battery-protection-board
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include "esp_camera.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "driver/rtc_io.h"

#define MOTION_PIN GPIO_NUM_13

void setup() {
  Serial.begin(115200);
  // Camera config (AI-Thinker defaults)
  camera_config_t config = {};
  // ... fill in standard AI-Thinker pin map ...
  esp_camera_init(&config);

  // Capture one frame
  camera_fb_t* fb = esp_camera_fb_get();

  // Connect WiFi
  WiFi.begin("MY_SSID","MY_PASS");
  while (WiFi.status() != WL_CONNECTED) delay(200);

  // POST to Telegram
  HTTPClient http;
  http.begin("https://api.telegram.org/botKEY/sendPhoto?chat_id=ID");
  http.addHeader("Content-Type", "image/jpeg");
  http.POST(fb->buf, fb->len);
  http.end();
  esp_camera_fb_return(fb);

  // Sleep until motion
  rtc_gpio_pulldown_dis(MOTION_PIN);
  rtc_gpio_pullup_en(MOTION_PIN);
  esp_sleep_enable_ext0_wakeup(MOTION_PIN, 1);
  esp_deep_sleep_start();
}
void loop() {}

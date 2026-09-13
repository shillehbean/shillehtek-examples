// Monitors a PIR sensor and, on motion, captures a photo with esp_camera and sends it via SMTP using ESP_Mail_Client (camera init and SMTP attachment details are left as placeholders).
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-cam-hc-sr501-pir-motion-photo-alerts-wifi
// Parts used: https://shillehtek.com/products/kuongshun-esp32-cam-development-board-wifi-bluetooth-module-with-ov3660-camera-with-soldering-and-foam
//             https://shillehtek.com/products/shillehtek-hc-sr501-pir-motion-sensor-module
//             https://shillehtek.com/products/micro-sd-tf-card-adapter-reader-module-spi-interface-for-arduino
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <esp_camera.h>
#include <ESP_Mail_Client.h>
#define PIR_PIN 13
const char* SSID = "WIFI";
const char* PASS = "PWD";
const char* FROM = "you@gmail.com";
const char* APP_PASS = "GMAIL_APP_PASSWORD";
const char* TO = "you@gmail.com";
SMTPSession smtp;

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  // camera_config + esp_camera_init(&config) goes here
}

void snapAndEmail() {
  camera_fb_t *fb = esp_camera_fb_get();
  // attach fb->buf as JPEG to the SMTP message, send via smtp.connect + MailClient.sendMail
  esp_camera_fb_return(fb);
}

void loop() {
  if (digitalRead(PIR_PIN) == HIGH) {
    snapAndEmail();
    delay(60000);   // 1 min cooldown
  }
  delay(200);
}

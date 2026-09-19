// Connects the ESP32 to Wi‑Fi, configures and starts ArduinoOTA with hostname/password and progress callbacks, and runs the OTA handler while leaving a spot for user code (e.g., LED blink).
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-arduinoota-ota-wifi-updates
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/esp8266-d1-mini-v3-4mb-dev-board-presoldered
//             https://shillehtek.com/products/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>          // ESP8266: <ESP8266WiFi.h> and <ESP8266mDNS.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>

const char* SSID = "YourNetwork";
const char* PASS = "YourPassword";
const int LED = 2;
const int BLINK_MS = 1000;        // change this later to prove the OTA update worked

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(250);
  Serial.println("IP: " + WiFi.localIP().toString());

  ArduinoOTA.setHostname("esp32-lamp");      // shows up as esp32-lamp in the port list
  ArduinoOTA.setPassword("update-me");       // the IDE will ask for this
  ArduinoOTA.onStart([]() { Serial.println("OTA start"); });
  ArduinoOTA.onProgress([](unsigned int done, unsigned int total) {
    Serial.printf("OTA %u%%\r", done * 100 / total);
  });
  ArduinoOTA.onEnd([]()   { Serial.println("\nOTA done, rebooting"); });
  ArduinoOTA.onError([](ota_error_t e) { Serial.printf("OTA error %u\n", e); });
  ArduinoOTA.begin();
  Serial.println("OTA ready");
}

void loop() {
  ArduinoOTA.handle();                       // must run often: this is what listens for uploads

  // --- your real project goes here; keep it non-blocking ---
  digitalWrite(LED, (millis() / BLINK_MS) % 2);
}

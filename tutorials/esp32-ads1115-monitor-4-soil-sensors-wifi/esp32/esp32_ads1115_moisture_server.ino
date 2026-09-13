// Reads four channels from an ADS1115 ADC and serves a simple HTML page over Wi‑Fi showing the raw ADC values for each soil sensor.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-ads1115-monitor-4-soil-sensors-wifi
// Parts used: https://shillehtek.com/products/shillehtek-ads-1115-pre-soldered
//             https://shillehtek.com/products/soil-moisture-sensor-hygrometer-module-for-arduino-watering-kit
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads;
WebServer server(80);
void root() {
  String body = "<h1>Plant Moisture</h1>";
  for (int ch = 0; ch < 4; ch++) {
    int raw = ads.readADC_SingleEnded(ch);
    body += "<p>Plant " + String(ch+1) + ": " + String(raw) + "</p>";
  }
  server.send(200, "text/html", body);
}
void setup() {
  Serial.begin(115200);
  WiFi.begin("SSID","PASS");
  while (WiFi.status() != WL_CONNECTED) delay(500);
  ads.begin();
  server.on("/", root); server.begin();
}
void loop() { server.handleClient(); }

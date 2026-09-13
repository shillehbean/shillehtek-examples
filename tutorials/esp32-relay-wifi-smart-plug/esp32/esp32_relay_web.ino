// Runs a minimal HTTP server on an ESP32 exposing /on and /off endpoints to set a relay pin HIGH/LOW.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-relay-wifi-smart-plug
// Parts used: https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/1-channel-5v-relay-module
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Minimal Arduino sketch - visit ESP32-IP/on or /off
#include <WiFi.h>
#include <WebServer.h>
WebServer server(80);
const int RELAY = 13;

void setup() {
  pinMode(RELAY, OUTPUT);
  WiFi.begin("SSID", "PASS");
  while (WiFi.status() != WL_CONNECTED) delay(500);
  server.on("/on",  [](){ digitalWrite(RELAY, HIGH); server.send(200, "text/plain", "ON"); });
  server.on("/off", [](){ digitalWrite(RELAY, LOW);  server.send(200, "text/plain", "OFF"); });
  server.begin();
}
void loop() { server.handleClient(); }

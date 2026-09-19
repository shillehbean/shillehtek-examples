// An ESP32 sketch that creates a Wi‑Fi access point and a minimal HTTP server exposing endpoints (/forward, /back, /left, /right, /stop) to drive the motors from a browser or app.
//
// Buy this module: https://shillehtek.com/products/esp32-cam-4wd-robot-car-kit
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-cam-4wd-robot-car-kit-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Bare-bones browser control: the car hosts its own Wi-Fi AP.
// Connect to "ESP32-CAR" and visit http://192.168.4.1/forward etc.
#include <WiFi.h>
#include <WebServer.h>

const int L_FWD = 12, L_REV = 13, R_FWD = 14, R_REV = 15;
WebServer server(80);

void drive(bool lf, bool lr, bool rf, bool rr) {
  digitalWrite(L_FWD, lf); digitalWrite(L_REV, lr);
  digitalWrite(R_FWD, rf); digitalWrite(R_REV, rr);
  server.send(200, "text/plain", "ok");
}

void setup() {
  for (int p : {L_FWD, L_REV, R_FWD, R_REV}) pinMode(p, OUTPUT);
  WiFi.softAP("ESP32-CAR", "drive1234");
  server.on("/forward", []() { drive(1, 0, 1, 0); });
  server.on("/back",    []() { drive(0, 1, 0, 1); });
  server.on("/left",    []() { drive(0, 1, 1, 0); });
  server.on("/right",   []() { drive(1, 0, 0, 1); });
  server.on("/stop",    []() { drive(0, 0, 0, 0); });
  server.begin();
}

void loop() {
  server.handleClient();
}

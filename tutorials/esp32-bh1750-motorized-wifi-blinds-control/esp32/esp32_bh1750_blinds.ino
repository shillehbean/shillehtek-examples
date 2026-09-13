// Hosts a simple web server on an ESP32 to control a 28BYJ‑48 stepper (via ULN2003) and reads ambient light from a BH1750; provides /up and /down endpoints to move the blinds.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-bh1750-motorized-wifi-blinds-control
// Parts used: https://shillehtek.com/products/shillehtek-5v-4-phase-stepper-motor-with-uln2003-driver
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/shillehtek-gy-302-bh1750-pre-soldered-light-intensity-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Stepper.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <BH1750.h>
Stepper stepper(2048, 12, 14, 13, 15);
BH1750 light;
WebServer server(80);
void up()    { stepper.step(2048 * 10); }    // 10 turns to roll up
void down()  { stepper.step(-2048 * 10); }
void setup() {
  Wire.begin(); light.begin();
  WiFi.begin("SSID","PASS");
  while (WiFi.status() != WL_CONNECTED) delay(500);
  stepper.setSpeed(15);   // RPM
  server.on("/up",   [](){ up();   server.send(200, "text/plain", "UP"); });
  server.on("/down", [](){ down(); server.send(200, "text/plain", "DOWN"); });
  server.begin();
}
void loop() {
  server.handleClient();
  float lux = light.readLightLevel();
  // Optional: auto-roll based on lux thresholds
}

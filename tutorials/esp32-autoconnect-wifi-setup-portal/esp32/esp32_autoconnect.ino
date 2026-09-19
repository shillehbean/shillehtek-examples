// Creates an ESP32 sketch that uses the AutoConnect library to host a captive Wi-Fi setup portal, serves a simple root web page, and saves/reconnects Wi‑Fi credentials.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-autoconnect-wifi-setup-portal
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/esp8266-d1-mini-v3-4mb-dev-board-presoldered
//             https://shillehtek.com/products/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>            // ESP8266: #include <ESP8266WiFi.h> and <ESP8266WebServer.h>
#include <WebServer.h>
#include <AutoConnect.h>

WebServer server(80);         // ESP8266: ESP8266WebServer server(80);
AutoConnect portal(server);
AutoConnectConfig config;

void rootPage() {             // your normal web page / app lives here
  String s = "<h1>Hello from the ESP32</h1>";
  s += "<p>Connected to " + WiFi.SSID() + " as " + WiFi.localIP().toString() + "</p>";
  s += "<p><a href='/_ac'>Wi-Fi settings</a></p>";   // built-in portal menu
  server.send(200, "text/html", s);
}

void setup() {
  Serial.begin(115200);
  config.apid = "ESP32-Setup";        // name of the setup hotspot
  config.psk  = "setup1234";          // hotspot password (8+ chars), or "" for open
  config.autoReconnect = true;        // reconnect to the saved network after outages
  config.retainPortal  = true;        // keep the portal reachable at /_ac while connected
  portal.config(config);

  server.on("/", rootPage);
  if (portal.begin()) {
    Serial.println("Online: " + WiFi.localIP().toString());
  }
}

void loop() {
  portal.handleClient();              // serves both your pages and the portal
}

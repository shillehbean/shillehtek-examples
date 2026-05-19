// Connects the XIAO ESP32S3 to Wi‑Fi and runs a minimal HTTP server that serves a status page showing uptime and free heap memory.
//
// Buy this module: https://shillehtek.com/products/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable-manual
// More examples: https://github.com/shillehtek/examples
//

// XIAO ESP32-S3 - Tiny HTTP server returning a status page.
// Replace YOUR_SSID / YOUR_PASS with your network credentials.

#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "YOUR_SSID";
const char* password = "YOUR_PASS";

WebServer server(80);

void handleRoot() {
  String html = "<h1>XIAO ESP32-S3</h1>";
  html += "<p>Uptime: " + String(millis() / 1000) + " s</p>";
  html += "<p>Free heap: " + String(ESP.getFreeHeap()) + " bytes</p>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(250); Serial.print('.'); }
  Serial.println();
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}

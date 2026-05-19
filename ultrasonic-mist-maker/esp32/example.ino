// Hosts a minimal web page on an ESP32 to toggle the mist maker wired to GPIO5 via /on and /off HTTP endpoints.
//
// Buy this module: https://shillehtek.com/products/dc-5v-ultrasonic-mist-maker-humidifier-module-108khz-usb
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/dc-5v-ultrasonic-mist-maker-humidifier-module-108khz-usb-manual
// More examples: https://github.com/shillehtek/examples
//

// ESP32 - Toggle the mist maker from a tiny web page
// Wire MOSFET gate to GPIO 5

#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const int   mistPin  = 5;
bool        misting  = false;

WebServer server(80);

String page() {
  String s = "<html><body><h1>Mist Maker</h1>";
  s += "<p>Status: " + String(misting ? "ON" : "OFF") + "</p>";
  s += "<a href=\"/on\">[ON]</a> <a href=\"/off\">[OFF]</a>";
  s += "</body></html>";
  return s;
}

void setup() {
  Serial.begin(115200);
  pinMode(mistPin, OUTPUT);
  digitalWrite(mistPin, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(300); Serial.print("."); }
  Serial.println(WiFi.localIP());

  server.on("/", []() { server.send(200, "text/html", page()); });
  server.on("/on",  []() { misting = true;  digitalWrite(mistPin, HIGH); server.send(200, "text/html", page()); });
  server.on("/off", []() { misting = false; digitalWrite(mistPin, LOW);  server.send(200, "text/html", page()); });
  server.begin();
}

void loop() { server.handleClient(); }

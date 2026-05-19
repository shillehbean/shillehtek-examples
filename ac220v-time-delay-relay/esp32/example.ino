// Runs a tiny web server on an ESP32; visiting /fire pulses GPIO5 HIGH for 150 ms to trigger the relay and returns a confirmation response.
//
// Buy this module: https://shillehtek.com/products/ac-220v-1-channel-time-delay-relay-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ac-220v-1-channel-time-delay-relay-module-manual
// More examples: https://github.com/shillehtek/examples
//

// ESP32 - fire the time-delay relay from a tiny web page
// Wire Trigger+ to GPIO 5, share GND.

#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const int   trigPin  = 5;

WebServer server(80);

void fire() {
  digitalWrite(trigPin, HIGH);
  delay(150);
  digitalWrite(trigPin, LOW);
}

void setup() {
  pinMode(trigPin, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(300); Serial.print("."); }
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/html", "<a href=\"/fire\">[ FIRE RELAY ]</a>");
  });
  server.on("/fire", []() {
    fire();
    server.send(200, "text/plain", "Triggered.");
  });
  server.begin();
}

void loop() { server.handleClient(); }

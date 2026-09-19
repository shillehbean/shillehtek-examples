// ESP32 Arduino-framework sketch that connects to Wi‑Fi, hosts an HTTP server, serves a simple control page, and toggles a GPIO to drive an LED or relay.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-webserver-relay-module-local-phone-control
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/1-channel-5v-relay-module
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <WebServer.h>

const char* SSID = "YourNetwork";
const char* PASS = "YourPassword";
const int   LED  = 2;                  // later: the relay's IN pin

WebServer server(80);
bool ledOn = false;

String page() {
  String s = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width,initial-scale=1'>";
  s += "<style>body{font-family:sans-serif;text-align:center;margin-top:40px}";
  s += "a{display:inline-block;padding:18px 40px;margin:10px;font-size:24px;color:#fff;border-radius:8px;text-decoration:none}";
  s += ".on{background:#2e7d32}.off{background:#c62828}</style></head><body>";
  s += "<h1>ESP32 LED Control</h1><p>LED is <b>" + String(ledOn ? "ON" : "OFF") + "</b></p>";
  s += "<a class='on' href='/led/on'>ON</a><a class='off' href='/led/off'>OFF</a></body></html>";
  return s;
}

void backHome() {                      // redirect to "/" so the page refreshes
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  WiFi.begin(SSID, PASS);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println("\nOpen http://" + WiFi.localIP().toString());

  server.on("/",        []() { server.send(200, "text/html", page()); });
  server.on("/led/on",  []() { ledOn = true;  digitalWrite(LED, HIGH); backHome(); });
  server.on("/led/off", []() { ledOn = false; digitalWrite(LED, LOW);  backHome(); });
  server.begin();
}

void loop() {
  server.handleClient();               // answer requests as they arrive
}

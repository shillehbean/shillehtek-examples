// Connect the Wemos D1 Mini to a Wi‑Fi network and print its local IP address to the Serial console.
//
// Full tutorial: https://shillehtek.com/blogs/news/wemos-d1-mini-esp8266-blink-led-wifi-ip
// Parts used: https://shillehtek.com/products/esp8266-d1-mini-v3-4mb-dev-board-presoldered
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <ESP8266WiFi.h>

const char* SSID = "your-network";
const char* PASS = "your-password";

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASS);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {}

// Connects the D1 Mini to a Wi‑Fi network and prints its IP address and RSSI to the serial console.
//
// Buy this module: https://shillehtek.com/products/esp8266-d1-mini-v3-4mb-dev-board-presoldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp8266-d1-mini-v3-4mb-dev-board-presoldered-manual
// More examples: https://github.com/shillehtek/examples
//

// D1 Mini V3 - join Wi-Fi and print IP
// Install: Boards Manager URL http://arduino.esp8266.com/stable/package_esp8266com_index.json
// Select Board: "LOLIN(WEMOS) D1 R2 & mini"

#include <ESP8266WiFi.h>

const char* ssid = "YOUR_SSID";
const char* pass = "YOUR_PASSWORD";

void setup() {
  Serial.begin(115200);
  delay(500);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) { delay(300); Serial.print("."); }
  Serial.println();
  Serial.print("IP: "); Serial.println(WiFi.localIP());
  Serial.print("RSSI: "); Serial.print(WiFi.RSSI()); Serial.println(" dBm");
}

void loop() { delay(5000); }

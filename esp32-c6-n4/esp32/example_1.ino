// Connect the ESP32-C6 to a 2.4 GHz Wi‑Fi network and print the assigned IP address to the Serial console.
//
// Buy this module: https://shillehtek.com/products/esp32-c6-n4-dev-board-presoldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-c6-n4-dev-board-presoldered-manual
// More examples: https://github.com/shillehtek/examples
//

// Connect the ESP32-C6 to your 2.4 GHz Wi-Fi network and print its IP.
// In Arduino IDE: Tools > Board > ESP32 Arduino > ESP32C6 Dev Module

#include <WiFi.h>

const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // nothing here
}

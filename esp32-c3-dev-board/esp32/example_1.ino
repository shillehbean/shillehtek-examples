// Connects the ESP32-C3 to a Wi‑Fi network, prints the assigned IP address and RSSI to the serial console, and periodically reports whether the connection is still active.
//
// Buy this module: https://shillehtek.com/products/esp32-c3-dev-board-4mb-wifi-presoldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-c3-dev-board-4mb-wifi-presoldered-manual
// More examples: https://github.com/shillehtek/examples
//

// ESP32-C3 - Connect to Wi-Fi and print IP
// Install: Boards Manager -> "esp32" by Espressif Systems
// Select Board: "ESP32C3 Dev Module"

#include <WiFi.h>

const char* ssid     = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

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
  Serial.print("RSSI: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

void loop() {
  delay(10000);
  Serial.print("Still connected? ");
  Serial.println(WiFi.status() == WL_CONNECTED ? "yes" : "no");
}

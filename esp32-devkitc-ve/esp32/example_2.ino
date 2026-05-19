// Connects the ESP32 to a Wi‑Fi network using the provided SSID/password and prints the board's IP address and RSSI to Serial.
//
// Buy this module: https://shillehtek.com/products/esp32-devkitc-ve-8mb-flash-8mb-psram-presoldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-devkitc-ve-8mb-flash-8mb-psram-presoldered-manual
// More examples: https://github.com/shillehtek/examples
//

// ESP32-DevKitC-VE - join Wi-Fi and print IP

#include <WiFi.h>

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

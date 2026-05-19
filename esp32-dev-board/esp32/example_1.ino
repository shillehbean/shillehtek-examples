// Connects the ESP32 to a specified Wi-Fi network and prints the board's local IP address and Wi‑Fi RSSI to the serial console.
//
// Buy this module: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-dev-board-cp2102-type-c-4mb-manual
// More examples: https://github.com/shillehtek/examples
//

// ESP-WROOM-32 - join Wi-Fi and print IP
// Install: Boards Manager -> "esp32" by Espressif Systems
// Select Board: "ESP32 Dev Module"

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

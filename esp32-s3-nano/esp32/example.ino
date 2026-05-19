// Scans nearby Wi‑Fi networks with the ESP32‑S3 and prints each network's SSID, RSSI, and encryption status to the serial console.
//
// Buy this module: https://shillehtek.com/products/esp32-s3-nano-dev-board-presoldered-wifi-ble
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-s3-nano-dev-board-presoldered-wifi-ble-manual
// More examples: https://github.com/shillehtek/examples
//

// ESP32-S3 Nano - Wi-Fi Network Scanner
// Install: Boards Manager -> "esp32" by Espressif Systems
// Select Board: "ESP32S3 Dev Module"

#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Set Wi-Fi to station mode and disconnect from any AP
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("ESP32-S3 Nano Wi-Fi Scanner Ready");
}

void loop() {
  Serial.println("Scanning for networks...");
  int n = WiFi.scanNetworks();

  if (n == 0) {
    Serial.println("No networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found:");
    for (int i = 0; i < n; i++) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(" dBm) ");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "[Open]" : "[Encrypted]");
      delay(10);
    }
  }
  Serial.println();
  delay(5000);
}

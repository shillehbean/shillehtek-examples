// Scan for nearby Wi‑Fi networks and print each network's SSID, RSSI, and whether it's open or encrypted to the Serial Monitor.
//
// Buy this module: https://shillehtek.com/products/xiao-seeed-esp32c3-pre-soldered-with-usb-to-usb-c-cable
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/xiao-seeed-esp32c3-pre-soldered-with-usb-to-usb-c-cable-manual
// More examples: https://github.com/shillehtek/examples
//

// XIAO ESP32-C3 - Scan for nearby Wi-Fi networks
// Prints SSID, RSSI, and encryption type to Serial Monitor.

#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(500);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Wi-Fi scan starting...");
}

void loop() {
  int n = WiFi.scanNetworks();
  Serial.printf("Found %d networks:\n", n);
  for (int i = 0; i < n; i++) {
    Serial.printf("  %2d) %-32s  %4d dBm  %s\n",
                  i + 1,
                  WiFi.SSID(i).c_str(),
                  WiFi.RSSI(i),
                  WiFi.encryptionType(i) == WIFI_AUTH_OPEN ? "OPEN" : "ENC");
  }
  Serial.println();
  delay(5000);
}

// Prints ESP32 chip/flash/PSRAM info, allocates 1 MB in PSRAM to verify it's usable, and performs a WiFi network scan showing SSIDs and RSSI.
//
// Buy this module: https://shillehtek.com/products/esp32-wrover-4mb-psram-wifi-bluetooth-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-wrover-4mb-psram-wifi-bluetooth-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// ESP32-WROVER - PSRAM check + WiFi scan
// Arduino IDE: Tools -> Board -> "ESP32 Wrover Module", PSRAM: "Enabled"

#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.printf("Chip: %s, %d cores @ %d MHz\n",
                ESP.getChipModel(), ESP.getChipCores(), ESP.getCpuFreqMHz());
  Serial.printf("Flash: %u bytes\n", ESP.getFlashChipSize());
  Serial.printf("PSRAM: %u bytes (%s)\n", ESP.getPsramSize(),
                psramFound() ? "FOUND" : "NOT FOUND");

  // Allocate 1MB in PSRAM to prove it's usable
  uint8_t *big = (uint8_t *)ps_malloc(1024 * 1024);
  Serial.printf("1MB PSRAM alloc: %s\n", big ? "OK" : "FAILED");
  if (big) free(big);

  WiFi.mode(WIFI_STA);
  Serial.println("\nScanning WiFi...");
  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; i++) {
    Serial.printf("%2d: %-24s %d dBm\n",
                  i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
  }
}

void loop() {}

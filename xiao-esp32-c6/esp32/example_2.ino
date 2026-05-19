// Connects the board to a Wi‑Fi network using the provided SSID/password and prints the IP address, RSSI and free heap to Serial.
//
// Buy this module: https://shillehtek.com/products/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable-manual
// More examples: https://github.com/shillehtek/examples
//

// XIAO ESP32-C6 - Connect to Wi-Fi (802.11ax/n/g/b)
// Replace YOUR_SSID / YOUR_PASS with your credentials.

#include <WiFi.h>

const char* ssid     = "YOUR_SSID";
const char* password = "YOUR_PASS";

void setup() {
  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }
  Serial.println();
  Serial.printf("Connected, IP = %s\n", WiFi.localIP().toString().c_str());
  Serial.printf("RSSI: %d dBm\n", WiFi.RSSI());
}

void loop() {
  delay(10000);
  Serial.printf("Heap: %u  RSSI: %d\n", ESP.getFreeHeap(), WiFi.RSSI());
}

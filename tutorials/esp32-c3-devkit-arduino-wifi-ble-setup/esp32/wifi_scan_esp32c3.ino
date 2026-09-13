// Scan for nearby WiFi networks in station mode and print each network's SSID and RSSI to the serial console.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-c3-devkit-arduino-wifi-ble-setup
// Parts used: https://shillehtek.com/products/xiao-seeed-esp32c3-pre-soldered-with-usb-to-usb-c-cable
//             https://shillehtek.com/products/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  Serial.printf("%d networks:\n", n);
  for (int i = 0; i < n; i++) {
    Serial.printf("  %s (%d dBm)\n",
                  WiFi.SSID(i).c_str(), WiFi.RSSI(i));
  }
}
void loop() {}

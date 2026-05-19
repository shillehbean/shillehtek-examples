// Connects the ESP32-S3 to a specified Wi‑Fi network and prints the assigned IP address and RSSI to the Serial console.
//
// Buy this module: https://shillehtek.com/products/esp32-s3-devkitc-1-presoldered-headers
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-s3-devkitc-1-presoldered-headers-manual
// More examples: https://github.com/shillehtek/examples
//

#include <WiFi.h>

const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Connecting to WiFi...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());
}

void loop() { }

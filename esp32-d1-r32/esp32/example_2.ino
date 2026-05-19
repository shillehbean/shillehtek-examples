// Connect the D1 R32 to a Wi‑Fi network using the WiFi.h library and print the assigned IP address to Serial.
//
// Buy this module: https://shillehtek.com/products/wifi-and-bluetooth-esp32-4mb-flash-uno-d1-r32-ch340g-development-board-type-b-usb
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/wifi-and-bluetooth-esp32-4mb-flash-uno-d1-r32-ch340g-development-board-type-b-usb-manual
// More examples: https://github.com/shillehtek/examples
//

// D1 R32 - Connect to WiFi and print the IP address

#include <WiFi.h>

const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASS";

void setup() {
  Serial.begin(115200);
  delay(100);

  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // your code
}

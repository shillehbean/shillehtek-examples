// Use the Arduino core WiFi API on the Pico 2W to connect to a wireless network and print the device's IP address over Serial.
//
// Buy this module: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/raspberry-pi-pico-2w-presoldered-headers-manual
// More examples: https://github.com/shillehtek/examples
//

// Raspberry Pi Pico 2W - Arduino IDE WiFi Example
// Install "Raspberry Pi Pico/RP2040/RP2350" by Earle Philhower.
// Select: Tools > Board > Raspberry Pi Pico 2W

#include <WiFi.h>

const char* ssid = "your_wifi_name";
const char* password = "your_wifi_password";

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(1000);
}

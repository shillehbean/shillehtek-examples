// Connects the ESP32-S3 to a WiFi network and prints the assigned IP address to the serial console.
//
// Buy this module: https://shillehtek.com/products/sx1262-esp32-s3-0-96-inch-blue-oled-display-bluetooth-wifi-kit-32-module-iot-development-board-for-arduino-w-antenna-868-915mhz-with-soldering-and-foam
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/sx1262-esp32-s3-0-96-inch-blue-oled-display-bluetooth-wifi-kit-32-module-iot-development-board-for-arduino-w-antenna-868-915mhz-with-soldering-and-foam-manual
// More examples: https://github.com/shillehtek/examples
//

// Heltec V3 - connect to WiFi and print IP

#include <WiFi.h>

const char* ssid = "YOUR_SSID";
const char* pass = "YOUR_PASS";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println();
  Serial.print("IP: "); Serial.println(WiFi.localIP());
}

void loop() {}

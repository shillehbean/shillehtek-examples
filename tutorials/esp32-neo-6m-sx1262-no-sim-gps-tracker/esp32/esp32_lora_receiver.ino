// Initializes the SX1262 LoRa radio as a receiver, waits for incoming packets, and prints received latitude/longitude strings to the serial console for use at a base station.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-neo-6m-sx1262-no-sim-gps-tracker
// Parts used: https://shillehtek.com/products/gt-u7-gps-module-presoldered-1
//             https://shillehtek.com/products/sx1262-esp32-s3-0-96-inch-blue-oled-display-bluetooth-wifi-kit-32-module-iot-development-board-for-arduino-w-antenna-868-915mhz-with-soldering-and-foam
//             https://shillehtek.com/products/18650-tp4056-1a-3-7-4-2v-lipo-battery-charging-board-micro-usb-with-current-protection
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <LoRa.h>
void setup() {
  Serial.begin(115200);
  LoRa.setPins(8, 12, 14);
  LoRa.begin(915E6);
}
void loop() {
  int size = LoRa.parsePacket();
  if (size) {
    String msg = "";
    while (LoRa.available()) msg += (char)LoRa.read();
    Serial.print("Lat,Lng: "); Serial.println(msg);
    // Paste into Google Maps as "lat, lng"
  }
}

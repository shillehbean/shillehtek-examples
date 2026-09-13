// Reads NMEA data from a NEO-6M GPS on Serial2, parses latitude/longitude with TinyGPS++, and transmits comma-separated coordinates over LoRa every 10 seconds.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-neo-6m-sx1262-no-sim-gps-tracker
// Parts used: https://shillehtek.com/products/gt-u7-gps-module-presoldered-1
//             https://shillehtek.com/products/sx1262-esp32-s3-0-96-inch-blue-oled-display-bluetooth-wifi-kit-32-module-iot-development-board-for-arduino-w-antenna-868-915mhz-with-soldering-and-foam
//             https://shillehtek.com/products/18650-tp4056-1a-3-7-4-2v-lipo-battery-charging-board-micro-usb-with-current-protection
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <LoRa.h>
HardwareSerial gpsSerial(2);
TinyGPSPlus gps;
void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);
  LoRa.setPins(8, 12, 14);    // SS, RST, DIO0 (board-specific)
  LoRa.begin(915E6);
}
void loop() {
  while (gpsSerial.available()) gps.encode(gpsSerial.read());
  if (gps.location.isUpdated()) {
    String msg = String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6);
    LoRa.beginPacket(); LoRa.print(msg); LoRa.endPacket();
    Serial.println("Sent: " + msg);
    delay(10000);   // 10s between transmissions
  }
}

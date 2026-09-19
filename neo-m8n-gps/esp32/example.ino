// Uses an ESP32 hardware UART (UART2) with TinyGPSPlus to parse NMEA sentences and print latitude, longitude, satellite count and altitude.
//
// Buy this module: https://shillehtek.com/products/gps-module-neo-m8n-antenna-battery-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gps-module-neo-m8n-antenna-battery-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <TinyGPSPlus.h>

TinyGPSPlus gps;
HardwareSerial gpsSerial(2);   // UART2

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);  // RX=16, TX=17
}

void loop() {
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isUpdated()) {
    Serial.printf("Lat: %.6f  Lng: %.6f  Sats: %lu  Alt: %.1f m\n",
                  gps.location.lat(), gps.location.lng(),
                  gps.satellites.value(), gps.altitude.meters());
  }
}

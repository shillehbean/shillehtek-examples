// Reads NMEA data over SoftwareSerial using TinyGPSPlus on an Arduino and prints latitude, longitude and satellite count when a new fix is available.
//
// Buy this module: https://shillehtek.com/products/gps-module-neo-m8n-antenna-battery-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gps-module-neo-m8n-antenna-battery-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Library Manager: install "TinyGPSPlus"
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

SoftwareSerial gpsSerial(4, 3);  // RX = D4 (GPS TXD), TX = D3
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  Serial.println("Waiting for GPS fix...");
}

void loop() {
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isUpdated()) {
    Serial.print("Lat: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print("  Lng: ");
    Serial.print(gps.location.lng(), 6);
    Serial.print("  Sats: ");
    Serial.println(gps.satellites.value());
  }
}

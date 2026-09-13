// Reads NMEA data from a NEO-6M GPS via SoftwareSerial, parses it with TinyGPS++, and prints latitude, longitude, satellite count, and UTC time to the Serial monitor.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-neo-6m-gps-read-lat-long
// Parts used: https://shillehtek.com/products/gt-u7-gps-module-presoldered-1
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RX = 4, TX = 3;
SoftwareSerial gps_serial(RX, TX);
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  gps_serial.begin(9600);
}

void loop() {
  while (gps_serial.available()) gps.encode(gps_serial.read());

  if (gps.location.isUpdated()) {
    Serial.print("Lat="); Serial.print(gps.location.lat(), 6);
    Serial.print(" Lng="); Serial.print(gps.location.lng(), 6);
    Serial.print(" Sats="); Serial.print(gps.satellites.value());
    Serial.print(" UTC=");
    Serial.print(gps.time.hour()); Serial.print(':');
    Serial.print(gps.time.minute()); Serial.print(':');
    Serial.println(gps.time.second());
  }
}

// Uses the TinyGPSPlus library to parse NMEA data and print updated latitude, longitude, altitude, and satellite count when a location fix is available.
//
// Buy this module: https://shillehtek.com/products/gt-u7-gps-module-presoldered-1
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gt-u7-gps-module-presoldered-1-manual
// More examples: https://github.com/shillehtek/examples
//

// GT-U7 GPS: parse NMEA with TinyGPSPlus library
// Install via Library Manager: "TinyGPSPlus" by Mikal Hart

#include 
#include 

SoftwareSerial gpsSerial(4, 3); // RX=D4, TX=D3
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  Serial.println("GT-U7: waiting for fix...");
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
    Serial.print("  Alt: ");
    Serial.print(gps.altitude.meters());
    Serial.print(" m  Sats: ");
    Serial.println(gps.satellites.value());
  }
}

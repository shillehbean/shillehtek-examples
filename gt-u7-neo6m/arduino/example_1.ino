// Forwards raw NMEA sentences from the GT-U7 to the USB Serial Monitor at 9600 baud using SoftwareSerial on D4 (RX) and D3 (TX).
//
// Buy this module: https://shillehtek.com/products/gt-u7-gps-module-presoldered-1
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gt-u7-gps-module-presoldered-1-manual
// More examples: https://github.com/shillehtek/examples
//

// GT-U7 GPS: print raw NMEA sentences over USB Serial
// Wiring: VCC->5V, GND->GND, GT-U7 TXD->D4, GT-U7 RXD->D3
// Open Serial Monitor at 9600 baud

#include 

SoftwareSerial gpsSerial(4, 3); // RX=D4, TX=D3

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  Serial.println("GT-U7 GPS ready. Waiting for NMEA sentences...");
}

void loop() {
  // Forward anything the GPS sends to the Serial Monitor
  while (gpsSerial.available()) {
    char c = gpsSerial.read();
    Serial.write(c);
  }
}

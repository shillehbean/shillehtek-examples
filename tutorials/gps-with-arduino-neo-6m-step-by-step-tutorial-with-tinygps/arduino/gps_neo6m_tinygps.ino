// Complete Arduino sketch that initializes serial ports, continuously reads GPS data, parses it with TinyGPS++ and prints updated latitude/longitude to Serial.
//
// Full tutorial: https://shillehtek.com/blogs/news/gps-with-arduino-neo-6m-step-by-step-tutorial-with-tinygps
// Parts used: https://shillehtek.com/products/gt-u7-gps-module-presoldered-1
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

SoftwareSerial serial_connection(2, 3);
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  serial_connection.begin(9600);
  Serial.println("GPS Start");
}

void loop() {
  while (serial_connection.available()) {
    gps.encode(serial_connection.read());
  }

  if (gps.location.isUpdated()) {
    Serial.print(gps.location.lat(), 6);
    Serial.print(", ");
    Serial.println(gps.location.lng(), 6);
  }
}

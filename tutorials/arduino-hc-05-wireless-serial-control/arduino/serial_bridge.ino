// Create a bidirectional serial bridge between the Arduino's USB Serial and an HC-05 connected via SoftwareSerial (pins 2 RX, 3 TX) at 9600 baud.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-hc-05-wireless-serial-control
// Parts used: https://shillehtek.com/products/hc-05-6pin-bluetooth-module-no-button
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SoftwareSerial.h>

// SoftwareSerial(rxPin, txPin)
SoftwareSerial bt(2, 3);

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  Serial.println(F("Type something on phone or here."));
}

void loop() {
  while (bt.available())     Serial.write(bt.read());
  while (Serial.available()) bt.write(Serial.read());
}

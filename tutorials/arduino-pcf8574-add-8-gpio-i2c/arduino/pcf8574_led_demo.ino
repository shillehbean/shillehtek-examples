// Demonstrates controlling a PCF8574 I2C GPIO expander from an Arduino: walks a single lit LED across the 8 outputs and then turns all outputs on and off.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-pcf8574-add-8-gpio-i2c
// Parts used: https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>

const byte ADDR = 0x20;

void writeAll(byte b) {
  Wire.beginTransmission(ADDR);
  Wire.write(b);
  Wire.endTransmission();
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  for (byte i = 0; i < 8; i++) {       // Walk one lit LED through the bank
    writeAll(1 << i);
    delay(150);
  }
  writeAll(0xFF);                         // All on
  delay(500);
  writeAll(0x00);                         // All off
  delay(500);
}

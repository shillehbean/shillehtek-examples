// Scans the I2C bus from a 5V Arduino through the bi-directional level shifter and prints discovered device addresses over serial.
//
// Buy this module: https://shillehtek.com/products/shillehtek-iic-i2c-logic-level-converter-pre-soldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/iic-i2c-logic-level-converter-pre-soldered-bi-directional
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Level-shifted I2C scan from 5V Arduino to 3.3V devices
// The shifter is on SDA/SCL; your code doesn't change.

#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Serial.println("Scanning I2C bus through level shifter...");
}

void loop() {
  byte count = 0;
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found device at 0x");
      if (addr < 16) Serial.print("0");
      Serial.println(addr, HEX);
      count++;
    }
  }
  Serial.print("Total devices: ");
  Serial.println(count);
  delay(3000);
}

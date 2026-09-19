// Scan the I2C bus using SDA=21 and SCL=22 and print any detected device addresses over serial.
//
// Buy this module: https://shillehtek.com/products/esp32-38-pin-gpio-expansion-breakout
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-38-pin-gpio-expansion-breakout-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);   // SDA, SCL on the breakout's I2C points
}

void loop() {
  int found = 0;
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.printf("Device at 0x%02X\n", addr);
      found++;
    }
  }
  if (!found) Serial.println("No I2C devices found - check SDA/SCL");
  Serial.println("---");
  delay(3000);
}

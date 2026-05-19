// Scans the I2C bus and prints any found device addresses (in hex) to the Serial console.
//
// Buy this module: https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd-manual
// More examples: https://github.com/shillehtek/examples
//

// Find the LCD's I2C address
#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("I2C Scanner");
}

void loop() {
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found device at 0x");
      Serial.println(addr, HEX);
    }
  }
  delay(5000);
}

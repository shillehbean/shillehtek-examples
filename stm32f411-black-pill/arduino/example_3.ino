// Scans the I2C bus (I2C1 on PB6=SCL, PB7=SDA) and prints any detected device addresses to the serial console.
//
// Buy this module: https://shillehtek.com/products/shillehtek-pre-soldered-authentic-stm32f411ceu6
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-pre-soldered-authentic-stm32f411ceu6-manual
// More examples: https://github.com/shillehtek/examples
//

// STM32F411 Black Pill - I2C Bus Scanner
// Default Wire bus uses I2C1 on PB6 (SCL) and PB7 (SDA).

#include <Wire.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  Wire.begin();
  Serial.println("\nI2C Scanner");
}

void loop() {
  byte found = 0;
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found device at 0x");
      if (addr < 16) Serial.print('0');
      Serial.println(addr, HEX);
      found++;
    }
  }
  Serial.print(found);
  Serial.println(" device(s) found.\n");
  delay(2000);
}

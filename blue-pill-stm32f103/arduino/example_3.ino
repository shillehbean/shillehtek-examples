// Scan the I2C1 bus (SDA=PB7, SCL=PB6) using the Wire library and print detected device addresses.
//
// Buy this module: https://shillehtek.com/products/shillehtek-unsoldered-stm32f103c8t6-blue-pill-arm-development-board-kit-pro-usb-v
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-unsoldered-stm32f103c8t6-blue-pill-arm-development-board-kit-pro-usb-v-manual
// More examples: https://github.com/shillehtek/examples
//

// STM32 Blue Pill - scan I2C1 bus (SDA=PB7, SCL=PB6)

#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin();   // I2C1 on default pins PB6/PB7
  delay(500);
  Serial.println("STM32 Blue Pill I2C Scanner");
}

void loop() {
  byte found = 0;
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("  Found device at 0x");
      if (addr < 16) Serial.print('0');
      Serial.println(addr, HEX);
      found++;
    }
  }
  if (found == 0) Serial.println("  No I2C devices found");
  Serial.println("---");
  delay(3000);
}

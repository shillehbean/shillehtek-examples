// Scans every TCA9548A channel and prints any discovered I2C device addresses to the Serial console.
//
// Buy this module: https://shillehtek.com/products/Arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/cjmcu-9548-tca9548a-1-to-8-i2c-8-channel-multiplexer-module-manual
// More examples: https://github.com/shillehtek/examples
//

#include <Wire.h>

#define TCA_ADDR 0x70

void tcaSelect(uint8_t ch) {
  if (ch > 7) return;
  Wire.beginTransmission(TCA_ADDR);
  Wire.write(1 << ch);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(100);

  for (uint8_t ch = 0; ch < 8; ch++) {
    tcaSelect(ch);
    Serial.print("Channel "); Serial.print(ch); Serial.println(":");
    for (uint8_t addr = 1; addr < 127; addr++) {
      if (addr == TCA_ADDR) continue;
      Wire.beginTransmission(addr);
      if (Wire.endTransmission() == 0) {
        Serial.print("  Found 0x"); Serial.println(addr, HEX);
      }
    }
  }
}

void loop() {}

// Runs a simple I2C bus scanner using Wire.begin on custom SDA/SCL pins (8 and 9) and reports any detected device addresses over Serial.
//
// Buy this module: https://shillehtek.com/products/esp32-s3-devkitc-1-presoldered-headers
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-s3-devkitc-1-presoldered-headers-manual
// More examples: https://github.com/shillehtek/examples
//

#include <Wire.h>

#define SDA_PIN 8
#define SCL_PIN 9

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
  delay(500);
  Serial.println("I2C Scanner starting...");
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
  Serial.print("Total: "); Serial.println(count);
  delay(3000);
}

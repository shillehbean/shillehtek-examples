// Scans the I2C bus (addresses 1–126) and prints any detected device addresses to the native USB Serial console to verify SDA/SCL wiring.
//
// Buy this module: https://shillehtek.com/products/manual
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pro-micro-atmega32u4-5v-16mhz-presoldered-type-c-manual
// More examples: https://github.com/shillehtek/examples
//

// Scans the I2C bus and prints the address of every device
// it finds. Useful first sketch to verify SDA/SCL wiring.

#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial) { ; }  // Wait for native USB CDC port
  Serial.println("I2C Scanner");
}

void loop() {
  byte found = 0;

  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Device at 0x");
      if (addr < 16) Serial.print("0");
      Serial.println(addr, HEX);
      found++;
    }
  }

  if (found == 0) Serial.println("No devices found");
  delay(5000);
}

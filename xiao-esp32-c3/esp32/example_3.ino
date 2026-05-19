// Perform an I2C bus scan using the XIAO ESP32C3 default SDA and SCL pins (GPIO6 and GPIO7) and report any detected device addresses over Serial.
//
// Buy this module: https://shillehtek.com/products/xiao-seeed-esp32c3-pre-soldered-with-usb-to-usb-c-cable
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/xiao-seeed-esp32c3-pre-soldered-with-usb-to-usb-c-cable-manual
// More examples: https://github.com/shillehtek/examples
//

// XIAO ESP32-C3 - I2C Bus Scanner
// SDA = D4 (GPIO6), SCL = D5 (GPIO7)

#include <Wire.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  Wire.begin();   // Defaults to SDA=GPIO6, SCL=GPIO7 on XIAO ESP32-C3
  Serial.println("\nI2C Scanner");
}

void loop() {
  byte found = 0;
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.printf("  Found device at 0x%02X\n", addr);
      found++;
    }
  }
  Serial.printf("%d device(s) found.\n\n", found);
  delay(2000);
}

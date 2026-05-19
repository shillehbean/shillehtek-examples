// Scan the I2C bus (default SDA=GPIO6, SCL=GPIO7) and print any detected device addresses to Serial.
//
// Buy this module: https://shillehtek.com/products/esp32-c6-n4-dev-board-presoldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-c6-n4-dev-board-presoldered-manual
// More examples: https://github.com/shillehtek/examples
//

// Scan the I2C bus and report every device address found.
// Default pins: SDA=GPIO6, SCL=GPIO7.

#include <Wire.h>

void setup() {
  Wire.begin(6, 7);
  Serial.begin(115200);
  Serial.println("I2C Scanner");
}

void loop() {
  byte error, address;
  int nDevices = 0;

  Serial.println("Scanning...");
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("Found device at 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      nDevices++;
    }
  }

  if (nDevices == 0) Serial.println("No I2C devices found");
  delay(5000);
}

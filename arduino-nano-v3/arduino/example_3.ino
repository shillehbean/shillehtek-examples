// Scan the I2C bus using SDA=A4 and SCL=A5 and print the hexadecimal addresses of any detected devices.
//
// Buy this module: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-nano-v3-presoldered-ch340g-atmega328p-manual
// More examples: https://github.com/shillehtek/examples
//

// Scan the I2C bus and print the address of every device.
// Use SDA = A4 and SCL = A5 on the Nano.

#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
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
      Serial.print("I2C device found at 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      nDevices++;
    }
  }

  if (nDevices == 0) Serial.println("No I2C devices found");
  else { Serial.print(nDevices); Serial.println(" device(s) found"); }

  delay(5000);
}

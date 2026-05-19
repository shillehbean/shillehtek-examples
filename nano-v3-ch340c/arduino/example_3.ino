// Scan the I2C bus (SDA=A4, SCL=A5) and print any detected device addresses to Serial.
//
// Buy this module: https://shillehtek.com/products/arduino-nano-v3-0-atmega328p-16mhz-ch340c-type-c
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-nano-v3-0-atmega328p-16mhz-ch340c-type-c-manual
// More examples: https://github.com/shillehtek/examples
//

// Scan the I2C bus and print the addresses of any devices found
// Use SDA=A4, SCL=A5 on the Nano

#include 

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);
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

  if (nDevices == 0) {
    Serial.println("No I2C devices found");
  } else {
    Serial.print(nDevices);
    Serial.println(" device(s) found");
  }

  delay(5000);
}

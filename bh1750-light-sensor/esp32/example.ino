// Demonstrates BH1750 on an ESP32 (SDA GPIO21, SCL GPIO22), reading lux via I2C and printing to Serial every 500 ms.
//
// Buy this module: https://shillehtek.com/products/shillehtek-gy-302-bh1750-pre-soldered-light-intensity-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/bh1750-pre-soldered-light-intensity-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// BH1750 on ESP32 via I2C (GPIO21 SDA, GPIO22 SCL)
// Requires: BH1750 library

#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  if (!lightMeter.begin()) {
    Serial.println("BH1750 not found.");
    while (1);
  }
}

void loop() {
  float lux = lightMeter.readLightLevel();
  Serial.printf("Light: %.1f lx\n", lux);
  delay(500);
}

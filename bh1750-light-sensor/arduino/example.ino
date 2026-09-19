// Reads ambient light in lux using the BH1750 Arduino library over I2C and prints measurements to Serial every 500 ms.
//
// Buy this module: https://shillehtek.com/products/shillehtek-gy-302-bh1750-pre-soldered-light-intensity-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/bh1750-pre-soldered-light-intensity-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// BH1750 - Read ambient light in lux
// Requires: BH1750 library by Christopher Laws

#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  if (!lightMeter.begin()) {
    Serial.println("BH1750 not found. Check wiring.");
    while (1);
  }
  Serial.println("BH1750 ready.");
}

void loop() {
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(500);
}

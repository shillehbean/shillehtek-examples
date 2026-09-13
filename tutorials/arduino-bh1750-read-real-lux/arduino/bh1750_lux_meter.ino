// Reads light intensity from a BH1750 sensor over I2C and outputs lux to the Serial Monitor at 500 ms intervals.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-bh1750-read-real-lux
// Parts used: https://shillehtek.com/products/shillehtek-gy-302-bh1750-pre-soldered-light-intensity-module
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <BH1750.h>

BH1750 light;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  light.begin();
}

void loop() {
  float lux = light.readLightLevel();
  Serial.print("Lux: "); Serial.println(lux, 1);
  delay(500);
}

// Arduino sketch that initializes an HX711 load cell amplifier, tares the scale, applies a calibration factor, and prints weight readings to the Serial Monitor.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-hx711-load-cell-read-weight
// Parts used: https://shillehtek.com/products/hx711-weighing-pressure-sensor-module-large-presoldered
//             https://shillehtek.com/products/arduino-nano-v3-0-atmega328p-16mhz-ch340c-type-c
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include "HX711.h"

#define DOUT  6
#define CLK   5

HX711 scale;

float calibration_factor = -7050; 

void setup() {
  Serial.begin(9600);
  scale.begin(DOUT, CLK);

  scale.set_scale();
  scale.tare();

  Serial.println("HX711 scale test");
  Serial.println("Remove all weight from the scale");
  Serial.println("After readings begin, place a known weight on the scale");
}

void loop() {
  scale.set_scale(calibration_factor);

  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 2);
  Serial.println(" units");

  delay(500);
}

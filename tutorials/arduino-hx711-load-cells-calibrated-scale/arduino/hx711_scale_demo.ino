// Demo sketch that applies the calibrated scale factor and continuously prints weight readings (in pounds) to the serial console.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-hx711-load-cells-calibrated-scale
// Parts used: https://shillehtek.com/products/load-cell-50kg-half-bridge-strain-sensor
//             https://shillehtek.com/products/hx711-weighing-pressure-sensor-module-large-presoldered
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include "HX711.h"

#define calibration_factor -7050.0 // from the calibration sketch
#define LOADCELL_DOUT_PIN 3
#define LOADCELL_SCK_PIN 2

HX711 scale;

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 scale demo");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.tare();
  Serial.println("Readings:");
}

void loop() {
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 1);
  Serial.print(" lbs");
  Serial.println();
}

// Reads weight from an HX711 load cell, tares at startup, and prints calibrated gram measurements over Serial for calibration and monitoring.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-hx711-load-cell-digital-scale
// Parts used: https://shillehtek.com/products/hx711-weighing-pressure-sensor-module-large-presoldered
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <HX711.h>

const int DT  = 3;
const int SCK = 2;
HX711 scale;

float CAL_FACTOR = 420.0;   // start here; you’ll tune this

void setup() {
  Serial.begin(9600);
  scale.begin(DT, SCK);
  scale.set_scale(CAL_FACTOR);
  scale.tare();
  Serial.println("Tared. Place known weight...");
}

void loop() {
  Serial.print("Weight: ");
  Serial.print(scale.get_units(10), 1);
  Serial.println(" g");
  delay(500);
}

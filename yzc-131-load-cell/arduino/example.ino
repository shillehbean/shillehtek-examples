// Initial Arduino sketch that reads calibrated weight (grams) from the HX711-connected YZC-131 load cell, taring on startup and printing values to Serial every 500 ms.
//
// Buy this module: https://shillehtek.com/products/load-cell-5kg-yzc-131-with-wires
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/load-cell-5kg-yzc-131-with-wires-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include "HX711.h"

HX711 scale;
const int DT = 2, SCK = 3;

void setup() {
  Serial.begin(9600);
  scale.begin(DT, SCK);
  scale.set_scale(420.0);  // calibrate: see FAQ
  scale.tare();            // zero with no load
}

void loop() {
  Serial.println(scale.get_units(5), 1);  // grams
  delay(500);
}

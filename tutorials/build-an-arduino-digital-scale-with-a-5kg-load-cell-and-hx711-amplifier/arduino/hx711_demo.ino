// Simple demo sketch that applies a fixed calibration_factor, tares at boot, and continuously prints weight readings (in lbs) to the Serial monitor.
//
// Full tutorial: https://shillehtek.com/blogs/news/build-an-arduino-digital-scale-with-a-5kg-load-cell-and-hx711-amplifier
// Parts used: https://shillehtek.com/products/load-cell-5kg-hx711-arduino-esp32-kit
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// SparkFun HX711 demo sketch (Nathan Seidle, public domain)
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
  scale.tare(); // no weight at boot = zero

  Serial.println("Readings:");
}

void loop() {
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 1);
  Serial.print(" lbs");
  Serial.println();
}

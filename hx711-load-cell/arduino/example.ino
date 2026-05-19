// Arduino sketch using the HX711 library: initializes the HX711 on pins 3 and 2, tares the scale, applies a calibration factor, and prints averaged weight in grams to Serial every 500 ms.
//
// Buy this module: https://shillehtek.com/products/hx711-weighing-pressure-sensor-module-large-presoldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hx711-weighing-pressure-sensor-module-large-presoldered-manual
// More examples: https://github.com/shillehtek/examples
//

// HX711 Load Cell Amplifier - Arduino Example
// Library: "HX711" by Bogdan Necula (Arduino Library Manager)
// DT  -> Arduino Digital Pin 3
// SCK -> Arduino Digital Pin 2

#include "HX711.h"

const int DT_PIN  = 3;
const int SCK_PIN = 2;

HX711 scale;

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 Load Cell Demo");

  scale.begin(DT_PIN, SCK_PIN);

  // Replace this with your own calibration factor
  // (see the "calibrate" section in the README of the HX711 library)
  scale.set_scale(420.0983);

  // Tare the scale so the current weight reads as zero
  scale.tare();
  Serial.println("Tare complete. Place an item on the scale.");
}

void loop() {
  if (scale.is_ready()) {
    float weight = scale.get_units(10);  // average of 10 readings
    Serial.print("Weight: ");
    Serial.print(weight, 2);
    Serial.println(" g");
  } else {
    Serial.println("HX711 not ready. Check wiring.");
  }
  delay(500);
}

// Arduino example using the Bogde HX711 library to tare the scale, apply a calibration factor, and print raw and averaged weight (kg) readings over Serial.
//
// Buy this module: https://shillehtek.com/products/load-cell-50kg-half-bridge-strain-sensor
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/load-cell-50kg-half-bridge-strain-sensor-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// 4x 50kg Load Cells + HX711 - Arduino Body Scale Example
// DT -> D3, SCK -> D2, VCC -> 5V
// Library: "HX711" by Bogdan Necula (bogde)

#include "HX711.h"

const int DT_PIN = 3;
const int SCK_PIN = 2;

// After calibrating: factor = tared raw reading / known weight in kg
float CALIBRATION_FACTOR = 1.0;

HX711 scale;

void setup() {
  Serial.begin(9600);
  scale.begin(DT_PIN, SCK_PIN);

  Serial.println("Empty the platform... taring in 3 s");
  delay(3000);
  scale.tare(20);
  scale.set_scale(CALIBRATION_FACTOR);
  Serial.println("Ready - step on!");
}

void loop() {
  if (scale.is_ready()) {
    float kg = scale.get_units(10);   // average of 10 samples
    long raw = scale.get_value(10);   // tared raw (for calibration)

    Serial.print("Raw: ");
    Serial.print(raw);
    Serial.print("  |  Weight: ");
    Serial.print(kg, 2);
    Serial.println(" kg");
  }
  delay(500);
}

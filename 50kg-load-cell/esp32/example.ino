// ESP32 example using the Bogde HX711 library to tare the scale, set a calibration factor, and print averaged weight (kg) readings to the serial console.
//
// Buy this module: https://shillehtek.com/products/load-cell-50kg-half-bridge-strain-sensor
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/load-cell-50kg-half-bridge-strain-sensor-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// 4x 50kg Load Cells + HX711 - ESP32 Example
// DT -> GPIO 16, SCK -> GPIO 4, VCC -> 3V3
// Library: "HX711" by Bogdan Necula

#include "HX711.h"

HX711 scale;
float CALIBRATION_FACTOR = 1.0;   // set after calibrating

void setup() {
  Serial.begin(115200);
  scale.begin(16, 4);               // DT, SCK

  Serial.println("Empty the platform... taring in 3 s");
  delay(3000);
  scale.tare(20);
  scale.set_scale(CALIBRATION_FACTOR);
  Serial.println("Ready - step on!");
}

void loop() {
  if (scale.wait_ready_timeout(1000)) {
    Serial.printf("Weight: %.2f kg\n", scale.get_units(10));
  }
  delay(500);
}

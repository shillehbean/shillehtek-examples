// Uses the Adafruit VL53L0X Arduino library to initialize the sensor and print single-shot distance measurements over Serial.
//
// Buy this module: https://shillehtek.com/products/gy-vl53l0xv2-laser-ranging-tof-sensor-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gy-vl53l0xv2-laser-ranging-tof-sensor-module-manual
// More examples: https://github.com/shillehtek/examples
//

// VL53L0X Time-of-Flight ranging
// Install: Arduino Library Manager → "Adafruit VL53L0X"
// Wiring: VCC->5V, GND->GND, SCL->A5, SDA->A4

#include <Wire.h>
#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("VL53L0X: initializing...");
  if (!lox.begin()) {
    Serial.println("Failed to boot VL53L0X. Check wiring.");
    while (1);
  }
  Serial.println("VL53L0X ready.");
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) {  // 4 = out of range
    Serial.print("Distance (mm): ");
    Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println("Out of range");
  }
  delay(100);
}

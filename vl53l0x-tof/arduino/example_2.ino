// Uses the Pololu VL53L0X Arduino library to configure long-range settings, start continuous measurements, and print continuous distance readings.
//
// Buy this module: https://shillehtek.com/products/gy-vl53l0xv2-laser-ranging-tof-sensor-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gy-vl53l0xv2-laser-ranging-tof-sensor-module-manual
// More examples: https://github.com/shillehtek/examples
//

// VL53L0X in Long Range mode (up to ~2m outdoors, ~1.5m in ambient light)
// Uses Pololu VL53L0X library for finer control
// Install: Arduino Library Manager → "VL53L0X by Pololu"

#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init()) {
    Serial.println("Failed to detect VL53L0X");
    while (1);
  }

  // Long range: lower signal rate limit, wider pulse period
  sensor.setSignalRateLimit(0.1);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  sensor.setMeasurementTimingBudget(33000); // ~33 ms

  sensor.startContinuous();
}

void loop() {
  uint16_t distance = sensor.readRangeContinuousMillimeters();
  Serial.print("Distance (mm): ");
  Serial.println(distance);
  if (sensor.timeoutOccurred()) Serial.println("Timeout!");
  delay(50);
}

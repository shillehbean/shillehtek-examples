// Sets up the VL53L1X on an ESP32 (explicit SDA/SCL pins) in short distance (fast) mode with a 20 ms timing budget and continuously prints distances to Serial at ~50 Hz.
//
// Buy this module: https://shillehtek.com/products/vl53l1x-tof-sensor-4m-pre-soldered-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/vl53l1x-tof-sensor-4m-pre-soldered-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <VL53L1X.h>

VL53L1X sensor;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);          // SDA, SCL
  sensor.setTimeout(500);
  if (!sensor.init()) {
    Serial.println("VL53L1X not found");
    while (1);
  }
  sensor.setDistanceMode(VL53L1X::Short);     // fastest, ~1.3 m
  sensor.setMeasurementTimingBudget(20000);   // 20 ms -> 50 Hz
  sensor.startContinuous(20);
}

void loop() {
  Serial.printf("Distance: %d mm\n", sensor.read());
}

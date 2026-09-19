// Initializes the VL53L1X in long-range mode (~4 m), starts continuous readings with a 50 ms timing budget, and prints distance in millimeters to the Serial console.
//
// Buy this module: https://shillehtek.com/products/vl53l1x-tof-sensor-4m-pre-soldered-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/vl53l1x-tof-sensor-4m-pre-soldered-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Library Manager: install "VL53L1X" by Pololu
#include <Wire.h>
#include <VL53L1X.h>

VL53L1X sensor;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  sensor.setTimeout(500);
  if (!sensor.init()) {
    Serial.println("VL53L1X not found - check wiring");
    while (1);
  }
  sensor.setDistanceMode(VL53L1X::Long);      // up to ~4 m
  sensor.setMeasurementTimingBudget(50000);   // 50 ms per reading
  sensor.startContinuous(50);
}

void loop() {
  int mm = sensor.read();
  Serial.print("Distance: ");
  Serial.print(mm);
  Serial.println(" mm");
}

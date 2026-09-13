// Reads distance from a VL53L0X ToF sensor using the Adafruit library and prints millimetre measurements (or out-of-range) over Serial at 115200 baud.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-vl53l0x-millimetre-distance-serial
// Parts used: https://shillehtek.com/products/gy-vl53l0xv2-laser-ranging-tof-sensor-module
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X tof;

void setup() {
  Serial.begin(115200);
  if (!tof.begin()) { Serial.println("VL53L0X not found"); while (1); }
}

void loop() {
  VL53L0X_RangingMeasurementData_t m;
  tof.rangingTest(&m, false);
  if (m.RangeStatus != 4) {
    Serial.print("Distance: "); Serial.print(m.RangeMilliMeter); Serial.println(" mm");
  } else {
    Serial.println("Out of range");
  }
  delay(100);
}

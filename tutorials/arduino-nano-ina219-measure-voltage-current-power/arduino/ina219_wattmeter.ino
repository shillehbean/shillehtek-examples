// Reads shunt voltage, bus voltage, current (mA) and power (mW) from an INA219 sensor and prints the values to the Serial console every 500 ms.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ina219-measure-voltage-current-power
// Parts used: https://shillehtek.com/products/cjmcu-219-ina219-i2c-bi-directional-current-power-monitoring-sensor-module-with-soldering-and-foam
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_INA219.h>
Adafruit_INA219 ina;
void setup() {
  Serial.begin(9600);
  if (!ina.begin()) { Serial.println("INA219 not found"); while(1); }
}
void loop() {
  float shunt = ina.getShuntVoltage_mV();
  float bus   = ina.getBusVoltage_V();
  float ma    = ina.getCurrent_mA();
  float mw    = ina.getPower_mW();
  Serial.print("V="); Serial.print(bus, 2);
  Serial.print(" I="); Serial.print(ma, 2); Serial.print("mA");
  Serial.print(" P="); Serial.print(mw, 2); Serial.println("mW");
  delay(500);
}

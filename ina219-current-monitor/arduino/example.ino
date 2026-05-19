// Uses the Adafruit_INA219 Arduino library to initialize the INA219, set a 32V/2A calibration, and print bus voltage, load voltage, current (mA) and power (mW) to Serial every second.
//
// Buy this module: https://shillehtek.com/products/cjmcu-219-ina219-i2c-bi-directional-current-power-monitoring-sensor-module-with-soldering-and-foam
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/cjmcu-219-ina219-i2c-bi-directional-current-power-monitoring-sensor-module-with-soldering-and-foam-manual
// More examples: https://github.com/shillehtek/examples
//

// INA219 - Arduino Example
// Library: Adafruit INA219

#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

void setup() {
  Serial.begin(9600);
  if (!ina219.begin()) {
    Serial.println("INA219 not found at 0x40");
    while (1);
  }
  // ina219.setCalibration_16V_400mA();   // for low-current logging
  // ina219.setCalibration_32V_1A();      // for typical projects
  ina219.setCalibration_32V_2A();         // default
}

void loop() {
  float busV   = ina219.getBusVoltage_V();
  float shuntV = ina219.getShuntVoltage_mV();
  float current_mA = ina219.getCurrent_mA();
  float power_mW   = ina219.getPower_mW();
  float loadV  = busV + (shuntV / 1000.0);

  Serial.print("Bus: ");   Serial.print(busV); Serial.println(" V");
  Serial.print("Load: ");  Serial.print(loadV); Serial.println(" V");
  Serial.print("Current: ");Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power: ");  Serial.print(power_mW); Serial.println(" mW");
  Serial.println();
  delay(1000);
}

// Scans a shared 1-Wire bus for multiple DS18B20 probes on Arduino and prints each sensor's temperature in Celsius.
//
// Buy this module: https://shillehtek.com/products/ds18b20-waterproof-digital-temp-sensor-probe-1m-for-arduino-pi
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ds18b20-waterproof-digital-temp-sensor-probe-1m-for-arduino-pi-manual
// More examples: https://github.com/shillehtek/examples
//

// DS18B20 - Multiple probes sharing one data wire
// All sensors share Red, Black, Yellow; one 4.7k pull-up for the whole bus

#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(2);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
  Serial.print("Found "); Serial.print(sensors.getDeviceCount()); Serial.println(" sensors");
}

void loop() {
  sensors.requestTemperatures();
  for (int i = 0; i < sensors.getDeviceCount(); i++) {
    Serial.print("Sensor "); Serial.print(i); Serial.print(": ");
    Serial.print(sensors.getTempCByIndex(i)); Serial.println(" C");
  }
  Serial.println("---");
  delay(2000);
}

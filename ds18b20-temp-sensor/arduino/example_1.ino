// Reads temperature from a single DS18B20 on Arduino using OneWire/DallasTemperature and prints Celsius and Fahrenheit to Serial every second.
//
// Buy this module: https://shillehtek.com/products/ds18b20-waterproof-digital-temp-sensor-probe-1m-for-arduino-pi
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ds18b20-waterproof-digital-temp-sensor-probe-1m-for-arduino-pi-manual
// More examples: https://github.com/shillehtek/examples
//

// DS18B20 - Read temperature on Arduino
// Wire: Red=5V, Black=GND, Yellow=D2 with 4.7k pull-up to 5V
// Install libraries: OneWire, DallasTemperature

#include <OneWire.h>
#include <DallasTemperature.h>

const int ONE_WIRE_BUS = 2;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
  float c = sensors.getTempCByIndex(0);
  float f = c * 9.0 / 5.0 + 32.0;

  Serial.print("Temp: "); Serial.print(c, 2); Serial.print(" C  /  ");
  Serial.print(f, 2); Serial.println(" F");
  delay(1000);
}

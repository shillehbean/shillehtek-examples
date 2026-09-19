// Reads the thermistor via an analog divider on A0, computes resistance and temperature using the beta (Steinhart) equation, and prints Celsius and Fahrenheit over Serial.
//
// Buy this module: https://shillehtek.com/products/10k-ntc-thermistor-temperature-sensor-mf52-103
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/10k-ntc-thermistor-temperature-sensor-mf52-103-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MF52-103 10K NTC Thermistor - Arduino Example
// Divider: 5V - thermistor - A0 - 10k - GND

#include <math.h>

const int   PIN      = A0;
const float SERIES_R = 10000.0;   // fixed resistor (measure yours!)
const float NOMINAL  = 10000.0;   // 10k at 25 C
const float B_COEFF  = 3950.0;
const float T_NOMINAL = 25.0;

float readTempC() {
  long total = 0;
  for (int i = 0; i < 20; i++) { total += analogRead(PIN); delay(5); }
  float adc = total / 20.0;                     // 0..1023

  // Thermistor is on TOP of the divider:
  // Vout = Vcc * R_fixed / (R_ntc + R_fixed)  =>  R_ntc = R_fixed*(1023/adc - 1)
  float rNtc = SERIES_R * (1023.0 / adc - 1.0);

  float steinhart = logf(rNtc / NOMINAL) / B_COEFF     // Beta equation
                  + 1.0 / (T_NOMINAL + 273.15);
  return 1.0 / steinhart - 273.15;
}

void setup() {
  Serial.begin(9600);
  Serial.println("MF52-103 thermistor ready");
}

void loop() {
  float c = readTempC();
  Serial.print("Temperature: ");
  Serial.print(c, 1);
  Serial.print(" C  /  ");
  Serial.print(c * 9.0 / 5.0 + 32.0, 1);
  Serial.println(" F");
  delay(1000);
}

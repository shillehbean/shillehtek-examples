// Reads the MQ-2 via an ESP32 ADC input behind a 2:1 voltage divider, converts the raw ADC value to the measured pin voltage and the real sensor voltage, and prints the results over Serial.
//
// Buy this module: https://shillehtek.com/products/mq-2-flammable-gas-smoke-sensor-module-for-arduino-safety
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mq-2-flammable-gas-smoke-sensor-module-for-arduino-safety-manual
// More examples: https://github.com/shillehtek/examples
//

// MQ-2 on ESP32 - read AO through a 2:1 divider

const int   aoPin   = 34;
const float VREF    = 3.3;
const float DIVIDER = 0.5;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
}

void loop() {
  int raw = analogRead(aoPin);
  float vAtPin = raw * VREF / 4095.0;
  float vReal  = vAtPin / DIVIDER;
  Serial.printf("Raw=%4d  Vpin=%.3f  Vreal=%.3f V\n", raw, vAtPin, vReal);
  delay(500);
}

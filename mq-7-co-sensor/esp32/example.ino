// Reads the MQ-7 via the ESP32 ADC on GPIO34 with 11dB attenuation, converts the 0–4095 raw reading to a voltage and compensates for a 1.5× resistor divider, then prints the sensor voltage.
//
// Buy this module: https://shillehtek.com/products/mq-7-co-gas-sensor-module-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mq-7-co-gas-sensor-module-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MQ-7 A0 -> 10k/20k divider -> GPIO 34 (see wiring tab)
const int AO_PIN = 34;
const float DIVIDER = 1.5;   // recovers the pre-divider voltage

void setup() {
  Serial.begin(115200);
  analogSetPinAttenuation(AO_PIN, ADC_11db);  // full 0-3.3 V range
}

void loop() {
  int raw = analogRead(AO_PIN);          // 0-4095
  float vAdc = raw * (3.3 / 4095.0);
  float vSensor = vAdc * DIVIDER;
  Serial.printf("Raw: %d  Sensor: %.2f V\n", raw, vSensor);
  delay(1000);
}

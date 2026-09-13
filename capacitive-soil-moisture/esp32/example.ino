// Reads the sensor from an ESP32 ADC pin (GPIO34) with 12-bit resolution and 11dB attenuation, converts a calibrated raw ADC value into a moisture percentage, and logs the result over Serial.
//
// Buy this module: https://shillehtek.com/products/Analog
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/capacitive-soil-moisture-sensor-v1-2-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Capacitive Soil Moisture Sensor V1.2 - ESP32
// AOUT -> GPIO34, VCC -> 3.3V, GND -> GND

const int SOIL_PIN = 34;

// 12-bit ADC: 0-4095. Calibrate these:
const int DRY_VALUE = 3000;
const int WET_VALUE = 1200;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db); // full 0-3.3V range
}

void loop() {
  int raw = analogRead(SOIL_PIN);
  int clamped = constrain(raw, WET_VALUE, DRY_VALUE);
  int percent = map(clamped, DRY_VALUE, WET_VALUE, 0, 100);

  Serial.printf("Raw: %d  Moisture: %d%%\n", raw, percent);
  delay(1000);
}

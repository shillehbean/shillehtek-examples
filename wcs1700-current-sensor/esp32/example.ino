// Reads the WCS1700 through a 2:1 voltage divider on an ESP32, auto-calibrates the ADC zero offset, reconstructs the sensor voltage, and computes current in amps.
//
// Buy this module: https://shillehtek.com/products/wcs1700-70a-hall-current-sensor-module-overcurrent-detect
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/wcs1700-70a-hall-current-sensor-module-overcurrent-detect-manual
// More examples: https://github.com/shillehtek/examples
//

// WCS1700 on ESP32 - measure current with a 2:1 divider on Aout
// Aout -> 10k -> GPIO34 -> 10k -> GND

const int  aoutPin     = 34;
const float VREF       = 3.3;       // ADC reference
const float DIVIDER    = 0.5;       // 2:1 voltage divider
const float SENSITIVITY = 0.032;    // V/A
float       offsetVolts = 1.25;     // 2.5V * 0.5 (divided)

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);  // 0 - 4095
  delay(500);

  long sum = 0;
  for (int i = 0; i < 500; i++) { sum += analogRead(aoutPin); delay(2); }
  offsetVolts = (sum / 500.0) * VREF / 4095.0;
}

void loop() {
  int raw = analogRead(aoutPin);
  float vAtPin = raw * VREF / 4095.0;
  float vReal  = vAtPin / DIVIDER;
  float amps   = (vReal - (offsetVolts / DIVIDER)) / SENSITIVITY;

  Serial.printf("Vpin=%.3f  Vreal=%.3f  I=%.2f A\n", vAtPin, vReal, amps);
  delay(250);
}

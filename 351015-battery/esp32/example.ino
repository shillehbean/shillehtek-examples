// Measures a 1S LiPo on ESP32 GPIO34 using analogReadMilliVolts with averaging and ADC attenuation, computes cell voltage and percent state-of-charge, prints to Serial and signals low battery.
//
// Buy this module: https://shillehtek.com/products/3.7V
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/351015-500mah-3-7v-lithium-rechargeable-battery-3-5-x-10-x-15mm-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// 351015 LiPo cell voltage monitor for ESP32
// Wiring: Cell (+) -- 100k -- GPIO34 -- 100k -- GND
// GPIO34 is an input-only ADC1 pin (safe for use during Wi-Fi).
// ESP32 ADC is nonlinear - we use analogReadMilliVolts() for a calibrated reading.

const int BAT_PIN   = 34;
const float DIVIDER = 2.0;     // R1 = R2 = 100k

float readCellVoltage() {
  uint32_t sumMv = 0;
  for (int i = 0; i < 32; i++) {
    sumMv += analogReadMilliVolts(BAT_PIN);  // returns calibrated mV
    delay(2);
  }
  float vpin = (sumMv / 32.0) / 1000.0;       // average, convert to volts
  return vpin * DIVIDER;
}

void setup() {
  Serial.begin(115200);
  analogSetPinAttenuation(BAT_PIN, ADC_11db); // ~0 - 3.3V input range
}

void loop() {
  float v = readCellVoltage();
  float soc = (v - 3.0) / 1.2 * 100.0;
  if (soc < 0)   soc = 0;
  if (soc > 100) soc = 100;

  Serial.printf("LiPo: %.2f V  (%.0f%%)\n", v, soc);
  if (v < 3.1) Serial.println("Low battery - going to deep sleep");
  delay(2000);
}

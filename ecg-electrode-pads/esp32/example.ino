// Samples the AD8232 OUTPUT on ESP32 ADC1 (GPIO34) with 11dB attenuation and prints 0 on lead-off or the 0–4095 ADC value at ~500 Hz.
//
// Buy this module: https://shillehtek.com/products/ecg-electrode-pads-ad8232-5-pack
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ecg-electrode-pads-ad8232-5-pack-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// OUTPUT -> GPIO 34 (ADC1), LO+ -> GPIO 25, LO- -> GPIO 26
const int ECG = 34, LO_PLUS = 25, LO_MINUS = 26;

void setup() {
  Serial.begin(115200);
  pinMode(LO_PLUS, INPUT);
  pinMode(LO_MINUS, INPUT);
  analogSetPinAttenuation(ECG, ADC_11db);   // full 0-3.3 V range
}

void loop() {
  if (digitalRead(LO_PLUS) || digitalRead(LO_MINUS)) {
    Serial.println(0);
  } else {
    Serial.println(analogRead(ECG));        // 0-4095
  }
  delayMicroseconds(2000);                  // 500 Hz
}

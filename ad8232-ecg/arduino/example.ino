// Reads raw ECG samples from the AD8232 on A0, detects leads-off via two digital pins, and streams values to the Serial Plotter at ~200 Hz.
//
// Buy this module: https://shillehtek.com/products/ad8232-ecg-module-heart-rate-ecg-monitoring-sensor-kit
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ad8232-ecg-module-heart-rate-ecg-monitoring-sensor-kit-manual
// More examples: https://github.com/shillehtek/examples
//

// AD8232 ECG Module - Arduino Example
// Prints raw ECG samples for the Arduino Serial Plotter.
// OUTPUT -> A0, LO+ -> D10, LO- -> D11

const int OUTPUT_PIN = A0;
const int LO_PLUS    = 10;
const int LO_MINUS   = 11;

void setup() {
  Serial.begin(9600);
  pinMode(LO_PLUS,  INPUT);
  pinMode(LO_MINUS, INPUT);
}

void loop() {
  // Leads-off detection: either line goes HIGH when an electrode is disconnected
  if (digitalRead(LO_PLUS) == HIGH || digitalRead(LO_MINUS) == HIGH) {
    Serial.println(0);   // Plot a flat line while leads are off
  } else {
    int ecg = analogRead(OUTPUT_PIN);  // 0 - 1023 on Arduino
    Serial.println(ecg);
  }

  // ~200 Hz sample rate
  delay(5);
}

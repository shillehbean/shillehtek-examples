// Reads the AD8232 analog OUTPUT on A0 and reports either the ECG waveform (analogRead) or 0 when LO+ or LO- indicate a lead-off, printing at ~500 samples/s to the Serial Plotter.
//
// Buy this module: https://shillehtek.com/products/ecg-electrode-pads-ad8232-5-pack
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ecg-electrode-pads-ad8232-5-pack-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// AD8232: OUTPUT -> A0, LO+ -> D11, LO- -> D10, 3.3V, GND
// Open Tools > Serial Plotter at 115200 baud
const int LO_PLUS = 11, LO_MINUS = 10;

void setup() {
  Serial.begin(115200);
  pinMode(LO_PLUS, INPUT);
  pinMode(LO_MINUS, INPUT);
}

void loop() {
  if (digitalRead(LO_PLUS) == HIGH || digitalRead(LO_MINUS) == HIGH) {
    Serial.println(0);              // an electrode came loose
  } else {
    Serial.println(analogRead(A0)); // the ECG waveform
  }
  delay(2);                          // ~500 samples/second
}

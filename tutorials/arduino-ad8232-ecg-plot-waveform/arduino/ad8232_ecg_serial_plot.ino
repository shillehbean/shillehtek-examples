// Reads AD8232 lead-off pins and the analog ECG output; prints '!' when an electrode is disconnected, otherwise prints the analog A0 value at ~500 Hz for plotting.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-ad8232-ecg-plot-waveform
// Parts used: https://shillehtek.com/products/ad8232-ecg-module-heart-rate-sensor-kit
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

void setup() {
  Serial.begin(9600);
  pinMode(10, INPUT); // LO-
  pinMode(11, INPUT); // LO+
}

void loop() {
  if (digitalRead(10) == HIGH || digitalRead(11) == HIGH) {
    Serial.println('!');           // electrode disconnected
  } else {
    Serial.println(analogRead(A0));
  }
  delay(2);                         // ~500 Hz sample rate
}

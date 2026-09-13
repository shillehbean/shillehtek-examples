// Reads the AD8232 ECG analog output on A0 and monitors lead-off pins on D10/D11, sending either the analog value or a '!' marker over serial at 9600 baud.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-ad8232-ecg-plot-waveforms
// Parts used: https://shillehtek.com/products/ad8232-ecg-module-heart-rate-sensor-kit
//             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
//             https://shillehtek.com/products/shillehtek-400-point-breadboard
// More examples: https://github.com/shillehbean/shillehtek-examples
//

void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);
  pinMode(10, INPUT); // Setup for leads-off detection LO+
  pinMode(11, INPUT); // Setup for leads-off detection LO-
}

void loop() {
  if ((digitalRead(10) == 1) || (digitalRead(11) == 1)) {
    Serial.println('!');
  } else {
    // Send the analog ECG value from A0
    Serial.println(analogRead(A0));
  }
  // Small delay to avoid saturating the serial buffer
  delay(1);
}

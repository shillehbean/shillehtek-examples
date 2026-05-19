// Read the module's analog SIG on A0, print the raw ADC value at ~50 Hz, and flag a "flex" when the reading exceeds a configurable threshold.
//
// Buy this module: https://shillehtek.com/products/emg-muscle-signal-sensor-module-kit-for-arduino-robotics
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/emg-muscle-signal-sensor-module-kit-for-arduino-robotics-manual
// More examples: https://github.com/shillehtek/examples
//

// ShillehTek EMG Sensor - Arduino Example
// Reads the analog signal from the EMG module on A0, prints
// raw value + a simple "flex detected" flag based on a threshold.

const int EMG_PIN = A0;
const int FLEX_THRESHOLD = 400;   // tune this by watching your resting value

void setup() {
  Serial.begin(9600);
  pinMode(EMG_PIN, INPUT);
}

void loop() {
  int raw = analogRead(EMG_PIN);

  Serial.print("EMG: ");
  Serial.print(raw);
  if (raw > FLEX_THRESHOLD) {
    Serial.println("  FLEX!");
  } else {
    Serial.println("");
  }

  delay(20);  // ~50 Hz sample rate
}

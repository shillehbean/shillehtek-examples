// Uses an ESP32 ADC to measure VBUS and drives a relay on GPIO25 to disconnect the load if the measured voltage exceeds an expected PD setting plus tolerance.
//
// Buy this module: https://shillehtek.com/products/Arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pdsink-pd-decoy-pd-fast-charging-test-board-5-20v-manual
// More examples: https://github.com/shillehtek/examples
//

// ESP32 PD Decoy monitor with relay cutoff
// VBUS -- 1M -- GPIO34 -- 100k -- GND (20V max -- 1.82V at ADC)
// Relay on GPIO25 opens load if voltage exceeds expected setting

const int adcPin = 34;
const int relayPin = 25;
const float dividerRatio = 11.0;
const float vRef = 3.3;
const float expectedV = 12.0;     // We set DIP for 12V
const float toleranceV = 2.0;     // +/- 2V tolerance

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  analogReadResolution(12);
}

void loop() {
  int raw = analogRead(adcPin);
  float vOut = (raw / 4095.0) * vRef * dividerRatio;

  if (vOut > expectedV + toleranceV) {
    digitalWrite(relayPin, HIGH);   // Open relay -- disconnect load
    Serial.printf("FAULT %.2f V (expected %.0f) -- relay opened\n", vOut, expectedV);
  } else {
    digitalWrite(relayPin, LOW);
    Serial.printf("Output: %.2f V (OK)\n", vOut);
  }
  delay(1000);
}

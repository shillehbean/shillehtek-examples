// Reads the LM2596 output through a 10k:2k voltage divider on A0, scales the ADC reading to the rail voltage (up to 30V), and prints the measured voltage to Serial every 500 ms.
//
// Buy this module: https://shillehtek.com/products/shillehtek-lm2596-dc-dc-adjustable-step-down-power-supply-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-lm2596-dc-dc-adjustable-step-down-power-supply-module-manual
// More examples: https://github.com/shillehtek/examples
//

// Read LM2596 OUT+ through a 10k:2k voltage divider on A0.
// Divider ratio = 2k / (10k + 2k) = 1/6
// So Arduino reads up to 5V * 6 = 30V on the rail.

const int sensePin = A0;
const float dividerRatio = 6.0;
const float adcRef = 5.0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(sensePin);
  float vAtPin = (raw / 1023.0) * adcRef;
  float vRail = vAtPin * dividerRatio;
  Serial.print("LM2596 output: ");
  Serial.print(vRail, 2);
  Serial.println(" V");
  delay(500);
}

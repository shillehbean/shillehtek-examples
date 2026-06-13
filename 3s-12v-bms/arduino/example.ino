// Reads the 3S pack voltage via a 470k/100k divider on Arduino A0, converts the ADC reading to pack voltage and prints the voltage and a simple percent state-of-charge (9.6–12.6V range).
//
// Buy this module: https://shillehtek.com/products/12V
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/3s-12v-18650-lithium-battery-protection-board-11-1v-12-6v-balanced-25a-manual
// More examples: https://github.com/shillehtek/examples
//

// 3S Pack Voltage Monitor for Arduino
// Voltage divider: P+ -- 470k -- A0 -- 100k -- GND
// Max ADC voltage: 12.6V * (100 / 570) = 2.21V (safely under 5V)

const int adcPin = A0;
const float dividerRatio = (470.0 + 100.0) / 100.0;  // = 5.7
const float vRef = 5.0;

float pctFromVoltage(float v) {
  if (v >= 12.6) return 100.0;
  if (v <= 9.6) return 0.0;
  return ((v - 9.6) / (12.6 - 9.6)) * 100.0;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(adcPin);
  float vAdc = (raw / 1023.0) * vRef;
  float vPack = vAdc * dividerRatio;

  Serial.print("Pack: ");
  Serial.print(vPack, 2);
  Serial.print(" V (");
  Serial.print(pctFromVoltage(vPack), 0);
  Serial.println(" %)");
  delay(1000);
}

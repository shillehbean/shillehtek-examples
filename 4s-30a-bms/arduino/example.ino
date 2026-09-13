// Reads a 4S pack voltage via a 680k/100k divider on A0, computes pack voltage and state-of-charge percentage, and prints results over Serial.
//
// Buy this module: https://shillehtek.com/products/14.8V
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4s-30a-18650-lithium-battery-protection-board-14-8v-16v-with-cable-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// 4S Pack Voltage Monitor for Arduino
// Voltage divider: P+ -- 680k -- A0 -- 100k -- GND
// Max ADC voltage at 16.8V: 16.8 * (100 / 780) = 2.15V

const int adcPin = A0;
const float dividerRatio = (680.0 + 100.0) / 100.0;  // = 7.8
const float vRef = 5.0;
const float fullV = 16.8;
const float emptyV = 12.0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(adcPin);
  float vAdc = (raw / 1023.0) * vRef;
  float vPack = vAdc * dividerRatio;

  float pct = ((vPack - emptyV) / (fullV - emptyV)) * 100.0;
  if (pct > 100) pct = 100;
  if (pct < 0) pct = 0;

  Serial.print("Pack: ");
  Serial.print(vPack, 2);
  Serial.print(" V (");
  Serial.print(pct, 0);
  Serial.println(" %)");
  delay(1000);
}

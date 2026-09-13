// Reads a 2S Li-ion pack voltage on A0 using a 220k/100k divider, computes the pack voltage and a percent state-of-charge (6.0–8.4V range), and prints the values to Serial every second.
//
// Buy this module: https://shillehtek.com/products/18650
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hx-2s-jh20-2s-7-4v-18650-lithium-battery-protection-board-10a-with-balancer-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// HX-2S-JH20 Pack Voltage Monitor for Arduino
// Voltage divider: P+ -- 220k -- A0 -- 100k -- GND (max ~8.4V/3.2 = 2.6V at A0)

const int adcPin = A0;
const float dividerRatio = (220.0 + 100.0) / 100.0;  // = 3.2
const float vRef = 5.0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(adcPin);
  float vAdc = (raw / 1023.0) * vRef;
  float vPack = vAdc * dividerRatio;

  float pct = ((vPack - 6.0) / (8.4 - 6.0)) * 100.0;
  if (pct > 100) pct = 100;
  if (pct < 0) pct = 0;

  Serial.print("Pack: ");
  Serial.print(vPack, 2);
  Serial.print(" V (");
  Serial.print(pct, 0);
  Serial.println(" %)");
  delay(1000);
}

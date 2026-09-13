// Reads a single-cell battery voltage on an Arduino via a 100k/100k divider (A0), converts the ADC result to battery voltage, estimates a rough state-of-charge percentage, and prints the values to Serial every second.
//
// Buy this module: https://shillehtek.com/products/18650
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/1s-3-7v-3a-2mos-bms-li-ion-18650-battery-protection-board-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// 1S BMS Battery Voltage Monitor
// Connect P+ to a voltage divider (100k / 100k) and read midpoint with A0
// Vbat range: 2.5V (cutoff) to 4.2V (full)

const int adcPin = A0;
const float dividerRatio = 2.0;        // 100k + 100k = halves the voltage
const float vRef = 5.0;                // Arduino Uno reference

void setup() {
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(adcPin);
  float vAdc = (raw / 1023.0) * vRef;
  float vBat = vAdc * dividerRatio;

  // Map to a percentage (very rough)
  float pct = ((vBat - 3.0) / (4.2 - 3.0)) * 100.0;
  if (pct > 100) pct = 100;
  if (pct < 0) pct = 0;

  Serial.print("Battery: ");
  Serial.print(vBat, 2);
  Serial.print(" V (");
  Serial.print(pct, 0);
  Serial.println(" %)");
  delay(1000);
}

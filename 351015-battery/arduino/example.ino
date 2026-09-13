// Reads a 1S LiPo voltage on an Arduino Uno/Nano using a 100k/100k divider, averages ADC samples, converts to cell voltage, estimates state-of-charge, prints to Serial and warns on low voltage.
//
// Buy this module: https://shillehtek.com/products/3.7V
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/351015-500mah-3-7v-lithium-rechargeable-battery-3-5-x-10-x-15mm-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// 351015 LiPo cell voltage monitor for Arduino Uno / Nano (5V, 10-bit ADC)
// Wiring: Cell (+) -- 100k -- A0 -- 100k -- GND
// Divider ratio = 0.5, so multiply ADC voltage x 2 to get cell voltage.

const int BAT_PIN   = A0;
const float VREF    = 5.0;     // 5V Arduino reference
const float DIVIDER = 2.0;     // (R1 + R2) / R2 with R1 = R2 = 100k

float readCellVoltage() {
  long sum = 0;
  for (int i = 0; i < 16; i++) {       // average 16 samples to reduce noise
    sum += analogRead(BAT_PIN);
    delay(2);
  }
  float adc = sum / 16.0;
  float vpin = (adc / 1023.0) * VREF;
  return vpin * DIVIDER;
}

int stateOfCharge(float v) {
  // Rough linear SoC map for 1S LiPo (3.0V empty, 4.2V full)
  float pct = (v - 3.0) / (4.2 - 3.0) * 100.0;
  if (pct < 0)   pct = 0;
  if (pct > 100) pct = 100;
  return (int)pct;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  float v = readCellVoltage();
  int   soc = stateOfCharge(v);
  Serial.print("Cell: ");
  Serial.print(v, 2);
  Serial.print(" V  (");
  Serial.print(soc);
  Serial.println("%)");

  if (v < 3.1) Serial.println("WARNING: cell near empty - stop discharge.");
  delay(2000);
}

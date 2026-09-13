// Reads a battery voltage via a 2:1 resistor divider on A0, prints the cell voltage and a simple charge-state classification over Serial on an Arduino.
//
// Buy this module: https://shillehtek.com/products/Arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tp4056-1a-lipo-battery-charging-board-type-c-with-current-protection-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// TP4056 Cell Voltage Monitor for Arduino
// Connect OUT+ to a 100k/100k divider and read midpoint with A0

const int adcPin = A0;
const float dividerRatio = 2.0;
const float vRef = 5.0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(adcPin);
  float vAdc = (raw / 1023.0) * vRef;
  float vBat = vAdc * dividerRatio;

  Serial.print("Cell: ");
  Serial.print(vBat, 2);
  Serial.print(" V");

  if (vBat > 4.15) Serial.println(" -- FULL");
  else if (vBat > 3.7) Serial.println(" -- GOOD");
  else if (vBat > 3.3) Serial.println(" -- LOW");
  else Serial.println(" -- CRITICAL");

  delay(1000);
}

// Reads a voltage divider on A0 to calculate the PD VBUS voltage and prints the measured voltage and inferred PD profile over serial.
//
// Buy this module: https://shillehtek.com/products/Arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pdsink-pd-decoy-pd-fast-charging-test-board-5-20v-manual
// More examples: https://github.com/shillehtek/examples
//

// PD Decoy Output Voltage Monitor for Arduino
// Voltage divider sized for 20V max: VBUS -- 1M -- A0 -- 100k -- GND
// Max ADC voltage: 20 * (100 / 1100) = 1.82V (safely under 5V)

const int adcPin = A0;
const float dividerRatio = (1000.0 + 100.0) / 100.0;  // = 11.0
const float vRef = 5.0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(adcPin);
  float vAdc = (raw / 1023.0) * vRef;
  float vOut = vAdc * dividerRatio;

  Serial.print("Output: ");
  Serial.print(vOut, 2);
  Serial.println(" V");

  // Identify which PD profile is active
  if      (vOut > 18.5) Serial.println("  Profile: 20V");
  else if (vOut > 13.5) Serial.println("  Profile: 15V");
  else if (vOut > 10.5) Serial.println("  Profile: 12V");
  else if (vOut >  7.5) Serial.println("  Profile: 9V");
  else if (vOut >  4.0) Serial.println("  Profile: 5V");
  else                  Serial.println("  Profile: none / disconnected");

  delay(1000);
}

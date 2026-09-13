// Calibrates the WCS1700 zero offset, reads averaged analog samples from A0, converts the sensor voltage to current in amps, and prints values over Serial.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-wcs1700-monitor-70a-current
// Parts used: https://shillehtek.com/products/wcs1700-70a-hall-current-sensor-module-overcurrent-detect
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int PIN = A0;
const float VCC = 5.0;
const float SENS = 0.044;   // V/A for WCS1700 (datasheet typical)
float zeroV = 0;

void setup() {
  Serial.begin(9600);
  long sum = 0;
  for (int i = 0; i < 500; i++) sum += analogRead(PIN);
  zeroV = (sum / 500.0) * (VCC / 1023.0);
  Serial.print("Zero V: "); Serial.println(zeroV, 3);
}

void loop() {
  long sum = 0;
  for (int i = 0; i < 50; i++) sum += analogRead(PIN);
  float v = (sum / 50.0) * (VCC / 1023.0);
  float amps = (v - zeroV) / SENS;
  Serial.print("V="); Serial.print(v, 3);
  Serial.print("  I="); Serial.print(amps, 2);
  Serial.println(" A");
  delay(250);
}

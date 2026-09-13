// Simple Arduino sketch that reads the ACS712 analog output, applies zero-offset calibration and sensitivity to compute current, and prints the result over Serial every 500 ms.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-acs712-measure-ac-dc-current-30a
// Parts used: https://shillehtek.com/products/acs712-current-sensor-5a-arduino-esp32
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int SENSOR = A0;
const float SENSITIVITY_5A = 0.185;   // V per Amp for ACS712-05B
// 20A variant = 0.100, 30A variant = 0.066

float zeroOffset = 2.5;   // will calibrate later

void setup() { Serial.begin(9600); }
void loop() {
  int raw = analogRead(SENSOR);
  float voltage = raw * 5.0 / 1023.0;
  float current = (voltage - zeroOffset) / SENSITIVITY_5A;
  Serial.print(current, 3);
  Serial.println(" A");
  delay(500);
}

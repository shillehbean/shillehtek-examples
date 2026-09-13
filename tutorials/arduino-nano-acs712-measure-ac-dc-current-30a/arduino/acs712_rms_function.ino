// Function to sample the ACS712 rapidly over a time window and return the RMS current (useful for AC measurements).
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-acs712-measure-ac-dc-current-30a
// Parts used: https://shillehtek.com/products/acs712-current-sensor-5a-arduino-esp32
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
// More examples: https://github.com/shillehbean/shillehtek-examples
//

float readAcRms(int pin, unsigned long window_ms = 200) {
  unsigned long start = millis();
  double sumsq = 0;
  int n = 0;
  while (millis() - start < window_ms) {
    int raw = analogRead(pin);
    float v = raw * 5.0 / 1023.0 - zeroOffset;
    float i = v / SENSITIVITY_5A;
    sumsq += i * i;
    n++;
  }
  return sqrt(sumsq / n);
}

// Performs a smooth PWM ramp up and down (breathing effect) on a PWM-capable Arduino pin to dim a 12V LED strip via the IRF520 driver.
//
// Buy this module: https://shillehtek.com/products/irf520-mosfet-driver-module-arduino-raspberry-pi-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/irf520-mosfet-driver-module-arduino-raspberry-pi-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int SIG = 9;

void setup() {
  pinMode(SIG, OUTPUT);
}

void loop() {
  // breathe a 12 V LED strip
  for (int d = 0; d <= 255; d += 3) {
    analogWrite(SIG, d);
    delay(12);
  }
  for (int d = 255; d >= 0; d -= 3) {
    analogWrite(SIG, d);
    delay(12);
  }
}

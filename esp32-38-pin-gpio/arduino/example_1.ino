// Toggle a chosen GPIO (TEST_PIN) on and off every 500 ms to blink an LED or verify wiring on the breakout.
//
// Buy this module: https://shillehtek.com/products/esp32-38-pin-gpio-expansion-breakout
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-38-pin-gpio-expansion-breakout-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Blink any breakout point to confirm your wiring & labels.
// Change TEST_PIN, upload, and put an LED (with resistor) or
// a multimeter on that terminal.
const int TEST_PIN = 27;

void setup() {
  pinMode(TEST_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.printf("Toggling GPIO %d\n", TEST_PIN);
}

void loop() {
  digitalWrite(TEST_PIN, HIGH);
  delay(500);
  digitalWrite(TEST_PIN, LOW);
  delay(500);
}

// Measure the pulse-width output from the tester on D2 and print the servo pulse width in microseconds to the serial console.
//
// Buy this module: https://shillehtek.com/products/servo-tester-rc-ccpm-checker
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/servo-tester-rc-ccpm-checker-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Tester OUT column S pin -> D2, tester GND -> Arduino GND
const int PULSE_PIN = 2;

void setup() {
  Serial.begin(9600);
  pinMode(PULSE_PIN, INPUT);
}

void loop() {
  // Width of the HIGH pulse in microseconds (typ. 800-2200)
  unsigned long us = pulseIn(PULSE_PIN, HIGH, 100000);
  if (us > 0) {
    Serial.print("Pulse: ");
    Serial.print(us);
    Serial.println(" us");
  } else {
    Serial.println("No signal");
  }
  delay(200);
}

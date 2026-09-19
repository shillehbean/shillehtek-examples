// Read a potentiometer on A0 and output corresponding 800–2200 µs servo pulses on D9 to manually position a servo.
//
// Buy this module: https://shillehtek.com/products/servo-tester-rc-ccpm-checker
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/servo-tester-rc-ccpm-checker-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Servo.h>

// Servo signal -> D9, potentiometer wiper -> A0
Servo servo;

void setup() {
  servo.attach(9, 800, 2200);   // match the tester's range
}

void loop() {
  int raw = analogRead(A0);               // 0-1023
  int us = map(raw, 0, 1023, 800, 2200);  // knob -> pulse width
  servo.writeMicroseconds(us);
  delay(15);
}

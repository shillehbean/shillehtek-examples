// Use the ESP32Servo library to sweep a servo attached to GPIO 18 across the 800–2200 µs range back and forth.
//
// Buy this module: https://shillehtek.com/products/servo-tester-rc-ccpm-checker
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/servo-tester-rc-ccpm-checker-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Library Manager: install "ESP32Servo"
#include <ESP32Servo.h>

Servo servo;

void setup() {
  servo.setPeriodHertz(50);
  servo.attach(18, 800, 2200);   // signal on GPIO 18
}

void loop() {
  for (int us = 800; us <= 2200; us += 10) {
    servo.writeMicroseconds(us);
    delay(10);
  }
  for (int us = 2200; us >= 800; us -= 10) {
    servo.writeMicroseconds(us);
    delay(10);
  }
}

// Arduino sketch that sweeps an SG92R servo smoothly from 0° to 180° and back using the Servo library.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-sg92r-servo-smooth-sweep
// Parts used: https://shillehtek.com/products/sg92r-micro-servo-motor-9g-carbon-fiber-gears-2-5kg-for-rc-plane
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Servo.h>

Servo s;

void setup() {
  s.attach(9);
}

void loop() {
  for (int angle = 0; angle <= 180; angle++) {
    s.write(angle);
    delay(15);
  }
  for (int angle = 180; angle >= 0; angle--) {
    s.write(angle);
    delay(15);
  }
}

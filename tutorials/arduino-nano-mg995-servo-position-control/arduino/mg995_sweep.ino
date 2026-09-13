// Attach an MG995 servo on pin D9 with an extended pulse range and cycle it through 0°, 90°, and 180° positions.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-mg995-servo-position-control
// Parts used: https://shillehtek.com/products/mg995-metal-gear-servo-motor-12kg-high-torque-180-degree-diy
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Servo.h>

Servo arm;

void setup() {
  arm.attach(9, 500, 2500);   // wider pulse range for full MG995 sweep
}

void loop() {
  arm.write(0);    delay(800);
  arm.write(90);   delay(800);
  arm.write(180);  delay(800);
  arm.write(90);   delay(800);
}

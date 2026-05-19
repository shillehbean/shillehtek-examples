// Moves the servo to 0°, 90°, and 180° (then back) while using a tightened pulse-width range (500–2500 µs) for fuller travel on pin 9.
//
// Buy this module: https://shillehtek.com/products/mg995-metal-gear-servo-motor-12kg-high-torque-180-degree-diy
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mg995-metal-gear-servo-motor-12kg-high-torque-180-degree-diy-manual
// More examples: https://github.com/shillehtek/examples
//

#include <Servo.h>

Servo s;

void setup() {
  s.attach(9, 500, 2500);   // tighter pulse range, full ~180 swing
}

void loop() {
  s.write(0);    delay(800);
  s.write(90);   delay(800);
  s.write(180);  delay(800);
  s.write(90);   delay(800);
}

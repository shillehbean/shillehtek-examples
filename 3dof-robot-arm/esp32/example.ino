// Control three servos on an ESP32 using the ESP32Servo library, centering them and performing per-joint glide motions in degrees.
//
// Buy this module: https://shillehtek.com/products/3dof-robot-arm-kit-mg995-servos
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/3dof-robot-arm-kit-mg995-servos-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Library Manager: install "ESP32Servo"
#include <ESP32Servo.h>

Servo joints[3];
const int PINS[3] = {25, 26, 27};

void setup() {
  for (int i = 0; i < 3; i++) {
    joints[i].setPeriodHertz(50);
    joints[i].attach(PINS[i], 500, 2500);
    joints[i].write(90);            // center everything
  }
  delay(1000);
}

void glide(int idx, int from, int to) {
  int dir = (to > from) ? 1 : -1;
  for (int a = from; a != to; a += dir) {
    joints[idx].write(a);
    delay(8);
  }
}

void loop() {
  glide(0, 90, 40);    // base left
  glide(1, 90, 120);   // shoulder down
  glide(2, 90, 60);    // elbow in
  delay(500);
  glide(2, 60, 90);
  glide(1, 120, 90);
  glide(0, 40, 90);
  delay(1200);
}

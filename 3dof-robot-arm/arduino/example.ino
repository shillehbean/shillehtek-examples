// Drive three MG995 servos from an Arduino using the Servo library and smooth (glide) joint motions by writing microsecond pulse widths.
//
// Buy this module: https://shillehtek.com/products/3dof-robot-arm-kit-mg995-servos
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/3dof-robot-arm-kit-mg995-servos-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Servo.h>

Servo base, shoulder, elbow;
int cur[3] = {1500, 1500, 1500};   // current pulse widths (us)

void setup() {
  base.attach(9);
  shoulder.attach(10);
  elbow.attach(11);
  writeAll();
  delay(1000);                      // settle at center
}

void writeAll() {
  base.writeMicroseconds(cur[0]);
  shoulder.writeMicroseconds(cur[1]);
  elbow.writeMicroseconds(cur[2]);
}

// glide all joints to a target pose together
void moveTo(int b, int s, int e, int stepDelay) {
  int tgt[3] = {b, s, e};
  bool moving = true;
  while (moving) {
    moving = false;
    for (int i = 0; i < 3; i++) {
      if (cur[i] < tgt[i]) { cur[i] += 5; moving = true; }
      if (cur[i] > tgt[i]) { cur[i] -= 5; moving = true; }
    }
    writeAll();
    delay(stepDelay);
  }
}

void loop() {
  moveTo(1200, 1700, 1300, 6);   // reach forward-left
  delay(600);
  moveTo(1800, 1400, 1700, 6);   // swing right, tuck
  delay(600);
  moveTo(1500, 1500, 1500, 6);   // home
  delay(1000);
}

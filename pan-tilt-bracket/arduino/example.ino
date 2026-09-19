// Uses the Arduino Servo library to sweep pan and tilt servos in a raster 'radar' pattern while respecting soft angle limits.
//
// Buy this module: https://shillehtek.com/products/pan-tilt-servo-bracket-kit-sg90-mg90s
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pan-tilt-servo-bracket-kit-sg90-mg90s-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Servo.h>

Servo pan, tilt;
const int PAN_MIN = 20, PAN_MAX = 160;   // soft limits
const int TILT_MIN = 60, TILT_MAX = 120;

void setup() {
  pan.attach(9);
  tilt.attach(10);
  pan.write(90);
  tilt.write(90);
  delay(800);
}

void loop() {
  // sweep pan at each tilt step - a "radar" raster
  for (int t = TILT_MIN; t <= TILT_MAX; t += 20) {
    tilt.write(t);
    for (int p = PAN_MIN; p <= PAN_MAX; p += 2) {
      pan.write(p);
      delay(15);
    }
    for (int p = PAN_MAX; p >= PAN_MIN; p -= 2) {
      pan.write(p);
      delay(15);
    }
  }
}

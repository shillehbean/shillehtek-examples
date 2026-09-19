// Uses the ESP32Servo library to smoothly glide two servos together to a series of target positions (aiming sequence) on ESP32 pins.
//
// Buy this module: https://shillehtek.com/products/pan-tilt-servo-bracket-kit-sg90-mg90s
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pan-tilt-servo-bracket-kit-sg90-mg90s-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Library Manager: install "ESP32Servo"
#include <ESP32Servo.h>

Servo pan, tilt;

void aim(int p, int t) {           // glide both axes together
  static int cp = 90, ct = 90;
  while (cp != p || ct != t) {
    if (cp < p) cp++; else if (cp > p) cp--;
    if (ct < t) ct++; else if (ct > t) ct--;
    pan.write(cp);
    tilt.write(ct);
    delay(10);
  }
}

void setup() {
  pan.setPeriodHertz(50);  pan.attach(26, 500, 2500);
  tilt.setPeriodHertz(50); tilt.attach(27, 500, 2500);
  pan.write(90); tilt.write(90);
  delay(800);
}

void loop() {
  aim(40, 80);    delay(700);   // look left-down
  aim(140, 80);   delay(700);   // look right-down
  aim(90, 115);   delay(700);   // look up-center
  aim(90, 90);    delay(1200);  // home
}

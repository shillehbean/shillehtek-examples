// Reads an analog joystick (X, Y, and switch) and drives two servos for pan and tilt with a dead zone, proportional speed, and click-to-recenter.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-analog-joystick-pan-tilt-servo-control
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/pan-tilt-servo-bracket-kit-sg90-mg90s
//             https://shillehtek.com/products/mg995-metal-gear-servo-motor-12kg-high-torque-180-degree-diy
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Servo.h>

Servo pan, tilt;
const int JOY_X = A0, JOY_Y = A1, JOY_SW = 2;
const int CENTER = 512, DEAD = 60;      // ignore stick wobble near the middle
const int MAX_STEP = 3;                 // degrees per update at full deflection
int panPos = 90, tiltPos = 90;

int stepFor(int raw) {                  // returns -MAX_STEP..+MAX_STEP, 0 in the dead zone
  int d = raw - CENTER;
  if (abs(d) < DEAD) return 0;
  return map(d, -512, 511, -MAX_STEP, MAX_STEP);
}

void setup() {
  pan.attach(9); tilt.attach(10);
  pinMode(JOY_SW, INPUT_PULLUP);
  pan.write(panPos); tilt.write(tiltPos);
}

void loop() {
  panPos  += stepFor(analogRead(JOY_X));           // push further = move faster
  tiltPos += stepFor(analogRead(JOY_Y));
  panPos  = constrain(panPos, 0, 180);
  tiltPos = constrain(tiltPos, 20, 160);           // keep the bracket off its mechanical stops

  if (digitalRead(JOY_SW) == LOW) { panPos = 90; tiltPos = 90; }   // click = recenter

  pan.write(panPos);
  tilt.write(tiltPos);
  delay(15);                                       // ~66 updates per second
}

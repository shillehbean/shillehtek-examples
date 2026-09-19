// Reads four LDRs, computes left/right and top/bottom averages with a dead band, and drives two servos to track the brightest light by moving one degree per loop while printing positions to Serial.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-ldr-solar-tracker-dual-axis
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/pan-tilt-servo-bracket-kit-sg90-mg90s
//             https://shillehtek.com/products/mg995-metal-gear-servo-motor-12kg-high-torque-180-degree-diy
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Servo.h>

Servo pan, tilt;
const int LDR_TL = A0, LDR_TR = A1, LDR_BL = A2, LDR_BR = A3;
const int TOL = 40;                  // dead band: ignore differences smaller than this
int panPos = 90, tiltPos = 90;

void setup() {
  pan.attach(9); tilt.attach(10);
  pan.write(panPos); tilt.write(tiltPos);
  Serial.begin(9600);
}

void loop() {
  int tl = analogRead(LDR_TL), tr = analogRead(LDR_TR);
  int bl = analogRead(LDR_BL), br = analogRead(LDR_BR);

  int top  = (tl + tr) / 2,  bottom = (bl + br) / 2;   // average each edge
  int left = (tl + bl) / 2,  right  = (tr + br) / 2;

  // move one degree toward the brighter side, but only outside the dead band
  if (abs(top - bottom) > TOL) tiltPos += (top  > bottom) ? 1 : -1;
  if (abs(left - right) > TOL) panPos  += (left > right)  ? -1 : 1;

  tiltPos = constrain(tiltPos, 20, 160);
  panPos  = constrain(panPos, 10, 170);
  tilt.write(tiltPos);
  pan.write(panPos);

  Serial.print("pan "); Serial.print(panPos);
  Serial.print("  tilt "); Serial.println(tiltPos);
  delay(30);                           // ~33 steps/second: smooth, not jittery
}

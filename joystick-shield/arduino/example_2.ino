// Maps the right joystick's X analog value (0–1023) to a 0–180° servo angle and drives a servo connected to digital pin 9.
//
// Buy this module: https://shillehtek.com/products/joystick-shield-v1-a-gamepad-controller-module-for-arduino-r3
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/joystick-shield-v1-a-gamepad-controller-module-for-arduino-r3-manual
// More examples: https://github.com/shillehtek/examples
//

// Map right joystick X (0-1023) to servo angle (0-180)
// Plug servo into the D9 servo header

#include <Servo.h>
Servo srv;

const int RX = A2;
const int SERVO_PIN = 9;

void setup() {
  srv.attach(SERVO_PIN);
}

void loop() {
  int x = analogRead(RX);
  int angle = map(x, 0, 1023, 0, 180);
  srv.write(angle);
  delay(15);
}

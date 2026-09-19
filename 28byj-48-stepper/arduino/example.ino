// Uses the built-in Arduino Stepper library to rotate the 28BYJ-48 one full revolution clockwise and counter-clockwise at a set RPM, demonstrating the correct pin ordering for the ULN2003 board.
//
// Buy this module: https://shillehtek.com/products/stepper-motor-28byj-48-5v-arduino-raspberry-pi
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/stepper-motor-28byj-48-5v-arduino-raspberry-pi-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// 28BYJ-48 + ULN2003 - Arduino Example (built-in Stepper library)
// IN1->8, IN2->9, IN3->10, IN4->11

#include <Stepper.h>

const int STEPS_PER_REV = 2048;      // full-step mode

// Note the pin order: IN1, IN3, IN2, IN4 for correct sequencing
Stepper stepper(STEPS_PER_REV, 8, 10, 9, 11);

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(12);              // RPM (10-15 is reliable)
}

void loop() {
  Serial.println("One revolution clockwise...");
  stepper.step(STEPS_PER_REV);
  delay(1000);

  Serial.println("One revolution counter-clockwise...");
  stepper.step(-STEPS_PER_REV);
  delay(1000);
}

// Drives a 28BYJ-48 (via ULN2003) from an Arduino to perform one full revolution clockwise and counterclockwise using the Stepper library (notes the swapped pin order).
//
// Buy this module: https://shillehtek.com/products/shillehtek-5v-4-phase-stepper-motor-with-uln2003-driver
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-5v-4-phase-stepper-motor-with-uln2003-driver-manual
// More examples: https://github.com/shillehtek/examples
//

// 28BYJ-48 + ULN2003 - Arduino full revolution example
// IN1->D8, IN2->D9, IN3->D10, IN4->D11
// NOTE: Stepper.h pin order is (IN1, IN3, IN2, IN4) — not 1,2,3,4!

#include 

// Steps per revolution for the 28BYJ-48 (full step with 64:1 gearbox)
const int STEPS_PER_REV = 2048;

// Stepper(steps, pin1, pin3, pin2, pin4) — note the swapped order
Stepper motor(STEPS_PER_REV, 8, 10, 9, 11);

void setup() {
  Serial.begin(9600);
  motor.setSpeed(10);  // RPM (max ~15 RPM for 28BYJ-48)
}

void loop() {
  Serial.println("One revolution clockwise");
  motor.step(STEPS_PER_REV);
  delay(1000);

  Serial.println("One revolution counter-clockwise");
  motor.step(-STEPS_PER_REV);
  delay(1000);
}

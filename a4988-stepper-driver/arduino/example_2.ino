// Uses the AccelStepper library in DRIVER mode to move the stepper one revolution with controlled speed and acceleration, reversing direction when the target position is reached.
//
// Buy this module: https://shillehtek.com/products/shillehtek-original-a4988-stepper-motor-driver-with-heatsink
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-original-a4988-stepper-motor-driver-with-heatsink-manual
// More examples: https://github.com/shillehtek/examples
//

// A4988 - Smooth motion with AccelStepper library
// Library: AccelStepper by Mike McCauley (Library Manager)

#include <AccelStepper.h>

#define STEP_PIN 3
#define DIR_PIN  4

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
  stepper.setMaxSpeed(1000);     // steps/sec
  stepper.setAcceleration(500);  // steps/sec^2
  stepper.moveTo(3200);          // one revolution at 1/16 microstepping
}

void loop() {
  if (stepper.distanceToGo() == 0) {
    stepper.moveTo(-stepper.currentPosition());   // reverse
  }
  stepper.run();
}

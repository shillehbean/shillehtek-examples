// Arduino sketch using the Stepper library to make a 28BYJ-48 stepper motor perform one full rotation clockwise and then one full rotation counterclockwise.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uln2003-stepper-one-revolution
// Parts used: https://shillehtek.com/products/shillehtek-5v-4-phase-stepper-motor-with-uln2003-driver
//             https://shillehtek.com/products/stepper-motor-28byj-48-5v-arduino-raspberry-pi
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Stepper.h>

// Driver input pins
#define OUTPUT1 7 // IN1 (Blue coil wire)
#define OUTPUT2 6 // IN2 (Pink coil wire)
#define OUTPUT3 5 // IN3 (Yellow coil wire)
#define OUTPUT4 4 // IN4 (Orange coil wire)

// 28BYJ-48: 2048 steps per output revolution in full-step mode
const int stepsPerRotation = 2048;

// Pin sequence OUTPUT1, OUTPUT3, OUTPUT2, OUTPUT4 pairs the coils correctly
Stepper myStepper(stepsPerRotation, OUTPUT1, OUTPUT3, OUTPUT2, OUTPUT4);

void setup() {
  myStepper.setSpeed(15); // RPM
}

void loop() {
  // One full rotation clockwise
  myStepper.step(stepsPerRotation);
  delay(1000);
  // One full rotation the other way
  myStepper.step(-stepsPerRotation);
  delay(1000);
}

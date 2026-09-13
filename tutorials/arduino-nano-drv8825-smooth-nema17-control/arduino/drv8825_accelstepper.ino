// Arduino sketch using the AccelStepper library to run the stepper with controlled max speed and acceleration to a target position (smoother motion).
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-drv8825-smooth-nema17-control
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <AccelStepper.h>

AccelStepper motor(1, 3, 2);   // driver mode, STEP, DIR

void setup() {
  motor.setMaxSpeed(2000);      // steps/sec
  motor.setAcceleration(500);   // steps/sec^2
  motor.moveTo(6400);           // 1 rev at 1/32
}

void loop() {
  motor.run();                  // must call often
}

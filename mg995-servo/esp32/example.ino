// Uses the ESP32Servo library to drive the MG995 on GPIO18 at 50 Hz with 500–2500 µs min/max pulses and steps the angle in 30° increments.
//
// Buy this module: https://shillehtek.com/products/mg995-metal-gear-servo-motor-12kg-high-torque-180-degree-diy
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mg995-metal-gear-servo-motor-12kg-high-torque-180-degree-diy-manual
// More examples: https://github.com/shillehtek/examples
//

// Install "ESP32Servo" via Library Manager

#include <ESP32Servo.h>

Servo myServo;

void setup() {
  myServo.setPeriodHertz(50);             // standard hobby servo
  myServo.attach(18, 500, 2500);          // GPIO 18, min/max us
}

void loop() {
  for (int a = 0; a <= 180; a += 30) {
    myServo.write(a);
    delay(400);
  }
}

// Continuously sweeps the MG995 from 0° to 180° and back using Arduino's Servo library on digital pin 9.
//
// Buy this module: https://shillehtek.com/products/mg995-metal-gear-servo-motor-12kg-high-torque-180-degree-diy
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mg995-metal-gear-servo-motor-12kg-high-torque-180-degree-diy-manual
// More examples: https://github.com/shillehtek/examples
//

// MG995 sweep using built-in Servo library
// Signal -> D9, V+ -> external 5-6V, GND tied together

#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(9);   // signal pin
}

void loop() {
  for (int pos = 0; pos <= 180; pos++) {
    myServo.write(pos);
    delay(15);
  }
  for (int pos = 180; pos >= 0; pos--) {
    myServo.write(pos);
    delay(15);
  }
}

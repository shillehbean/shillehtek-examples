// Sweep the SG92R back and forth between 0° and 180° using the Arduino Servo library on pin 9.
//
// Buy this module: https://shillehtek.com/products/sg92r-micro-servo-motor-9g-carbon-fiber-gears-2-5kg-for-rc-plane
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/sg92r-micro-servo-motor-9g-carbon-fiber-gears-2-5kg-for-rc-plane-manual
// More examples: https://github.com/shillehtek/examples
//

// SG92R Servo - Sweep from 0 to 180 degrees and back
// Library: Servo (built-in to Arduino IDE)

#include <Servo.h>

Servo myServo;
const int servoPin = 9;

void setup() {
  myServo.attach(servoPin);
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

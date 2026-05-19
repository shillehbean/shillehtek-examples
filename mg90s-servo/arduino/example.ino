// Demonstrates sweeping the MG90S across 0–180° using the Arduino Servo library on digital pin 9 with tuned pulse widths.
//
// Buy this module: https://shillehtek.com/products/mg90s-metal-gear-micro-servo-motor-180-degree-9g-for-rc-plane
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mg90s-metal-gear-micro-servo-motor-180-degree-9g-for-rc-plane-manual
// More examples: https://github.com/shillehtek/examples
//

// MG90S Servo Sweep - Arduino Example
// Signal pin: Digital 9
// Power the servo from an external 5V supply with a common ground.

#include <Servo.h>

Servo myServo;
const int servoPin = 9;

void setup() {
  Serial.begin(9600);
  // attach(pin, minPulseUs, maxPulseUs) — tune these for your servo
  myServo.attach(servoPin, 500, 2400);
  myServo.write(90);   // center
  delay(500);
}

void loop() {
  // Sweep 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);
    delay(15);
  }

  // Sweep back 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);
    delay(15);
  }
}

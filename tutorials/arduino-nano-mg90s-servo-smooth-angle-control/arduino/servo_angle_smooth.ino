// Smoothly sweep a servo between MIN_ANGLE and MAX_ANGLE by incrementing/decrementing the target angle and writing positions with Servo.write().
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-mg90s-servo-smooth-angle-control
// Parts used: https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
//             https://shillehtek.com/products/mg90s-metal-gear-micro-servo-motor-180-degree-9g-for-rc-plane
//             https://shillehtek.com/products/arduino-nano-v3-0-atmega328p-16mhz-ch340c-type-c
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include "Servo.h"

#define SERVO1_PIN 9

#define MIN_ANGLE 0
#define MAX_ANGLE 180
#define DEFAULT_ANGLE 90

int servoAngle = DEFAULT_ANGLE;

Servo Servo1;

void setup()
{
  Servo1.attach(SERVO1_PIN);
  Servo1.write(DEFAULT_ANGLE);
}

void loop()
{
  graduallyApplyServoAngle(MAX_ANGLE);
  delay(1000);

  graduallyApplyServoAngle(MIN_ANGLE);
  delay(1000);
}

void graduallyApplyServoAngle(int angle)
{
  int limitedAngle = limitServoAngle(angle);

  while (servoAngle != limitedAngle) {
    if (servoAngle > limitedAngle) {
      servoAngle--;
    }

    if (servoAngle < limitedAngle) {
      servoAngle++;
    }

    Servo1.write(servoAngle);
    delay(5);
  }
}

int limitServoAngle(int angle)
{
  return constrain(angle, MIN_ANGLE, MAX_ANGLE);
}

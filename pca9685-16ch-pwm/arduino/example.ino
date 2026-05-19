// Uses the Adafruit PWM Servo Driver library to initialize the PCA9685 at 50Hz and sweep a hobby servo connected to channel 0 between two pulse-length limits.
//
// Buy this module: https://shillehtek.com/products/pca9685-16-channel-12-bit-pwm-servo-motor-driver-i2c-for-arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pca9685-16-channel-12-bit-pwm-servo-motor-driver-i2c-for-arduino-manual
// More examples: https://github.com/shillehtek/examples
//

// PCA9685 - Sweep a servo on channel 0
// Library: Adafruit PWM Servo Driver Library (Library Manager)

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150   // ~0.6 ms pulse  (-90 deg)
#define SERVOMAX  600   // ~2.4 ms pulse  (+90 deg)

void setup() {
  pwm.begin();
  pwm.setPWMFreq(50);   // 50 Hz for hobby servos
}

void loop() {
  for (int p = SERVOMIN; p <= SERVOMAX; p += 5) {
    pwm.setPWM(0, 0, p);
    delay(15);
  }
  for (int p = SERVOMAX; p >= SERVOMIN; p -= 5) {
    pwm.setPWM(0, 0, p);
    delay(15);
  }
}

// Sweeps servos connected to PCA9685 channels 0–7 by varying the PWM pulse length between defined minimum and maximum values at 60 Hz.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-pca9685-control-multiple-servos
// Parts used: https://shillehtek.com/products/pca9685-16-channel-12-bit-pwm-servo-motor-driver-i2c-for-arduino
//             https://shillehtek.com/products/mg90s-metal-gear-micro-servo-motor-180-degree-9g-for-rc-plane
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150
#define SERVOMAX  600

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);
  delay(10);
}

void loop() {
  for (int pulse = SERVOMIN; pulse <= SERVOMAX; pulse++) {
    for (int channel = 0; channel < 8; channel++) {
      pwm.setPWM(channel, 0, pulse);
    }
    delay(10);
  }

  for (int pulse = SERVOMAX; pulse >= SERVOMIN; pulse--) {
    for (int channel = 0; channel < 8; channel++) {
      pwm.setPWM(channel, 0, pulse);
    }
    delay(10);
  }
}

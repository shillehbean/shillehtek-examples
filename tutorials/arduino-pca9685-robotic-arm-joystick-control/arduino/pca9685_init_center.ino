// Initialize the PCA9685 PWM driver, set 50 Hz refresh rate, and center the first six servos.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-pca9685-robotic-arm-joystick-control
// Parts used: https://shillehtek.com/products/pca9685-16-channel-12-bit-pwm-servo-motor-driver-i2c-for-arduino
//             https://shillehtek.com/products/mg90s-metal-gear-micro-servo-motor-180-degree-9g-for-rc-plane
//             https://shillehtek.com/products/ky-023-dual-axis-joystick-module-ps2-analog-sensor-for-arduino
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
const int SERVO_MIN = 150, SERVO_MAX = 600;
void setup() {
  pwm.begin(); pwm.setPWMFreq(50);
  for (int s = 0; s < 6; s++) pwm.setPWM(s, 0, (SERVO_MIN + SERVO_MAX) / 2);
}
void loop() {}

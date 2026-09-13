// Read two analog joystick axes and map them to servo angles for base and shoulder, updating channels 0 and 1 on the PCA9685.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-pca9685-robotic-arm-joystick-control
// Parts used: https://shillehtek.com/products/pca9685-16-channel-12-bit-pwm-servo-motor-driver-i2c-for-arduino
//             https://shillehtek.com/products/mg90s-metal-gear-micro-servo-motor-180-degree-9g-for-rc-plane
//             https://shillehtek.com/products/ky-023-dual-axis-joystick-module-ps2-analog-sensor-for-arduino
// More examples: https://github.com/shillehbean/shillehtek-examples
//

int curBase = 90, curShoulder = 90;
void loop() {
  int xRaw = analogRead(A0) - 512;
  int yRaw = analogRead(A1) - 512;
  if (abs(xRaw) > 50) curBase = constrain(curBase + xRaw/200, 0, 180);
  if (abs(yRaw) > 50) curShoulder = constrain(curShoulder + yRaw/200, 0, 180);
  pwm.setPWM(0, 0, map(curBase, 0, 180, SERVO_MIN, SERVO_MAX));
  pwm.setPWM(1, 0, map(curShoulder, 0, 180, SERVO_MIN, SERVO_MAX));
  delay(20);
}

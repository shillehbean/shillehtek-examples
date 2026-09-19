// Arduino sketch for a two-wheel self-balancing robot: defines motor/MPU pin mappings, PID and complementary-filter tuning constants, and helper functions to write to and read raw sensor data from the MPU-6050 over I2C.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-mpu6050-self-balancing-robot
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer
//             https://shillehtek.com/products/shillehtek-l298n-motor-driver-controller-board
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
const int ENA = 3, IN1 = 4, IN2 = 8, IN3 = 5, IN4 = 7, ENB = 6;
const uint8_t MPU = 0x68;

// ---- tuning (see Step 5) ----
float Kp = 20.0, Ki = 150.0, Kd = 0.6;
float setpoint  = 0.0;          // degrees: the angle at which the robot is truly balanced
const int   MIN_PWM    = 40;    // motors don't turn below this
const float FALL_ANGLE = 35.0;  // give up beyond this

float angle = 0, integral = 0, lastErr = 0, gyroOffset = 0;
unsigned long lastUs;

void mpuWrite(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(MPU); Wire.write(reg); Wire.write(val); Wire.endTransmission();
}
void mpuRead(int16_t& ax, int16_t& az, int16_t& gy) {
  Wire.beginTransmission(MPU); Wire.write(0x3B); Wire.endTransmission(false);
  Wire.requestFrom(MPU, (uint8_t)14);
  ax = Wire.read() << 8 | Wire.read();  Wire.read(); Wire.read();   // ax, (ay skipped)
  az = Wire.read() << 8 | Wire.read();
  Wire.read(); Wire.read();                                        // temperature
  Wire.read(); Wire.read();                                        // gx
  gy = Wire.read() << 8 | Wire.read();                              // gyro around the axle
  Wire.read(); Wire.read();                                        // gz
}

void drive(int pwm) {                       // -215..215, positive = forward
  bool fwd = pwm > 0; pwm = abs(pwm);
  if (pwm > 0) pwm = constrain(pwm + MIN_PWM, 0, 255);   // jump over the dead band
  digitalWrite(IN1, fwd);  digitalWrite(IN2, !fwd);
  digitalWrite(IN3, fwd);  digitalWrite(IN4, !fwd);
  analogWrite(ENA, pwm);   analogWrite(ENB, pwm);
}

void setup() {
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  Wire.begin(); Wire.setClock(400000);
  mpuWrite(0x6B, 0x00);        // wake up
  mpuWrite(0x1B, 0x00);        // gyro  +/-250 deg/s  -> 131 LSB per deg/s
  mpuWrite(0x1C, 0x00);        // accel +/-2 g
  mpuWrite(0x1A, 0x03);        // 44 Hz low-pass filter
  delay(500);
  long sum = 0;                // gyro offset: keep the robot still for one second after power-up
  for (int i = 0; i < 500; i++) { int16_t ax, az, gy; mpuRead(ax, az, gy); sum += gy; delay(2); }
  gyroOffset = sum / 500.0;
  lastUs = micros();
}

void loop() {
  int16_t ax, az, gy; mpuRead(ax, az, gy);
  unsigned long now = micros(); float dt = (now - lastUs) / 1e6; lastUs = now;

  float accAngle = atan2((float)ax, (float)az) * 57.296;            // lean angle from gravity
  float gyroRate = (gy - gyroOffset) / 131.0;                        // deg/s
  angle = 0.98 * (angle + gyroRate * dt) + 0.02 * accAngle;          // complementary filter

  if (abs(angle) > FALL_ANGLE) { drive(0); integral = 0; lastErr = 0; return; }   // fallen over

  float err = angle - setpoint;                                      // positive = leaning forward
  integral = constrain(integral + err * dt, -30, 30);
  float deriv = (err - lastErr) / dt; lastErr = err;
  float out = Kp * err + Ki * integral + Kd * deriv;
  drive(constrain(out, -215, 215));                                  // drive INTO the lean

  while (micros() - lastUs < 5000) {}                                // fixed 200 Hz loop
}

// Drive the 1027 coin vibration motor from an Arduino PWM pin (D9) via a transistor to produce single/double taps and a soft ramping vibration pattern.
//
// Buy this module: https://shillehtek.com/products/coin-vibration-motor-1027-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/coin-vibration-motor-1027-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// 1027 coin motor through a transistor on D9 (PWM).
// Motor powered from 3.3V; duty values here assume that rail.

const int MOTOR_PIN = 9;

void buzz(int strength, int ms) {   // strength 0-255
  analogWrite(MOTOR_PIN, strength);
  delay(ms);
  analogWrite(MOTOR_PIN, 0);
}

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
}

void loop() {
  // Single tap
  buzz(255, 80);
  delay(1000);

  // Double tap
  buzz(255, 60); delay(100); buzz(255, 60);
  delay(1000);

  // Soft ramp (phone-style)
  for (int p = 60; p <= 255; p += 15) {
    analogWrite(MOTOR_PIN, p);
    delay(30);
  }
  analogWrite(MOTOR_PIN, 0);
  delay(2000);
}

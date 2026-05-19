// Basic Step/Dir test that enables the driver and rotates a stepper one full revolution forward and then back using STEP and DIR pins.
//
// Buy this module: https://shillehtek.com/products/mks-tmc2209-motor-driver-with-heatsink
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mks-tmc2209-motor-driver-with-heatsink-manual
// More examples: https://github.com/shillehtek/examples
//

// TMC2209 Step/Dir basic test - rotates back and forth

const int EN_PIN = 8;
const int DIR_PIN = 4;
const int STEP_PIN = 5;

const int STEPS_PER_REV = 200 * 16;  // 200 fullsteps * 16 microsteps

void setup() {
  pinMode(EN_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);  // enabled (active LOW)
}

void rotate(bool dir, int steps, int delayUs) {
  digitalWrite(DIR_PIN, dir);
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(2);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(delayUs);
  }
}

void loop() {
  rotate(true, STEPS_PER_REV, 200);   // 1 rev forward
  delay(500);
  rotate(false, STEPS_PER_REV, 200);  // 1 rev back
  delay(500);
}

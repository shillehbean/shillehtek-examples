// Simple Arduino sketch to drive a NEMA 17 stepper via an A4988 using STEP and DIR pins; it rotates one full revolution forward then one full revolution in reverse.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-a4988-nema17-stepper-control
// Parts used: https://shillehtek.com/products/shillehtek-original-a4988-stepper-motor-driver-with-heatsink
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int STEP = 3;
const int DIR  = 4;
const int STEPS_PER_REV = 200;   // 1.8° motor

void setup() {
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
}

void rotate(int steps, bool forward, int delay_us) {
  digitalWrite(DIR, forward ? HIGH : LOW);
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(delay_us);
    digitalWrite(STEP, LOW);
    delayMicroseconds(delay_us);
  }
}

void loop() {
  rotate(STEPS_PER_REV, true,  800);  // one rev forward
  delay(500);
  rotate(STEPS_PER_REV, false, 800);  // one rev reverse
  delay(500);
}

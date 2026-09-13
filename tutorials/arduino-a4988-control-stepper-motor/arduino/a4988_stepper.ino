// Toggles the A4988 STEP pin to move the stepper motor a fixed number of steps, and switches the DIR pin to reverse direction; uses microsecond delays to control speed.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-a4988-control-stepper-motor
// Parts used: https://shillehtek.com/products/shillehtek-original-a4988-stepper-motor-driver-with-heatsink
//             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
//             https://shillehtek.com/products/shillehtek-400-point-breadboard
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// ShillehTek A4988 Stepper Driver Demo
// Arduino Uno: STEP=D3, DIR=D4

const int PIN_STEP = 3;
const int PIN_DIR = 4;

// Lower delay = faster speed. Start slow, then decrease.
int stepDelayMicros = 800;

void stepMotor(int steps) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(PIN_STEP, HIGH);
    delayMicroseconds(2);
    digitalWrite(PIN_STEP, LOW);
    delayMicroseconds(stepDelayMicros);
  }
}

void setup() {
  pinMode(PIN_STEP, OUTPUT);
  pinMode(PIN_DIR, OUTPUT);

  digitalWrite(PIN_DIR, HIGH);
}

void loop() {
  // Forward
  digitalWrite(PIN_DIR, HIGH);
  stepMotor(2000);
  delay(500);

  // Reverse
  digitalWrite(PIN_DIR, LOW);
  stepMotor(2000);
  delay(500);
}

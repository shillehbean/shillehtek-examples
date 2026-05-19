// Basic Arduino example that enables the A4988 and toggles STEP and DIR pins to run the motor one full revolution forward and then reverse using a fixed microstep delay.
//
// Buy this module: https://shillehtek.com/products/shillehtek-original-a4988-stepper-motor-driver-with-heatsink
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-original-a4988-stepper-motor-driver-with-heatsink-manual
// More examples: https://github.com/shillehtek/examples
//

// A4988 Stepper Driver - Arduino Example
// STEP = D3, DIR = D4, EN = D5
// Set VREF to your motor's rated current BEFORE first run.

#define STEP_PIN  3
#define DIR_PIN   4
#define EN_PIN    5

const int stepsPerRev = 200;       // NEMA 17 = 200 full steps/rev
const int microsteps  = 16;        // matching MS1/MS2/MS3 = HIGH/HIGH/HIGH
const int totalSteps  = stepsPerRev * microsteps;

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);   // enable driver
}

void loop() {
  digitalWrite(DIR_PIN, HIGH); // forward
  for (int i = 0; i < totalSteps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(500);    // tune for desired RPM
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(500);
  }
  delay(500);

  digitalWrite(DIR_PIN, LOW);  // reverse
  for (int i = 0; i < totalSteps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(500);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(500);
  }
  delay(500);
}

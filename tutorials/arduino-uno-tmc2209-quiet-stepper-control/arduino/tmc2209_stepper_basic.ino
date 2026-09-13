// Basic Arduino UNO sketch that enables a TMC2209 driver and pulses the STEP pin to move a stepper motor forward and backward with configurable step count and pulse timing.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-tmc2209-quiet-stepper-control
// Parts used: https://shillehtek.com/products/mks-tmc2209-motor-driver-with-heatsink
//             https://shillehtek.com/products/shillehtek-5v-4-phase-stepper-motor-with-uln2003-driver
//             https://shillehtek.com/products/shillehtek-lm2596-dc-dc-adjustable-step-down-power-supply-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Pin Definitions
#define EN_PIN   8   // LOW: driver enabled, HIGH: driver disabled
#define STEP_PIN 9   // One step on each rising edge
#define DIR_PIN  10  // Selects rotation direction

int noOfSteps         = 500;   // Steps per direction
int microSecondsDelay = 1000;  // Delay between STEP edges

void setup() {
  pinMode(EN_PIN,   OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN,  OUTPUT);

  digitalWrite(EN_PIN,  LOW);   // Enable the driver
  digitalWrite(DIR_PIN, LOW);   // Initial direction
}

void loop() {
  // Forward
  digitalWrite(DIR_PIN, LOW);
  moveSteps(noOfSteps);

  // Reverse
  digitalWrite(DIR_PIN, HIGH);
  moveSteps(noOfSteps);

  delay(500);                   // Pause between sweeps
}

void moveSteps(int steps) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(microSecondsDelay);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(microSecondsDelay);
  }
}

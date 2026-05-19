// Initializes and configures a TMC2209 via SoftwareSerial using the TMCStepper library (sets current, microsteps, and StealthChop) then steps the motor.
//
// Buy this module: https://shillehtek.com/products/mks-tmc2209-motor-driver-with-heatsink
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mks-tmc2209-motor-driver-with-heatsink-manual
// More examples: https://github.com/shillehtek/examples
//

// TMC2209 - UART configuration via TMCStepper library
// Library: TMCStepper by teemuatlut (Library Manager)

#include <TMCStepper.h>
#include <SoftwareSerial.h>

#define EN_PIN    8
#define DIR_PIN   4
#define STEP_PIN  5
#define R_SENSE   0.11f       // sense resistor on most boards
#define DRIVER_ADDRESS 0b00   // MS1=LOW, MS2=LOW

SoftwareSerial uart(2, 3);  // RX, TX
TMC2209Stepper driver(&uart, R_SENSE, DRIVER_ADDRESS);

void setup() {
  pinMode(EN_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);

  uart.begin(115200);
  driver.begin();
  driver.toff(5);
  driver.rms_current(800);     // 800 mA RMS
  driver.microsteps(16);
  driver.en_spreadCycle(false); // false = StealthChop (quiet)
}

void loop() {
  digitalWrite(DIR_PIN, HIGH);
  for (int i = 0; i < 3200; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(2);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(200);
  }
  delay(1000);
}

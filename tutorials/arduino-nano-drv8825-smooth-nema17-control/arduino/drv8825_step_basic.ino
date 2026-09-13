// Simple Arduino sketch that enables the DRV8825, sets motor direction, and toggles the STEP pin at a fixed interval to step the motor.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-drv8825-smooth-nema17-control
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int STEP_PIN = 3;
const int DIR_PIN  = 2;
const int EN_PIN   = 8;

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);   // enable driver
  digitalWrite(DIR_PIN, HIGH);
}

void loop() {
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(500);
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(500);
}

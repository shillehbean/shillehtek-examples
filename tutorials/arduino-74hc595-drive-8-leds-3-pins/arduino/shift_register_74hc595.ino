// Drives eight LEDs via a 74HC595 shift register using shiftOut(); implements a binary counter and a Knight Rider chase pattern.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-74hc595-drive-8-leds-3-pins
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
//             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int DATA  = 11;   // SER   (pin 14)
const int LATCH = 12;   // RCLK  (pin 12)
const int CLOCK = 9;    // SRCLK (pin 11)

void writeByte(byte value) {
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, value);
  digitalWrite(LATCH, HIGH);          // all 8 outputs update at once
}

void setup() {
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
}

void loop() {
  // binary counter: watch 0-255 tick across the LEDs
  for (int i = 0; i <= 255; i++) {
    writeByte(i);
    delay(120);
  }

  // knight-rider chase
  for (int i = 0; i < 8; i++)  { writeByte(1 << i); delay(80); }
  for (int i = 7; i >= 0; i--) { writeByte(1 << i); delay(80); }
}

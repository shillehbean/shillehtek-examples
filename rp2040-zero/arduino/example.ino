// Blink an external LED connected to GP2 by toggling the pin HIGH and LOW every 500 ms using the Arduino RP2040 core.
//
// Buy this module: https://shillehtek.com/products/rp2040-zero-microcontroller-board-presoldered-headers
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/rp2040-zero-microcontroller-board-presoldered-headers-manual
// More examples: https://github.com/shillehtek/examples
//

// RP2040-Zero - external LED blink on GP2
// Install: Boards Manager URL https://github.com/earlephilhower/arduino,/pico/releases/download/global/package_rp2040_index.json
// Select Board: Tools -> Board -> "Raspberry Pi Pico/RP2040" -> "Generic RP2040"

const int ledPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
}

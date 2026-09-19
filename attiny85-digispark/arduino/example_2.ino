// Fade an LED on PWM-capable P0 while a button on P2 is held, using the internal pull-up on P2.
//
// Buy this module: https://shillehtek.com/products/attiny85-digispark-usb-arduino-development-board
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/attiny85-digispark-usb-arduino-development-board-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Digispark ATtiny85 - Fade an LED on P0 while a button on P2 is held.
// Wiring: LED + 220R resistor from P0 to GND; button from P2 to GND.
// Uses only P0/P1/P2, so USB uploads stay unaffected.

const int LED_PIN = 0;      // PWM capable
const int BUTTON_PIN = 2;   // input with pull-up

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {   // button held
    for (int b = 0; b <= 255; b += 5) {
      analogWrite(LED_PIN, b);
      delay(10);
    }
    for (int b = 255; b >= 0; b -= 5) {
      analogWrite(LED_PIN, b);
      delay(10);
    }
  } else {
    analogWrite(LED_PIN, 0);
  }
}

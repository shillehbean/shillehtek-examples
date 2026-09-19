// Use the Leonardo's native USB HID to send a typed text macro when a pushbutton on pin 2 is pressed, using the internal pull-up and a simple debounce.
//
// Buy this module: https://shillehtek.com/products/arduino-leonardo-r3-atmega32u4
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-leonardo-r3-atmega32u4-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Leonardo R3 - Type a text macro when a button is pressed.
// Wiring: pushbutton between pin 2 and GND (uses internal pull-up).
// The button guard keeps the keyboard idle until YOU trigger it.

#include <Keyboard.h>

const int BUTTON_PIN = 2;
bool lastState = HIGH;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Keyboard.begin();
}

void loop() {
  bool state = digitalRead(BUTTON_PIN);

  // Falling edge = button just pressed
  if (state == LOW && lastState == HIGH) {
    Keyboard.print("Hello from ShillehTek!");
    delay(50);                 // simple debounce
  }
  lastState = state;
}

// Uses a pushbutton on D2 with INPUT_PULLUP to send the string "Hello from Pro Micro!" and press Enter via the USB Keyboard HID on button press.
//
// Buy this module: https://shillehtek.com/products/manual
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pro-micro-atmega32u4-5v-16mhz-presoldered-type-c-manual
// More examples: https://github.com/shillehtek/examples
//

// Wire a pushbutton between D2 and GND.
// When pressed, the Pro Micro types "Hello from Pro Micro!"
// as if it were a real USB keyboard.

#include <Keyboard.h>

const int BUTTON_PIN = 2;
bool lastState = HIGH;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Keyboard.begin();
}

void loop() {
  bool state = digitalRead(BUTTON_PIN);

  // Trigger on press (HIGH -> LOW transition)
  if (lastState == HIGH && state == LOW) {
    Keyboard.print("Hello from Pro Micro!");
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(50);  // debounce
  }

  lastState = state;
}

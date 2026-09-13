// Reads four input buttons with internal pull-ups and sends corresponding USB HID key presses (F13–F16) when buttons are pressed, with simple debounce.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-pro-micro-push-buttons-usb-hid-macro-pad
// Parts used: https://shillehtek.com/products/pro-micro-atmega32u4-5v-16mhz-presoldered-micro-usb
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Keyboard.h>

const uint8_t PINS[] = {2, 3, 4, 5};
const uint8_t KEYS[] = {
  KEY_F13,        // map to anything in your OS
  KEY_F14,
  KEY_F15,
  KEY_F16
};
bool prev[4] = {HIGH, HIGH, HIGH, HIGH};

void setup() {
  for (uint8_t p : PINS) pinMode(p, INPUT_PULLUP);
  Keyboard.begin();
}

void loop() {
  for (uint8_t i = 0; i < 4; i++) {
    bool now = digitalRead(PINS[i]);
    if (prev[i] == HIGH && now == LOW) {
      Keyboard.press(KEYS[i]);
      delay(15);          // crude debounce
      Keyboard.release(KEYS[i]);
    }
    prev[i] = now;
  }
}

// Configurable Arduino sketch that maps multiple input pins to keyboard HID keys (with optional shift modifier) and sends the mapped keystroke when a pin is pressed.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-leonardo-usb-hid-foot-pedal-keyboard
// Parts used: https://shillehtek.com/products/arduino-leonardo-r3-atmega32u4
//             https://shillehtek.com/products/pro-micro-atmega32u4-5v-16mhz-pre-soldered-usb-c-development-board
//             https://shillehtek.com/products/micro-usb-cable-0-5m-1-64ft
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Keyboard.h>

typedef struct {
  uint8_t pin;
  bool shift;
  uint8_t key;
  uint8_t pinStateLast;
} pinKey_t;

pinKey_t pinKey[] = {
  { 2, false, KEY_PAGE_DOWN, 0 }, // Pin 2 sends page down
  { 3, false, KEY_PAGE_UP,   0 }, // Pin 3 sends page up
  { 6, false, 'a',           0 }, // Pin 6 sends a
  { 7, true,  'a',           0 }  // Pin 7 sends SHIFT + a
};

void setup()
{
  Keyboard.begin();
  for (uint8_t i = 0; i < sizeof(pinKey) / sizeof(pinKey_t); i++) {
    pinMode(pinKey[i].pin, INPUT_PULLUP);
    pinKey[i].pinStateLast = digitalRead(pinKey[i].pin);
  }
}

void loop()
{
  uint8_t pinState;
  for (uint8_t i = 0; i < sizeof(pinKey) / sizeof(pinKey_t); i++) {
    pinState = digitalRead(pinKey[i].pin);
    if (pinKey[i].pinStateLast != pinState) {
      pinKey[i].pinStateLast = pinState;
      if (pinState == 0) {
        if (pinKey[i].shift) {
          Keyboard.press(KEY_LEFT_SHIFT);
        }
        Keyboard.press(pinKey[i].key);
        delay(100);
        Keyboard.releaseAll();
      }
    }
  }
  delay(50);
}

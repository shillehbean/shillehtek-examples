// Partial USB macro-pad sketch with two example key actions; setup() initialization is missing and must be supplied before use.
//
// Full tutorial: https://shillehtek.com/blogs/news/pro-micro-4x4-matrix-keypad-usb-macro-pad
// Parts used: https://shillehtek.com/products/pro-micro-atmega32u4-5v-16mhz-presoldered-micro-usb
//             https://shillehtek.com/products/4x4-membrane-matrix-keypad-16-key-switch-module-for-arduino-diy
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Keypad.h>
#include <Keyboard.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void sendMacroCommand(uint8_t key) {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(key);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    switch (key) {
      case '1': sendMacroCommand(KEY_F1); break;
      case '2': sendMacroCommand(KEY_F2); break;
      // ...one case per button, F1-F12 plus a-d
    }
    Keyboard.releaseAll();
  }
}

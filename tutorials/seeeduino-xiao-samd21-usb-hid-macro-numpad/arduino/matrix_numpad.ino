// Scans a 4x4 matrix keypad and sends the corresponding character over USB HID when a key is pressed.
//
// Full tutorial: https://shillehtek.com/blogs/news/seeeduino-xiao-samd21-usb-hid-macro-numpad
// Parts used: https://shillehtek.com/products/seeeduino-xiao-samd21-arduino-board-presoldered
//             https://shillehtek.com/products/4x4-membrane-matrix-keypad-16-key-switch-module-for-arduino-diy
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Keyboard.h>

const int ROW_PINS[] = {0, 1, 2, 3};
const int COL_PINS[] = {4, 5, 6, 7};

const char KEYMAP[4][4] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'0','.','=','/'},
};

void setup() {
  Keyboard.begin();

  for (int r : ROW_PINS) pinMode(r, OUTPUT);
  for (int c : COL_PINS) pinMode(c, INPUT_PULLUP);
  for (int r : ROW_PINS) digitalWrite(r, HIGH);
}

void loop() {
  for (int r = 0; r < 4; r++) {
    digitalWrite(ROW_PINS[r], LOW);

    for (int c = 0; c < 4; c++) {
      if (digitalRead(COL_PINS[c]) == LOW) {
        Keyboard.press(KEYMAP[r][c]);
        delay(80);
        Keyboard.releaseAll();
      }
    }

    digitalWrite(ROW_PINS[r], HIGH);
  }

  delay(5);
}

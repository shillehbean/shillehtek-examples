// Sends a single USB keyboard string at startup using the Arduino Keyboard HID library.
//
// Full tutorial: https://shillehtek.com/blogs/news/seeeduino-xiao-samd21-usb-hid-macro-numpad
// Parts used: https://shillehtek.com/products/seeeduino-xiao-samd21-arduino-board-presoldered
//             https://shillehtek.com/products/4x4-membrane-matrix-keypad-16-key-switch-module-for-arduino-diy
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Keyboard.h>

void setup() {
  Keyboard.begin();
  delay(2000);
  Keyboard.print("Hello from ShillehTek XIAO!");
}

void loop() {}

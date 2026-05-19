// Reads key presses from a 4x4 matrix keypad using the Keypad library and prints the pressed key to the Serial console.
//
// Buy this module: https://shillehtek.com/products/4x4-membrane-matrix-keypad-16-key-switch-module-for-arduino-diy
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4x4-membrane-matrix-keypad-16-key-switch-module-for-arduino-diy-manual
// More examples: https://github.com/shillehtek/examples
//

// 4x4 Keypad - Arduino Example
// Library: Keypad by Mark Stanley & Alexander Brevig (Library Manager)

#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    Serial.print("Pressed: ");
    Serial.println(key);
  }
}

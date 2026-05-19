// Reads key presses from the 4x3 keypad and prints each pressed key to the serial console.
//
// Buy this module: https://shillehtek.com/products/4x3-membrane-switch-matrix-keypad
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4x3-membrane-switch-matrix-keypad-manual
// More examples: https://github.com/shillehtek/examples
//

#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 3;

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};   // R1..R4
byte colPins[COLS] = {5, 4, 3};       // C1..C3

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

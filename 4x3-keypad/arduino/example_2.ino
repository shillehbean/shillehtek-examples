// Implements a simple 4-digit PIN entry system using the keypad, with '*' to clear, '#' to submit, and masked feedback via serial indicating ACCESS GRANTED or DENIED.
//
// Buy this module: https://shillehtek.com/products/4x3-membrane-switch-matrix-keypad
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4x3-membrane-switch-matrix-keypad-manual
// More examples: https://github.com/shillehtek/examples
//

#include <Keypad.h>

const byte ROWS = 4, COLS = 3;
char keys[ROWS][COLS] = {
  {'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}
};
byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const String correct = "1234";
String entered = "";

void setup() { Serial.begin(9600); Serial.println("Enter 4-digit PIN, end with #"); }

void loop() {
  char k = keypad.getKey();
  if (k) {
    if (k == '#') {
      Serial.println(entered == correct ? "ACCESS GRANTED" : "DENIED");
      entered = "";
    } else if (k == '*') {
      entered = "";
      Serial.println("Cleared");
    } else {
      entered += k;
      Serial.print('*');
    }
  }
}

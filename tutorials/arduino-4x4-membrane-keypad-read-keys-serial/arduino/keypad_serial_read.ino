// Reads a 4×4 membrane matrix keypad and prints each pressed key to the Serial Monitor.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-4x4-membrane-keypad-read-keys-serial
// Parts used: https://shillehtek.com/products/4x4-membrane-matrix-keypad-16-key-switch-module-for-arduino-diy
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

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

Keypad pad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  char k = pad.getKey();
  if (k) {
    Serial.print(F("Pressed: "));
    Serial.println(k);
  }
}

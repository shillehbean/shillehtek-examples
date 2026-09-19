// Scans a 4x4 matrix keypad, maps each key to a frequency for two octaves, plays the note on a passive buzzer, and prints the key and frequency to Serial.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-4x4-keypad-buzzer-piano-two-octaves
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/4x4-membrane-matrix-keypad-16-key-switch-module-for-arduino-diy
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Keypad.h>

const byte ROWS = 4, COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};
Keypad pad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int BUZZ = 11;

int noteFor(char k) {                 // C4 up to D6, reading the keypad left-to-right
  switch (k) {
    case '1': return 262;  case '2': return 294;  case '3': return 330;  case 'A': return 349;
    case '4': return 392;  case '5': return 440;  case '6': return 494;  case 'B': return 523;
    case '7': return 587;  case '8': return 659;  case '9': return 698;  case 'C': return 784;
    case '*': return 880;  case '0': return 988;  case '#': return 1047; case 'D': return 1175;
  }
  return 0;
}

void setup() {
  pinMode(BUZZ, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  char k = pad.getKey();              // scans the matrix every call
  if (k) {                            // a new key went down: start its note
    int f = noteFor(k);
    tone(BUZZ, f);
    Serial.print(k); Serial.print(" -> "); Serial.print(f); Serial.println(" Hz");
  }
  if (pad.getState() == RELEASED) noTone(BUZZ);   // key came up: stop the note
}

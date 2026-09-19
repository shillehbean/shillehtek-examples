// Arduino sketch implementing a 4x4 keypad door lock: reads keypad input, masks entry on an LCD1602, verifies the 4-digit code against EEPROM-stored password, and triggers a relay to operate a lock.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-4x4-keypad-eeprom-door-lock
// Parts used: https://shillehtek.com/products/4x4-membrane-matrix-keypad-16-key-switch-module-for-arduino-diy
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
//             https://shillehtek.com/products/1-channel-5v-relay-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Keypad.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

LiquidCrystal lcd(9, 8, 7, 6, 5, 4);
const int relayPin = 10;

const byte ROWS = 4, COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'}, {'4','5','6','B'},
  {'7','8','9','C'}, {'*','0','#','D'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {A4, A5, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char entered[5];
byte pos = 0;

bool checkPassword() {
  for (byte i = 0; i < 4; i++)
    if (entered[i] != (char)EEPROM.read(i)) return false;
  return true;
}

void setup() {
  lcd.begin(16, 2);
  pinMode(relayPin, OUTPUT);
  if (EEPROM.read(0) == 255) {          // first boot: store default 1234
    const char def[4] = {'1','2','3','4'};
    for (byte i = 0; i < 4; i++) EEPROM.write(i, def[i]);
  }
  lcd.print("Enter Password:");
}

void loop() {
  char key = keypad.getKey();
  if (!key) return;

  entered[pos++] = key;
  lcd.setCursor(pos - 1, 1);
  lcd.print('*');

  if (pos == 4) {
    lcd.clear();
    if (checkPassword()) {
      lcd.print("Access Granted");
      digitalWrite(relayPin, HIGH);     // fire the lock
      delay(5000);
      digitalWrite(relayPin, LOW);
    } else {
      lcd.print("Access Denied");
      delay(2000);
    }
    pos = 0;
    lcd.clear();
    lcd.print("Enter Password:");
  }
}

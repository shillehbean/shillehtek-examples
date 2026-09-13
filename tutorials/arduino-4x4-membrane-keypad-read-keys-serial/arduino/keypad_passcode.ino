// Implements a simple passcode checker: collect digits, use '#' to submit, '*' to clear, and pulse a lock output on correct code.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-4x4-membrane-keypad-read-keys-serial
// Parts used: https://shillehtek.com/products/4x4-membrane-matrix-keypad-16-key-switch-module-for-arduino-diy
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const String EXPECTED = "1234";
String entered;
const int LOCK_PIN = 13;

void loop() {
  char k = pad.getKey();
  if (!k) return;

  if (k == '#') {
    if (entered == EXPECTED) {
      Serial.println(F("ACCESS GRANTED"));
      digitalWrite(LOCK_PIN, HIGH);
      delay(2000);
      digitalWrite(LOCK_PIN, LOW);
    } else {
      Serial.println(F("denied"));
    }
    entered = "";
  } else if (k == '*') {
    entered = "";
    Serial.println(F("cleared"));
  } else {
    entered += k;
    Serial.println(entered);
  }
}

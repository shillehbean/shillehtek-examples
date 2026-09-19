// Arduino sketch that counts people entering and leaving using two IR sensors, shows In/Out/Inside on an I2C LCD, and controls a relay to switch lights based on occupancy.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-ir-sensors-visitor-counter-auto-lights
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
//             https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int S1 = 2, S2 = 3, RELAY = 7;              // S1 = outer sensor, S2 = inner sensor
const unsigned long WINDOW = 1000;                // ms allowed between the two beams
int in = 0, out = 0, inside = 0;

bool blocked(int pin) { return digitalRead(pin) == LOW; }

void show() {
  lcd.setCursor(0, 0); lcd.print("In:"); lcd.print(in); lcd.print(" Out:"); lcd.print(out); lcd.print("    ");
  lcd.setCursor(0, 1); lcd.print("Inside: "); lcd.print(inside); lcd.print("      ");
  digitalWrite(RELAY, inside > 0 ? HIGH : LOW);   // lights on while anyone is in the room
}

// wait (up to WINDOW ms) for the second sensor; returns true if it tripped
bool waitFor(int pin) {
  unsigned long t0 = millis();
  while (millis() - t0 < WINDOW) if (blocked(pin)) return true;
  return false;
}

void waitClear() { while (blocked(S1) || blocked(S2)); delay(150); }   // both beams free again

void setup() {
  pinMode(S1, INPUT); pinMode(S2, INPUT); pinMode(RELAY, OUTPUT);
  lcd.init(); lcd.backlight();
  show();
}

void loop() {
  if (blocked(S1)) {                              // outer beam first: someone entering
    if (waitFor(S2)) { in++; inside++; show(); }
    waitClear();
  }
  else if (blocked(S2)) {                         // inner beam first: someone leaving
    if (waitFor(S1) && inside > 0) { out++; inside--; show(); }
    waitClear();
  }
}

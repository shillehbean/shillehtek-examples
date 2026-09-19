// Arduino sketch that implements a millis()-based stopwatch with Start/Stop, Lap, and Reset buttons, displays time and lap on an I2C LCD1602, and uses LEDs and a buzzer for feedback.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-lcd1602-millis-stopwatch
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
//             https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int BTN_START = A0, BTN_LAP = A1, BTN_RESET = A2;
const int LED_RUN = 8, LED_STOP = 9, BUZZ = 13;

bool running = false;
unsigned long startMs = 0, elapsed = 0, lapMs = 0;

bool pressed(int pin) {                       // debounced press + click, waits for release
  if (digitalRead(pin) == LOW) {
    delay(25);
    if (digitalRead(pin) == LOW) {
      tone(BUZZ, 1200, 30);
      while (digitalRead(pin) == LOW);
      return true;
    }
  }
  return false;
}

void printTime(int col, int row, unsigned long ms) {
  unsigned long hund = (ms / 10) % 100, sec = (ms / 1000) % 60, min = ms / 60000;
  char buf[12];
  sprintf(buf, "%02lu:%02lu.%02lu", min, sec, hund);   // MM:SS.hh
  lcd.setCursor(col, row); lcd.print(buf);
}

void setup() {
  pinMode(BTN_START, INPUT_PULLUP); pinMode(BTN_LAP, INPUT_PULLUP); pinMode(BTN_RESET, INPUT_PULLUP);
  pinMode(LED_RUN, OUTPUT); pinMode(LED_STOP, OUTPUT);
  lcd.init(); lcd.backlight();
  lcd.setCursor(0, 0); lcd.print("TIME");
  lcd.setCursor(0, 1); lcd.print("LAP");
}

void loop() {
  if (pressed(BTN_START)) {
    if (running) { elapsed += millis() - startMs; running = false; }   // stop: bank the time
    else         { startMs = millis(); running = true; }               // start: new segment
  }
  if (pressed(BTN_LAP) && running)  lapMs = elapsed + (millis() - startMs);
  if (pressed(BTN_RESET) && !running) { elapsed = 0; lapMs = 0; }

  unsigned long now = elapsed + (running ? millis() - startMs : 0);
  printTime(6, 0, now);
  printTime(6, 1, lapMs);
  digitalWrite(LED_RUN, running);
  digitalWrite(LED_STOP, !running);
}

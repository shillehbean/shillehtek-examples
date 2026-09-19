// Arduino sketch implementing a knob-set countdown kitchen timer with an I2C LCD1602, Start/Reset buttons, and a buzzer using a simple state machine.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-lcd1602-kitchen-timer-countdown
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
//             https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int POT = A0, START = 4, RESET = 5, BUZZ = 6;
enum State { SETTING, RUNNING, ALARM };
State state = SETTING;

long secondsLeft = 0;
unsigned long lastTick = 0;

void showTime(long s, bool colon) {
  lcd.setCursor(4, 1);
  if (s / 60 < 10) lcd.print('0');
  lcd.print(s / 60); lcd.print(colon ? ':' : ' ');
  if (s % 60 < 10) lcd.print('0');
  lcd.print(s % 60);
}

void setup() {
  pinMode(START, INPUT_PULLUP); pinMode(RESET, INPUT_PULLUP);
  lcd.init(); lcd.backlight();
}

void loop() {
  if (digitalRead(RESET) == LOW) { state = SETTING; noTone(BUZZ); delay(200); }

  switch (state) {
    case SETTING: {
      // knob -> 0..60 min in 30 s steps
      secondsLeft = (map(analogRead(POT), 0, 1023, 0, 120)) * 30L;
      lcd.setCursor(0, 0); lcd.print("Set time:  START");
      showTime(secondsLeft, true);
      if (digitalRead(START) == LOW && secondsLeft > 0) {
        state = RUNNING; lastTick = millis(); delay(200);
      }
      break;
    }
    case RUNNING: {
      lcd.setCursor(0, 0); lcd.print("Counting down...");
      if (millis() - lastTick >= 1000) {
        lastTick += 1000;
        secondsLeft--;
        if (secondsLeft <= 0) state = ALARM;
      }
      showTime(secondsLeft, (millis() / 500) % 2);   // blinking colon
      break;
    }
    case ALARM: {
      lcd.setCursor(0, 0); lcd.print("   TIME'S UP!   ");
      showTime(0, (millis() / 250) % 2);
      tone(BUZZ, (millis() / 250) % 2 ? 2000 : 0);   // chirping alarm
      break;
    }
  }
}

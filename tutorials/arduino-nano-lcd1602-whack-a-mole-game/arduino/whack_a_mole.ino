// Main Arduino sketch implementing the Whack-a-Mole game: controls LEDs and buttons, updates score and countdown bar on an I2C LCD, and plays buzzer sounds.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-lcd1602-whack-a-mole-game
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/200pcs-6mm-light-touch-button-switch-kit-plastic-box-4-3-5-6-7-8-9-10-12-14-16mm
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int leds[5] = {2, 3, 4, 5, 6};
const int btns[5] = {8, 9, 10, 11, 12};
const int BUZZ = 13;
const unsigned long GAME_MS = 30000;

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(btns[i], INPUT_PULLUP);
  }
  lcd.init(); lcd.backlight();
  randomSeed(analogRead(A0));
}

void loop() {
  int score = 0;
  unsigned long start = millis();

  while (millis() - start < GAME_MS) {
    // reaction window shrinks from 1200ms to 500ms as time runs out
    long window = map(millis() - start, 0, GAME_MS, 1200, 500);

    int mole = random(5);
    digitalWrite(leds[mole], HIGH);
    unsigned long popped = millis();
    bool hit = false;

    while (millis() - popped < (unsigned long)window) {
      if (digitalRead(btns[mole]) == LOW) { hit = true; break; }
    }
    digitalWrite(leds[mole], LOW);

    if (hit) { score++; tone(BUZZ, 1200, 80); }
    else     { tone(BUZZ, 200, 120); }

    lcd.setCursor(0, 0);
    lcd.print("Score: "); lcd.print(score); lcd.print("  ");

    // countdown bar on line 2: one block per 1/16th of time left
    int blocks = map(GAME_MS - (millis() - start), 0, GAME_MS, 0, 16);
    lcd.setCursor(0, 1);
    for (int i = 0; i < 16; i++) lcd.print(i < blocks ? (char)255 : ' ');

    delay(random(200, 600));   // breather between moles
  }

  lcd.clear();
  lcd.print("Final score!");
  delay(4000);
  lcd.clear();
}

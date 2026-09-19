// Partial Simon game sketch from the article; setup() initialization is missing and must be supplied before use.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-lcd1602-simon-memory-game
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/200pcs-6mm-light-touch-button-switch-kit-plastic-box-4-3-5-6-7-8-9-10-12-14-16mm
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int leds[4]    = {8, 9, 10, 11};
const int buttons[4] = {2, 3, 4, 5};
const int tones[4]   = {262, 330, 392, 523};   // C E G C
const int BUZZER = 12;

int sequence[100];
int level = 0;

void playStep(int c, int ms) {
  digitalWrite(leds[c], HIGH);
  tone(BUZZER, tones[c], ms);
  delay(ms);
  digitalWrite(leds[c], LOW);
  delay(120);
}

int waitForButton() {
  while (true)
    for (int i = 0; i < 4; i++)
      if (digitalRead(buttons[i]) == LOW) {
        playStep(i, 200);          // echo the press
        while (digitalRead(buttons[i]) == LOW);  // wait for release
        return i;
      }
}

void loop() {
  sequence[level++] = random(4);            // add a step

  for (int i = 0; i < level; i++)           // play the sequence
    playStep(sequence[i], 400);

  for (int i = 0; i < level; i++)           // read the player
    if (waitForButton() != sequence[i]) {
      tone(BUZZER, 110, 700);               // fail sound
      lcd.clear();
      lcd.print("Score: ");
      lcd.print(level - 1);
      delay(2500);
      level = 0;                            // restart
      return;
    }

  delay(600);                               // next round
}

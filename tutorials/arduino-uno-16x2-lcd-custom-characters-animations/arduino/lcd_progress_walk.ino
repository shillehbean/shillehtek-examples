// Provides functions to create partial-fill characters for a smooth 80-step progress bar and to animate a two-frame walking figure on the top row of the LCD.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-16x2-lcd-custom-characters-animations
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
//             https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte walk[2][8] = {                          // two frames of a walking figure
  {B01110, B01110, B00100, B01110, B10101, B00100, B01010, B10001},   // legs apart
  {B01110, B01110, B00100, B11111, B00100, B00100, B00100, B00110}    // legs together
};

void makeBarChars() {                        // slots 1..5 = 1..5 columns filled
  for (int n = 1; n <= 5; n++) {
    byte row = 0, g[8];
    for (int c = 0; c < n; c++) row |= (B10000 >> c);
    for (int r = 0; r < 8; r++) g[r] = row;
    lcd.createChar(n, g);
  }
}

void bar(int pct) {                          // 0..100 % across the bottom row, 80 pixel columns
  int cols = map(pct, 0, 100, 0, 80);
  lcd.setCursor(0, 1);
  for (int cell = 0; cell < 16; cell++) {
    int fill = constrain(cols - cell * 5, 0, 5);
    if (fill == 0) lcd.print(" "); else lcd.write(byte(fill));
  }
}

void setup() { lcd.init(); lcd.backlight(); makeBarChars(); }

void loop() {
  static int x = 0, frame = 0, pct = 0;
  lcd.createChar(0, walk[frame]);            // redefine slot 0 -> the figure on screen changes instantly
  lcd.setCursor(x, 0); lcd.write(byte(0));   // draw the walker at its current cell
  bar(pct);
  delay(250);
  lcd.setCursor(x, 0); lcd.print(" ");       // erase before moving on
  frame ^= 1;                                // next frame
  x = (x + 1) % 16;                          // next cell
  pct = (pct + 3) % 101;
}

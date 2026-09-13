// Complete Arduino sketch using U8glib to draw two text pages on a SH1106 128x64 I2C OLED and alternate between them with delays.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-sh1106-oled-i2c-text-pages-demo
// Parts used: https://shillehtek.com/products/1-3-i2c-white-oled-display-module-4-pin-sh1106
//             https://shillehtek.com/products/1-3-i2c-blue-oled-display-module-4-pin-sh1106
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include "U8glib.h"
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);

void draw(void) {
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(0, 10);
  u8g.print("This is the 1.3\"");
  u8g.setPrintPos(0, 25);
  u8g.print("White i2c OLED");
  u8g.setPrintPos(0, 40);
  u8g.print("with Arduino.");
}

void draw2(void) {
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(0, 10);
  u8g.print("Second screen -");
  u8g.setPrintPos(0, 25);
  u8g.print("swap in your own");
  u8g.setPrintPos(0, 40);
  u8g.setFont(u8g_font_profont10);
  u8g.print("sensor readings here.");
}

void setup(void) {
}

void loop(void) {
  u8g.firstPage();
  do {
    draw();
  } while (u8g.nextPage());
  delay(3500);

  u8g.firstPage();
  do {
    draw2();
  } while (u8g.nextPage());
  delay(3500);
}

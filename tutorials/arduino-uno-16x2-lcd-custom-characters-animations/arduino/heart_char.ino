// Defines a single 8-byte bitmap for a heart custom character compatible with HD44780 createChar().
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-16x2-lcd-custom-characters-animations
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
//             https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
// More examples: https://github.com/shillehbean/shillehtek-examples
//

byte heart[8] = {
  B00000,
  B01010,   //  .#.#.
  B11111,   //  #####
  B11111,   //  #####
  B01110,   //  .###.
  B00100,   //  ..#..
  B00000,
  B00000
};

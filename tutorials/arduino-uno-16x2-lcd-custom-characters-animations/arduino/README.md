# Arduino examples

- [`heart_char.ino`](./heart_char.ino) — Defines a single 8-byte bitmap for a heart custom character compatible with HD44780 createChar().
- [`lcd_custom_chars.ino`](./lcd_custom_chars.ino) — Initializes a 16x2 I2C LCD, creates four custom characters (heart, smiley, bell, degree) and displays them alongside text.
- [`lcd_progress_walk.ino`](./lcd_progress_walk.ino) — Provides functions to create partial-fill characters for a smooth 80-step progress bar and to animate a two-frame walking figure on the top row of the LCD.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/arduino-uno-16x2-lcd-custom-characters-animations)  
Parts used: [Arduino Uno R3 Super Starter Kit](https://shillehtek.com/products/arduino-uno-r3-starter-kit) · [LCD1602 16x2 Display](https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module) · [PCF8574 I2C Adapter](https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd) · [Dupont Jumper Wires](https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire)

// Initialize an SSD1306 128x64 I2C OLED, clear the buffer, write "Hello!" with larger text, and send it to the display.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-tm1637-ssd1306-epaper-pick-display
// Parts used: https://shillehtek.com/products/4-bits-tm1637-red-led-display-module-clock
//             https://shillehtek.com/products/2-13-inch-black-white-e-paper-hat-ink-screen-spi-250x122-for-raspberry-pi
//             https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 oled(128, 64, &Wire, -1);
oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
oled.clearDisplay();
oled.setCursor(0,0);
oled.setTextSize(2);
oled.print("Hello!");
oled.display();

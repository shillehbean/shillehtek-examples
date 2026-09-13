// Initializes an SSD1306 I2C OLED, prints two lines of text at different sizes, draws a rectangle and a filled rectangle, then updates the display.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-ssd1306-oled-display-text-graphics
// Parts used: https://shillehtek.com/products/0-96-i2c-blue-oled-display-module-4-pin-ssd1306
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define WIDTH 128
#define HEIGHT 64
Adafruit_SSD1306 oled(WIDTH, HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 init failed");
    while (1);
  }
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0);
  oled.println("ShillehTek");
  oled.setTextSize(1);
  oled.println("Hello, OLED!");
  oled.drawRect(0, 40, 128, 20, SSD1306_WHITE);
  oled.fillRect(2, 42, 60, 16, SSD1306_WHITE);
  oled.display();
}

void loop() {}

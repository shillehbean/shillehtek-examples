// Initializes the SSD1306 via I2C using the Adafruit_GFX and Adafruit_SSD1306 libraries and displays static text and device info on a 128×64 OLED.
//
// Buy this module: https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/0-96-i2c-white-oled-display-module-4-pin-ssd1306-manual
// More examples: https://github.com/shillehtek/examples
//

// 0.96" SSD1306 OLED - Arduino I2C Example
// Libraries: Adafruit_GFX + Adafruit_SSD1306 (Library Manager)
// Wiring: SDA -> A4, SCL -> A5

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDR   0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR)) {
    Serial.println("SSD1306 not found at 0x3C");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("ShillehTek");
  display.setTextSize(1);
  display.setCursor(0, 24);
  display.println("SSD1306 OLED");
  display.println("128 x 64");
  display.display();
}

void loop() {
  // Static demo - nothing to update
}

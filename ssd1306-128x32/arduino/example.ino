// Initializes the SSD1306 over I2C on an Arduino and displays a numeric counter with a moving progress bar on the 128x32 OLED.
//
// Buy this module: https://shillehtek.com/products/oled-ssd1306-128x32-i2c-0-91in
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/oled-ssd1306-128x32-i2c-0-91in-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// 0.91" SSD1306 128x32 I2C OLED - Arduino Example
// SDA->A4, SCL->A5, VCC->5V, GND->GND
// Libraries: Adafruit SSD1306 + Adafruit GFX (Library Manager)

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
unsigned int count = 0;

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("SSD1306 not found at 0x3C");
    for (;;);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("ShillehTek 128x32");

  display.setTextSize(2);
  display.setCursor(0, 12);
  display.print("N=");
  display.print(count);

  int barWidth = (count * 4) % SCREEN_WIDTH;   // moving bar
  display.fillRect(0, 30, barWidth, 2, SSD1306_WHITE);

  display.display();
  count++;
  delay(200);
}

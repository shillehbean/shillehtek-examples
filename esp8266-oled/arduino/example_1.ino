// Initializes I2C on GPIO4/GPIO5, starts the SSD1306 128x64 OLED at address 0x3C, and displays a large "Hello!" message.
//
// Buy this module: https://shillehtek.com/products/nodemcu-esp8266-development-board-with-0-96-inch-oled-display-type-c-with-soldering-and-foam
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/nodemcu-esp8266-development-board-with-0-96-inch-oled-display-type-c-with-soldering-and-foam-manual
// More examples: https://github.com/shillehtek/examples
//

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  Wire.begin(4, 5);  // SDA=GPIO4, SCL=GPIO5
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 16);
  display.println("Hello!");
  display.display();
}

void loop() {}

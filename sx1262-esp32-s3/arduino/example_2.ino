// Initializes the OLED display on the Heltec WiFi LoRa 32 V3, powers the Vext rail, and writes a three-line "Hello" message to the screen.
//
// Buy this module: https://shillehtek.com/products/sx1262-esp32-s3-0-96-inch-blue-oled-display-bluetooth-wifi-kit-32-module-iot-development-board-for-arduino-w-antenna-868-915mhz-with-soldering-and-foam
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/sx1262-esp32-s3-0-96-inch-blue-oled-display-bluetooth-wifi-kit-32-module-iot-development-board-for-arduino-w-antenna-868-915mhz-with-soldering-and-foam-manual
// More examples: https://github.com/shillehtek/examples
//

// Heltec WiFi LoRa 32 V3 - OLED "Hello World"

#include <Wire.h>
#include <HT_SSD1306Wire.h>

SSD1306Wire display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED);

void setup() {
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, LOW);   // power on Vext rail
  delay(50);

  display.init();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Hello,");
  display.drawString(0, 20, "ShillehTek!");
  display.drawString(0, 40, "WiFi LoRa V3");
  display.display();
}

void loop() {}

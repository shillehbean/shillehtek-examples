// Arduino sketch that selects TCA9548A channels to initialize and update SSD1306 OLED displays, showing channel number and uptime.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-tca9548a-8-i2c-devices
// Parts used: https://shillehtek.com/products/cjmcu-9548-tca9548a-1-to-8-i2c-8-channel-multiplexer-module
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define MUX_ADDR 0x70
void selectMuxChan(uint8_t ch) {
  Wire.beginTransmission(MUX_ADDR);
  Wire.write(1 << ch);
  Wire.endTransmission();
}

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

void setup() {
  Wire.begin();
  for (int ch = 0; ch < 4; ch++) {
    selectMuxChan(ch);
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    oled.clearDisplay();
    oled.setCursor(0, 0);
    oled.setTextSize(3); oled.setTextColor(WHITE);
    oled.printf("CH %d", ch);
    oled.display();
  }
}
void loop() {
  for (int ch = 0; ch < 4; ch++) {
    selectMuxChan(ch);
    oled.clearDisplay();
    oled.setCursor(0, 0);
    oled.setTextSize(2);
    oled.print("uptime ");
    oled.print(millis() / 1000);
    oled.display();
  }
  delay(500);
}

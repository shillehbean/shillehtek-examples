// Arduino Uno master sketch: requests four bytes (temperature and humidity in tenths) from the peripheral at 0x08, displays the values on an SSD1306 128x64 OLED and prints to Serial, and (intended to) send an LED control command back to the peripheral (note: this block is truncated at the end).
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-nano-i2c-dht11-oled-display
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/shillehtek-dht11-with-cables
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 oled(128, 64, &Wire, -1);
#define PERIPHERAL 0x08
int16_t t10 = 0, h10 = 0;                  // last values received, in tenths

void setup() {
  Serial.begin(9600);
  Wire.begin();                            // no address = controller
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(SSD1306_WHITE);
}

void loop() {
  // 1) request 4 bytes: temperature and humidity in tenths
  int n = Wire.requestFrom(PERIPHERAL, 4);
  if (n == 4) {
    t10 = (Wire.read() << 8) | Wire.read();
    h10 = (Wire.read() << 8) | Wire.read();
    oled.clearDisplay();
    oled.setTextSize(1); oled.setCursor(0, 0);  oled.print("From Nano @0x08");
    oled.setTextSize(2); oled.setCursor(0, 16); oled.print(t10 / 10.0, 1); oled.print(" C");
    oled.setCursor(0, 40);                      oled.print(h10 / 10.0, 1); oled.print(" %");
    oled.display();
    Serial.print(t10 / 10.0); Serial.print(" C  "); Serial.print(h10 / 10.0); Serial.println(" %");
  } else {
    Serial.println("no answer from 0x08 - check SDA/SCL/GND");
  }

  // 2) send a command the other way: light the Nano's LED above 25.0 C
  Wire.beginTransmission(PERIPHERAL);
  Wire.write((n == 4 && t10 > 250) ? 1 : 0);
  Wire.endTransmission();

  delay(1000);
}

// Reads temperature and humidity from a DHT11 sensor, prints the values to serial, and displays centered temperature and humidity strings on an SSD1306 OLED.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-c6-dht11-oled-centered-temp-logger
// Parts used: https://shillehtek.com/products/esp32-c6-n4-dev-board-presoldered
//             https://shillehtek.com/products/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable
//             https://shillehtek.com/products/shillehtek-dht11-with-cables
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 2          // DHT11 data pin (match your wiring)
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.printf("T: %.1f C  H: %.0f %%\n", t, h);

  display.clearDisplay();

  // center each line using its measured pixel width
  String tempStr = "T:" + String(t, 1) + "C";
  int16_t x1, y1; uint16_t w, hgt;
  display.getTextBounds(tempStr, 0, 0, &x1, &y1, &w, &hgt);
  display.setCursor((SCREEN_WIDTH - w) / 2, 15);
  display.print(tempStr);

  String humStr = "H:" + String(h, 0) + "%";
  display.getTextBounds(humStr, 0, 0, &x1, &y1, &w, &hgt);
  display.setCursor((SCREEN_WIDTH - w) / 2, 40);
  display.print(humStr);

  display.display();
  delay(2000);          // update every 2 s
}

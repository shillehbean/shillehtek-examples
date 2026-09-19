// Reads NMEA data from a NEO‑M8N GPS via SoftwareSerial, computes local time using a UTC offset, and displays the time and date on a 240×240 ST7789 TFT.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-neo-m8n-gps-local-time-clock
// Parts used: https://shillehtek.com/products/gps-module-neo-m8n-antenna-battery-arduino-esp32
//             https://shillehtek.com/products/tft-lcd-1-3-240x240-st7789-esp32-arduino
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_CS   -1   // 7-pin module: CS tied internally
#define TFT_DC    8
#define TFT_RST   9
#define UTC_OFFSET  -5      // your timezone (e.g. -5 = EST)

TinyGPSPlus gps;
SoftwareSerial gpsSerial(4, 3);   // GPS TX -> D4
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  gpsSerial.begin(9600);
  tft.init(240, 240);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);
}

void loop() {
  while (gpsSerial.available()) gps.encode(gpsSerial.read());

  if (gps.time.isUpdated() && gps.date.isValid()) {
    int h = (gps.time.hour() + UTC_OFFSET + 24) % 24;

    char line[16];
    snprintf(line, sizeof(line), "%02d:%02d:%02d",
             h, gps.time.minute(), gps.time.second());
    tft.setTextSize(4);
    tft.setCursor(25, 90);
    tft.print(line);

    snprintf(line, sizeof(line), "%02d/%02d/%04d",
             gps.date.month(), gps.date.day(), gps.date.year());
    tft.setTextSize(2);
    tft.setCursor(55, 150);
    tft.print(line);
  }
}

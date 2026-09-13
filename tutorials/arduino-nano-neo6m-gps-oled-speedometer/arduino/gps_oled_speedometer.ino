// Reads NEO-6M GPS data via SoftwareSerial using TinyGPS++, and displays current speed in km/h and satellite count on an SSD1306 OLED.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-neo6m-gps-oled-speedometer
// Parts used: https://shillehtek.com/products/gt-u7-gps-module-presoldered-1
//             https://shillehtek.com/products/0-96-i2c-blue-oled-display-module-4-pin-ssd1306
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

SoftwareSerial gpsSerial(4, 3);
TinyGPSPlus gps;
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

void setup() {
  Serial.begin(9600); gpsSerial.begin(9600);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(SSD1306_WHITE);
}
void loop() {
  while (gpsSerial.available()) gps.encode(gpsSerial.read());

  oled.clearDisplay();
  if (gps.location.isValid() && gps.speed.isValid()) {
    float kmh = gps.speed.kmph();
    oled.setTextSize(4); oled.setCursor(0, 4);
    oled.print((int)kmh);
    oled.setTextSize(2); oled.setCursor(80, 14); oled.print("kmh");
    oled.setTextSize(1); oled.setCursor(0, 56);
    oled.printf("Sats: %d", gps.satellites.value());
  } else {
    oled.setTextSize(2); oled.setCursor(0, 24);
    oled.println("Searching...");
  }
  oled.display();
}

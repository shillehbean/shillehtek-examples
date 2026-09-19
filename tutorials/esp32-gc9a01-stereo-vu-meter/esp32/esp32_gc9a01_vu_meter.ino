// Reads an analog audio envelope input on the ESP32 and draws a damped, animated needle on a GC9A01 240x240 round TFT to act as a VU meter (single channel).
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-gc9a01-stereo-vu-meter
// Parts used: https://shillehtek.com/products/round-1-28in-ips-lcd-gc9a01-240x240-esp32
//             https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/100pcs-common-diode-kit-1n4148-1n4007-1n5819-1n5399-plastic-bag
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_GC9A01A.h"

#define TFT_DC 2
#define TFT_CS 15
#define DEG2RAD 0.0174532925

Adafruit_GC9A01A tft(TFT_CS, TFT_DC);

const int AUDIO_IN = 34;   // envelope follower output
float needle = 0;          // current needle angle

void setup() {
  tft.begin();
  tft.fillScreen(0xAB21);  // retro dial background color
  // draw the scale arc, tick marks and labels once here
}

void loop() {
  int raw = analogRead(AUDIO_IN);
  float target = map(raw, 0, 4095, -45, 45);   // level  needle angle
  needle += (target - needle) * 0.25;          // damped, homogeneous motion

  // erase the previous needle, then redraw at the new angle
  float x = 120 + 80 * sin(needle * DEG2RAD);
  float y = 150 - 80 * cos(needle * DEG2RAD);
  tft.drawLine(120, 150, x, y, GC9A01A_RED);

  delay(20);
}

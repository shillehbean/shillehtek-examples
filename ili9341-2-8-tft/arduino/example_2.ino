// Reads touch input from an XPT2046 resistive touch controller and prints the raw x, y, z touch coordinates to Serial when the screen is touched.
//
// Buy this module: https://shillehtek.com/products/2-8-spi-tft-lcd-touch-screen-module-240x320-ili9341-for-arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/2-8-spi-tft-lcd-touch-screen-module-240x320-ili9341-for-arduino-manual
// More examples: https://github.com/shillehtek/examples
//

// Install "XPT2046_Touchscreen" by Paul Stoffregen

#include <SPI.h>
#include <XPT2046_Touchscreen.h>

#define T_CS  21
#define T_IRQ 22

XPT2046_Touchscreen ts(T_CS, T_IRQ);

void setup() {
  Serial.begin(115200);
  ts.begin();
  ts.setRotation(1);
}

void loop() {
  if (ts.touched()) {
    TS_Point p = ts.getPoint();
    Serial.print("x="); Serial.print(p.x);
    Serial.print("  y="); Serial.print(p.y);
    Serial.print("  z="); Serial.println(p.z);
  }
  delay(50);
}

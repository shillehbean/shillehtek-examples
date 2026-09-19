// Reads the 64 pixel temperatures, finds the hottest pixel and its (x,y) coordinates, and prints the hottest temperature with a warm-body hint.
//
// Buy this module: https://shillehtek.com/products/amg8833-ir-thermal-camera-sensor-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/amg8833-ir-thermal-camera-sensor-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Adafruit_AMG88xx.h>

Adafruit_AMG88xx amg;
float px[64];

void setup() {
  Serial.begin(115200);
  if (!amg.begin()) { Serial.println("Sensor missing"); while (1); }
}

void loop() {
  amg.readPixels(px);
  float maxT = -100;
  int maxI = 0;
  for (int i = 0; i < 64; i++) {
    if (px[i] > maxT) { maxT = px[i]; maxI = i; }
  }
  Serial.printf("Hottest: %.1f C at (%d,%d)  %s\n",
                maxT, maxI % 8, maxI / 8,
                maxT > 28 ? "<- warm body?" : "");
  delay(300);
}

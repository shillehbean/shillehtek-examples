// Reads the AMG8833 8x8 temperature array and prints a tab-separated grid of pixel temperatures to the Serial console every 500 ms.
//
// Buy this module: https://shillehtek.com/products/amg8833-ir-thermal-camera-sensor-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/amg8833-ir-thermal-camera-sensor-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Library Manager: install "Adafruit AMG88xx Library"
#include <Adafruit_AMG88xx.h>

Adafruit_AMG88xx amg;
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];

void setup() {
  Serial.begin(115200);
  if (!amg.begin()) {          // 0x69 default
    Serial.println("AMG8833 not found - check wiring");
    while (1);
  }
  delay(100);
}

void loop() {
  amg.readPixels(pixels);
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      Serial.print(pixels[y * 8 + x], 1);
      Serial.print("\t");
    }
    Serial.println();
  }
  Serial.println("----------");
  delay(500);
}

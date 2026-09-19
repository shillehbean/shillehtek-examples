// ESP32 example using the HX711 library to initialize the sensor on specified GPIO pins, tare, and print averaged weight in grams with a timeout-based ready check.
//
// Buy this module: https://shillehtek.com/products/load-cell-5kg-hx711-arduino-esp32-kit
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/load-cell-5kg-hx711-arduino-esp32-kit-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// 5kg Load Cell + HX711 - ESP32 Example
// DT -> GPIO 16, SCK -> GPIO 4, VCC -> 3V3, GND -> GND
// Library: "HX711" by Bogdan Necula (works on ESP32)

#include "HX711.h"

const int DT_PIN = 16;
const int SCK_PIN = 4;

float CALIBRATION_FACTOR = 1.0;  // set after calibrating

HX711 scale;

void setup() {
  Serial.begin(115200);
  scale.begin(DT_PIN, SCK_PIN);

  Serial.println("Remove all weight... taring in 3 s");
  delay(3000);
  scale.tare();
  scale.set_scale(CALIBRATION_FACTOR);
  Serial.println("Ready.");
}

void loop() {
  if (scale.wait_ready_timeout(1000)) {
    float grams = scale.get_units(10);
    Serial.printf("Weight: %.1f g\n", grams);
  } else {
    Serial.println("HX711 not responding - check wiring");
  }
  delay(500);
}

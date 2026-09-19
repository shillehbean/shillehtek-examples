// Arduino example using the HX711 Arduino library to tare the scale, set a calibration factor, and print raw ADC counts and averaged weight in grams over serial.
//
// Buy this module: https://shillehtek.com/products/load-cell-5kg-hx711-arduino-esp32-kit
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/load-cell-5kg-hx711-arduino-esp32-kit-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// 5kg Load Cell + HX711 - Arduino Example
// DT -> D3, SCK -> D2, VCC -> 5V, GND -> GND
// Library: "HX711" by Bogdan Necula (bogde)

#include "HX711.h"

const int DT_PIN = 3;
const int SCK_PIN = 2;

// Start with 1.0, then calibrate:
// factor = (raw with weight - raw empty) / weight in grams
float CALIBRATION_FACTOR = 1.0;

HX711 scale;

void setup() {
  Serial.begin(9600);
  scale.begin(DT_PIN, SCK_PIN);

  Serial.println("Remove all weight... taring in 3 s");
  delay(3000);
  scale.tare();                       // zero the empty platform
  scale.set_scale(CALIBRATION_FACTOR);
  Serial.println("Ready. Place a known weight to calibrate,");
  Serial.println("or start weighing if already calibrated.");
}

void loop() {
  if (scale.is_ready()) {
    // Average 10 readings for a steady value
    float grams = scale.get_units(10);
    long raw = scale.get_value(10);   // tared raw counts (for calibration)

    Serial.print("Raw: ");
    Serial.print(raw);
    Serial.print("  |  Weight: ");
    Serial.print(grams, 1);
    Serial.println(" g");
  } else {
    Serial.println("HX711 not responding - check wiring");
  }
  delay(500);
}

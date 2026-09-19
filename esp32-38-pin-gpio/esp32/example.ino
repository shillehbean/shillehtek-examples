// Read an ADC1 pin (GPIO34) while Wi‑Fi is active and print the raw ADC value and calculated voltage to demonstrate ADC1 works with Wi‑Fi enabled.
//
// Buy this module: https://shillehtek.com/products/esp32-38-pin-gpio-expansion-breakout
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-38-pin-gpio-expansion-breakout-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Proof of the ADC rule: GPIO 34 (ADC1) keeps working with Wi-Fi on;
// an ADC2 pin (e.g. GPIO 25) would return zeros here.
#include <WiFi.h>

const int SENSOR = 34;   // input-only ADC1 pin on the breakout

void setup() {
  Serial.begin(115200);
  analogSetPinAttenuation(SENSOR, ADC_11db);
  WiFi.begin("YourNetwork", "YourPassword");   // Wi-Fi active
}

void loop() {
  int raw = analogRead(SENSOR);
  float volts = raw * (3.3 / 4095.0);
  Serial.printf("ADC1 raw: %d  (%.2f V)  WiFi: %s\n",
                raw, volts,
                WiFi.status() == WL_CONNECTED ? "connected" : "...");
  delay(500);
}

// Uses the ESP32 ADC (GPIO36 / ADC1_CH0) with the same voltage divider to measure the XL4015 output, converts 12‑bit ADC readings to voltage using a 3.3 V reference, and prints the rail voltage every 500 ms.
//
// Buy this module: https://shillehtek.com/products/dc-dc-xl4015-adjustable-step-down-module-5a-75w-with-3-bit-digital-voltmeter-display
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/dc-dc-xl4015-adjustable-step-down-module-5a-75w-with-3-bit-digital-voltmeter-display-manual
// More examples: https://github.com/shillehtek/examples
//

// ESP32 - monitor XL4015 output rail
// Same divider, ADC1_CH0 = GPIO 36

const int sensePin = 36;
const float DIV_RATIO = 4.0;
const float VREF = 3.3;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);  // 0-4095
}

void loop() {
  int raw = analogRead(sensePin);
  float vAtPin = raw * (VREF / 4095.0);
  float vRail = vAtPin * DIV_RATIO;
  Serial.printf("Rail: %.2f V\n", vRail);
  delay(500);
}

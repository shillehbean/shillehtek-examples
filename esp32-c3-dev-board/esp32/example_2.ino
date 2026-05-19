// Reads a 10k potentiometer on ADC A0 (GPIO0) with 12-bit resolution, converts the raw value to voltage, and prints both raw and voltage readings to the serial console.
//
// Buy this module: https://shillehtek.com/products/esp32-c3-dev-board-4mb-wifi-presoldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-c3-dev-board-4mb-wifi-presoldered-manual
// More examples: https://github.com/shillehtek/examples
//

// ESP32-C3 - Read a 10k potentiometer on A0 (GPIO0)
// Wire: pot ends to 3V3 and GND, wiper to GPIO0

const int potPin = 0;  // A0 = GPIO0

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);  // 0 - 4095
}

void loop() {
  int raw = analogRead(potPin);
  float voltage = raw * 3.3 / 4095.0;
  Serial.printf("Raw: %4d   Voltage: %.2f V\n", raw, voltage);
  delay(200);
}

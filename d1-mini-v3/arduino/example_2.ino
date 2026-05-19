// Reads the board's single ADC channel (A0) and prints the raw 10-bit value and the converted 0–3.2V voltage to serial.
//
// Buy this module: https://shillehtek.com/products/esp8266-d1-mini-v3-4mb-dev-board-presoldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp8266-d1-mini-v3-4mb-dev-board-presoldered-manual
// More examples: https://github.com/shillehtek/examples
//

// D1 Mini V3 - read the single ADC channel on A0
// The on-board divider gives 0 - 3.2V input range, 10-bit (0 - 1023)

void setup() {
  Serial.begin(115200);
}

void loop() {
  int raw = analogRead(A0);
  float voltage = raw * 3.2 / 1023.0;
  Serial.print("Raw="); Serial.print(raw);
  Serial.print("  V="); Serial.println(voltage, 3);
  delay(200);
}

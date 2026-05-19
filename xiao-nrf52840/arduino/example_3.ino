// Reads a 12-bit ADC value from A0 and prints the raw sample and its converted voltage to the serial console.
//
// Buy this module: https://shillehtek.com/products/xiao-seeed-nrf52840-pre-soldered-with-usb-c-cable
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/xiao-seeed-nrf52840-pre-soldered-with-usb-c-cable-manual
// More examples: https://github.com/shillehtek/examples
//

// XIAO nRF52840 - Read 12-bit analog on A0 (P0.02)
// Default reference is internal 0.6V * 6 = 3.6V; analogRead returns 0-4095.

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
}

void loop() {
  int raw = analogRead(A0);
  float volts = raw * (3.3f / 4095.0f);
  Serial.print(raw);
  Serial.print(" -> ");
  Serial.print(volts, 3);
  Serial.println(" V");
  delay(500);
}

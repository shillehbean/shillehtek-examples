// Reads a 12-bit ADC value from A0 (GP26), converts the raw reading to volts (0–3.3V), and prints both the raw value and voltage to the serial console.
//
// Buy this module: https://shillehtek.com/products/seeed-studio-xiao-rp2040-pre-soldered-with-usb-to-usb-c-cable
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/seeed-studio-xiao-rp2040-pre-soldered-with-usb-to-usb-c-cable-manual
// More examples: https://github.com/shillehtek/examples
//

// XIAO RP2040 - Read 12-bit analog on A0 (GP26)

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

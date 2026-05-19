// Read the analog voltage from the UNO A0 header (mapped to GPIO36/SVP) with 12-bit resolution and print the raw value and voltage.
//
// Buy this module: https://shillehtek.com/products/wifi-and-bluetooth-esp32-4mb-flash-uno-d1-r32-ch340g-development-board-type-b-usb
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/wifi-and-bluetooth-esp32-4mb-flash-uno-d1-r32-ch340g-development-board-type-b-usb-manual
// More examples: https://github.com/shillehtek/examples
//

// D1 R32 - Read analog on UNO header A0 (mapped to GPIO 36 / SVP)

const int analogPin = 36;  // UNO A0 header position

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);  // 12-bit (0..4095)
}

void loop() {
  int raw = analogRead(analogPin);
  float volts = raw * 3.3 / 4095.0;
  Serial.printf("Raw: %d   V: %.2f\n", raw, volts);
  delay(500);
}

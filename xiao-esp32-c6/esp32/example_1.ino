// Blinks an external LED connected to GPIO0 (D0) at a 1 Hz rate using the ESP32 Arduino core.
//
// Buy this module: https://shillehtek.com/products/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable-manual
// More examples: https://github.com/shillehtek/examples
//

// XIAO ESP32-C6 - Blink an external LED on D0
// Board: "XIAO_ESP32C6" in the Arduino IDE (esp32 core v3+)

#define LED_PIN D0   // GPIO0

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}

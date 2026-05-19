// Blink an external LED connected to GPIO2 (D0) by toggling it on and off every 250 ms.
//
// Buy this module: https://shillehtek.com/products/xiao-seeed-esp32c3-pre-soldered-with-usb-to-usb-c-cable
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/xiao-seeed-esp32c3-pre-soldered-with-usb-to-usb-c-cable-manual
// More examples: https://github.com/shillehtek/examples
//

// XIAO ESP32-C3 - Blink an external LED on D0
// Board: "XIAO_ESP32C3" in the Arduino IDE (esp32 core)

#define LED_PIN D0   // GPIO2

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(250);
  digitalWrite(LED_PIN, LOW);
  delay(250);
}

// Blink the onboard LED (GPIO2) on the D1 R32 at 500 ms intervals using the Arduino/ESP32 core.
//
// Buy this module: https://shillehtek.com/products/wifi-and-bluetooth-esp32-4mb-flash-uno-d1-r32-ch340g-development-board-type-b-usb
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/wifi-and-bluetooth-esp32-4mb-flash-uno-d1-r32-ch340g-development-board-type-b-usb-manual
// More examples: https://github.com/shillehtek/examples
//

// D1 R32 ESP32 - Blink onboard LED
// Board: ESP32 Dev Module (or "WEMOS D1 MINI ESP32")
// Upload Speed: 460800

#define LED_PIN 2  // onboard LED on most D1 R32 boards

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}

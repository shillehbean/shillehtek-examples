// Sequentially cycles the on-board RGB LED (active LOW) so each color (red, green, blue) turns on for 400 ms.
//
// Buy this module: https://shillehtek.com/products/xiao-seeed-nrf52840-pre-soldered-with-usb-c-cable
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/xiao-seeed-nrf52840-pre-soldered-with-usb-c-cable-manual
// More examples: https://github.com/shillehtek/examples
//

// XIAO nRF52840 - Cycle the on-board RGB LED
// LEDs are active LOW (HIGH = off, LOW = on).
// Board: "Seeed XIAO nRF52840" (Seeed nRF52 mbed-enabled core)

#define LED_R LED_BUILTIN  // RED  (P0.26)
#define LED_G LED_GREEN    // GREEN (P0.30)
#define LED_B LED_BLUE     // BLUE  (P0.06)

void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

void all_off() {
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED_B, HIGH);
}

void loop() {
  all_off(); digitalWrite(LED_R, LOW); delay(400);
  all_off(); digitalWrite(LED_G, LOW); delay(400);
  all_off(); digitalWrite(LED_B, LOW); delay(400);
}

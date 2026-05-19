// Blinks the onboard user LED on PC13 at 2 Hz (active LOW) using the Arduino API for STM32.
//
// Buy this module: https://shillehtek.com/products/shillehtek-pre-soldered-authentic-stm32f411ceu6
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-pre-soldered-authentic-stm32f411ceu6-manual
// More examples: https://github.com/shillehtek/examples
//

// STM32F411 Black Pill - Blink Example (PC13 user LED)
// Board: "Generic STM32F4 series" -> "BlackPill F411CE"
// Upload method: USB DFU (hold BOOT0, tap NRST first time)

#define LED_PIN PC13   // User LED is on PC13 (active LOW)

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, LOW);   // ON
  delay(250);
  digitalWrite(LED_PIN, HIGH);  // OFF
  delay(250);
}

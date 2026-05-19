// Initializes USB CDC serial and prints system uptime in seconds once per second over the USB virtual COM port.
//
// Buy this module: https://shillehtek.com/products/shillehtek-pre-soldered-authentic-stm32f411ceu6
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-pre-soldered-authentic-stm32f411ceu6-manual
// More examples: https://github.com/shillehtek/examples
//

// STM32F411 Black Pill - Print to Serial Monitor over USB CDC
// In the Tools menu, set "USB support" to "CDC (generic Serial supersede U(S)ART)".

void setup() {
  Serial.begin(115200);
  while (!Serial) { /* wait for USB enumeration */ }
}

void loop() {
  Serial.print("Uptime: ");
  Serial.print(millis() / 1000);
  Serial.println(" s");
  delay(1000);
}

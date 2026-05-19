// Blinks the board's built-in LED (which is active LOW) at a 1 Hz rate.
//
// Buy this module: https://shillehtek.com/products/seeeduino-xiao-samd21-arduino-board-presoldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/seeeduino-xiao-samd21-arduino-board-presoldered-manual
// More examples: https://github.com/shillehtek/examples
//

// Seeeduino XIAO SAMD21 - Built-in LED blink
// Install: Boards Manager -> "Seeed SAMD Boards" by Seeed Studio
// Select Board: "Seeeduino XIAO"

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);   // LED is active LOW
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
}

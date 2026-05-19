// Blink the built-in LED using the Arduino core for Raspberry Pi Pico 2 and print LED state messages to Serial at 115200 baud.
//
// Buy this module: https://shillehtek.com/products/raspberry-pi-pico-2-usb-c-presoldered-headers
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/raspberry-pi-pico-2-usb-c-presoldered-headers-manual
// More examples: https://github.com/shillehtek/examples
//

// Raspberry Pi Pico 2 - Arduino IDE Blink Example
// Install "Raspberry Pi Pico/RP2040/RP2350" board package by Earle Philhower
// Select: Tools > Board > Raspberry Pi Pico 2

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("LED ON");
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("LED OFF");
  delay(500);
}

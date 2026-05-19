// Blinks an external LED connected to D0 (GPIO1) on the XIAO ESP32S3 with a 250 ms on/off cycle using the ESP32 Arduino core.
//
// Buy this module: https://shillehtek.com/products/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable-manual
// More examples: https://github.com/shillehtek/examples
//

// XIAO ESP32-S3 - Blink an external LED on D0
// Board: "XIAO_ESP32S3" in the Arduino IDE (esp32 core)

#define LED_PIN D0   // GPIO1

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(250);
  digitalWrite(LED_PIN, LOW);
  delay(250);
}

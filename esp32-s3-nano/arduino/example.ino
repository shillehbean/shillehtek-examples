// Blinks an external LED connected to D2 (GPIO5) with a 500 ms on/off cycle.
//
// Buy this module: https://shillehtek.com/products/esp32-s3-nano-dev-board-presoldered-wifi-ble
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-s3-nano-dev-board-presoldered-wifi-ble-manual
// More examples: https://github.com/shillehtek/examples
//

// ESP32-S3 Nano - Blink an external LED on D2 (GPIO5)
// Wire LED through a 220 ohm resistor between D2 and GND

const int ledPin = 5;  // D2 = GPIO5

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
}

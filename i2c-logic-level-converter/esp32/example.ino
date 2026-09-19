// Toggles an ESP32 GPIO that is passed through the level shifter to drive a 5V peripheral, printing the pin state over serial.
//
// Buy this module: https://shillehtek.com/products/shillehtek-iic-i2c-logic-level-converter-pre-soldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/iic-i2c-logic-level-converter-pre-soldered-bi-directional
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// ESP32 (3.3V) driving a 5V peripheral through the level shifter.
// Toggles a 5V output via one channel.

const int logicOut = 5;  // ESP32 GPIO, shifted to 5V on the other side

void setup() {
  Serial.begin(115200);
  pinMode(logicOut, OUTPUT);
}

void loop() {
  digitalWrite(logicOut, HIGH);
  Serial.println("5V side: HIGH");
  delay(500);
  digitalWrite(logicOut, LOW);
  Serial.println("5V side: LOW");
  delay(500);
}

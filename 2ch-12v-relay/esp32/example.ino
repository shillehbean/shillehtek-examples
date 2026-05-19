// ESP32 (Arduino framework) example that configures GPIO5 and GPIO18 as outputs, keeps them HIGH to start OFF, and alternately toggles each relay with active-LOW control.
//
// Buy this module: https://shillehtek.com/products/2-channel-12v-relay-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/2-channel-12v-relay-module-manual
// More examples: https://github.com/shillehtek/examples
//

// 2-Channel 12V Relay Module - ESP32 Arduino Example
// IN pins: GPIO 5, 18
// Active LOW logic.

void setup() {
  Serial.begin(115200);
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);  // start OFF
  pinMode(18, OUTPUT);
  digitalWrite(18, HIGH);  // start OFF
}

void loop() {
  digitalWrite(5, LOW);   // Relay 1 ON
  delay(500);
  digitalWrite(5, HIGH);  // Relay 1 OFF
  delay(500);
  digitalWrite(18, LOW);   // Relay 2 ON
  delay(500);
  digitalWrite(18, HIGH);  // Relay 2 OFF
  delay(500);
}

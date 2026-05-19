// Shows how to control the four relays from an ESP32 (active LOW) by toggling GPIO 5, 18, 19, and 21 on and off in sequence with 500 ms delays.
//
// Buy this module: https://shillehtek.com/products/4-channel-5v-relay-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4-channel-5v-relay-module-manual
// More examples: https://github.com/shillehtek/examples
//

// 4-Channel 5V Relay Module - ESP32 Arduino Example
// IN pins: GPIO 5, 18, 19, 21
// Active LOW logic.

void setup() {
  Serial.begin(115200);
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);  // start OFF
  pinMode(18, OUTPUT);
  digitalWrite(18, HIGH);  // start OFF
  pinMode(19, OUTPUT);
  digitalWrite(19, HIGH);  // start OFF
  pinMode(21, OUTPUT);
  digitalWrite(21, HIGH);  // start OFF
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
  digitalWrite(19, LOW);   // Relay 3 ON
  delay(500);
  digitalWrite(19, HIGH);  // Relay 3 OFF
  delay(500);
  digitalWrite(21, LOW);   // Relay 4 ON
  delay(500);
  digitalWrite(21, HIGH);  // Relay 4 OFF
  delay(500);
}

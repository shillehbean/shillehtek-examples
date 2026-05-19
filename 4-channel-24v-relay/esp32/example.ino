// ESP32 Arduino example that initializes GPIOs 5, 18, 19, 21 as outputs for active-low relays and cycles each relay with 500 ms delays.
//
// Buy this module: https://shillehtek.com/products/4-channel-24v-relay-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4-channel-24v-relay-module-manual
// More examples: https://github.com/shillehtek/examples
//

// 4-Channel 24V Relay Module - ESP32 Arduino Example
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

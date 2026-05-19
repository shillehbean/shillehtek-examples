// Configures ESP32 GPIOs 5, 18, 19, 21, 22, 23, 25, 26 as outputs (active LOW) and cycles each relay on for 500 ms then off in sequence.
//
// Buy this module: https://shillehtek.com/products/8-channel-12v-relay-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/8-channel-12v-relay-module-manual
// More examples: https://github.com/shillehtek/examples
//

// 8-Channel 12V Relay Module - ESP32 Arduino Example
// IN pins: GPIO 5, 18, 19, 21, 22, 23, 25, 26
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
  pinMode(22, OUTPUT);
  digitalWrite(22, HIGH);  // start OFF
  pinMode(23, OUTPUT);
  digitalWrite(23, HIGH);  // start OFF
  pinMode(25, OUTPUT);
  digitalWrite(25, HIGH);  // start OFF
  pinMode(26, OUTPUT);
  digitalWrite(26, HIGH);  // start OFF
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
  digitalWrite(22, LOW);   // Relay 5 ON
  delay(500);
  digitalWrite(22, HIGH);  // Relay 5 OFF
  delay(500);
  digitalWrite(23, LOW);   // Relay 6 ON
  delay(500);
  digitalWrite(23, HIGH);  // Relay 6 OFF
  delay(500);
  digitalWrite(25, LOW);   // Relay 7 ON
  delay(500);
  digitalWrite(25, HIGH);  // Relay 7 OFF
  delay(500);
  digitalWrite(26, LOW);   // Relay 8 ON
  delay(500);
  digitalWrite(26, HIGH);  // Relay 8 OFF
  delay(500);
}

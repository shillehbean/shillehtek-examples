// Arduino example that initializes IN pins HIGH so the relays start OFF and then cycles each relay on/off using active-LOW signals.
//
// Buy this module: https://shillehtek.com/products/2-channel-12v-relay-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/2-channel-12v-relay-module-manual
// More examples: https://github.com/shillehtek/examples
//

// 2-Channel 12V Relay Module - Arduino Example
// Active LOW: digitalWrite(pin, LOW) energizes the relay.
// IN pins: 7, 8

void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);  // start with relay OFF
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);  // start with relay OFF
}

void loop() {
  // Cycle through each relay one by one
  digitalWrite(7, LOW);   // Relay 1 ON
  delay(500);
  digitalWrite(7, HIGH);  // Relay 1 OFF
  delay(500);
  digitalWrite(8, LOW);   // Relay 2 ON
  delay(500);
  digitalWrite(8, HIGH);  // Relay 2 OFF
  delay(500);
}

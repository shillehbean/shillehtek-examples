// Demonstrates toggling relays connected to digital pins 7 and 8 on an Arduino using active-LOW logic to cycle each relay on and off.
//
// Buy this module: https://shillehtek.com/products/2-channel-24v-relay-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/2-channel-24v-relay-module-manual
// More examples: https://github.com/shillehtek/examples
//

// 2-Channel 24V Relay Module - Arduino Example
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

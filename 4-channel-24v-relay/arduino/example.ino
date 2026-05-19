// Arduino sketch that configures pins 7, 8, 9, 10 as outputs for active-low relay inputs and cycles each relay on for 500 ms then off.
//
// Buy this module: https://shillehtek.com/products/4-channel-24v-relay-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4-channel-24v-relay-module-manual
// More examples: https://github.com/shillehtek/examples
//

// 4-Channel 24V Relay Module - Arduino Example
// Active LOW: digitalWrite(pin, LOW) energizes the relay.
// IN pins: 7, 8, 9, 10

void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);  // start with relay OFF
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);  // start with relay OFF
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);  // start with relay OFF
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);  // start with relay OFF
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
  digitalWrite(9, LOW);   // Relay 3 ON
  delay(500);
  digitalWrite(9, HIGH);  // Relay 3 OFF
  delay(500);
  digitalWrite(10, LOW);   // Relay 4 ON
  delay(500);
  digitalWrite(10, HIGH);  // Relay 4 OFF
  delay(500);
}

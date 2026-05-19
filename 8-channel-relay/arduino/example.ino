// Initializes eight Arduino digital pins as outputs (active-LOW) and cycles each relay on and off in sequence with 500ms delays.
//
// Buy this module: https://shillehtek.com/products/8-channel-5v-relay-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/8-channel-5v-relay-module-manual
// More examples: https://github.com/shillehtek/examples
//

// 8-Channel 5V Relay Module - Arduino Example
// Active LOW: digitalWrite(pin, LOW) energizes the relay.
// IN pins: 7, 8, 9, 10, 11, 12, 13, 14

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
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);  // start with relay OFF
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);  // start with relay OFF
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);  // start with relay OFF
  pinMode(14, OUTPUT);
  digitalWrite(14, HIGH);  // start with relay OFF
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
  digitalWrite(11, LOW);   // Relay 5 ON
  delay(500);
  digitalWrite(11, HIGH);  // Relay 5 OFF
  delay(500);
  digitalWrite(12, LOW);   // Relay 6 ON
  delay(500);
  digitalWrite(12, HIGH);  // Relay 6 OFF
  delay(500);
  digitalWrite(13, LOW);   // Relay 7 ON
  delay(500);
  digitalWrite(13, HIGH);  // Relay 7 OFF
  delay(500);
  digitalWrite(14, LOW);   // Relay 8 ON
  delay(500);
  digitalWrite(14, HIGH);  // Relay 8 OFF
  delay(500);
}

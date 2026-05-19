// Arduino sketch that toggles the relay on digital pin 7 (active LOW), initializing the pin HIGH to keep the relay off during boot and switching it every 2 seconds.
//
// Buy this module: https://shillehtek.com/products/1-channel-5v-relay-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/1-channel-5v-relay-module-manual
// More examples: https://github.com/shillehtek/examples
//

// 1-Channel 5V Relay Module - Arduino Example
// IN pin: Digital 7 (active LOW - LOW closes the relay)

const int RELAY_PIN = 7;

void setup() {
  // Set HIGH first so the relay does not click ON at boot
  digitalWrite(RELAY_PIN, HIGH);
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Relay ready");
}

void loop() {
  // Turn the load ON for 2 seconds
  Serial.println("Relay ON");
  digitalWrite(RELAY_PIN, LOW);   // active LOW
  delay(2000);

  // Turn the load OFF for 2 seconds
  Serial.println("Relay OFF");
  digitalWrite(RELAY_PIN, HIGH);
  delay(2000);
}

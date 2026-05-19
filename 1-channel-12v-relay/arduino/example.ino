// Arduino sketch that toggles the relay on digital pin 7 (active LOW) every 2 seconds and prints status to Serial.
//
// Buy this module: https://shillehtek.com/products/1-channel-12v-relay-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/1-channel-12v-relay-module-manual
// More examples: https://github.com/shillehtek/examples
//

// 1-Channel 12V Relay Module - Arduino Example
// IN pin: Digital 7 (active LOW - LOW closes the relay)
// VCC powered from external 12V supply, GND shared with Arduino

const int RELAY_PIN = 7;

void setup() {
  // Set HIGH first so the relay does not click ON at boot
  digitalWrite(RELAY_PIN, HIGH);
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("12V relay ready");
}

void loop() {
  Serial.println("Relay ON");
  digitalWrite(RELAY_PIN, LOW);   // active LOW
  delay(2000);

  Serial.println("Relay OFF");
  digitalWrite(RELAY_PIN, HIGH);
  delay(2000);
}

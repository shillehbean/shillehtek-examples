// Arduino sketch that keeps the relay off at boot, then toggles the relay (active LOW on digital pin 7) every 2 seconds while printing status over Serial.
//
// Buy this module: https://shillehtek.com/products/1-channel-24v-relay-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/1-channel-24v-relay-module-manual
// More examples: https://github.com/shillehtek/examples
//

// 1-Channel 24V Relay Module - Arduino Example
// IN pin: Digital 7 (active LOW - LOW closes the relay)
// VCC powered from external 24V supply, GND shared with Arduino

const int RELAY_PIN = 7;

void setup() {
  // Set HIGH first so the relay does not click ON at boot
  digitalWrite(RELAY_PIN, HIGH);
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("24V relay ready");
}

void loop() {
  Serial.println("Relay ON");
  digitalWrite(RELAY_PIN, LOW);   // active LOW
  delay(2000);

  Serial.println("Relay OFF");
  digitalWrite(RELAY_PIN, HIGH);
  delay(2000);
}

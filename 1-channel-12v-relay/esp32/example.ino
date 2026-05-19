// ESP32 sketch that toggles the relay on GPIO23 (active LOW) every 2 seconds and logs on/off messages over Serial.
//
// Buy this module: https://shillehtek.com/products/1-channel-12v-relay-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/1-channel-12v-relay-module-manual
// More examples: https://github.com/shillehtek/examples
//

// 1-Channel 12V Relay Module - ESP32 Example
// IN pin: GPIO 23 (active LOW)
// VCC powered from external 12V supply, GND shared with ESP32

const int RELAY_PIN = 23;

void setup() {
  digitalWrite(RELAY_PIN, HIGH); // keep relay off through boot
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  Serial.println("ON");
  digitalWrite(RELAY_PIN, LOW);
  delay(2000);

  Serial.println("OFF");
  digitalWrite(RELAY_PIN, HIGH);
  delay(2000);
}

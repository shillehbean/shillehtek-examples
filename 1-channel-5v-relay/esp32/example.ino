// ESP32 Arduino-style example that controls the relay on GPIO23 (active LOW), keeping the relay off through boot and toggling it every 2 seconds.
//
// Buy this module: https://shillehtek.com/products/1-channel-5v-relay-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/1-channel-5v-relay-module-manual
// More examples: https://github.com/shillehtek/examples
//

// 1-Channel 5V Relay Module - ESP32 Example
// IN pin: GPIO 23 (active LOW)

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

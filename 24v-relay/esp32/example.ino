// ESP32 example that configures GPIO23 as an output, holds the relay off through boot, and alternately drives it LOW/HIGH every 2 seconds with status printed to Serial.
//
// Buy this module: https://shillehtek.com/products/1-channel-24v-relay-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/1-channel-24v-relay-module-manual
// More examples: https://github.com/shillehtek/examples
//

// 1-Channel 24V Relay Module - ESP32 Example
// IN pin: GPIO 23 (active LOW)
// VCC powered from external 24V supply, GND shared with ESP32

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

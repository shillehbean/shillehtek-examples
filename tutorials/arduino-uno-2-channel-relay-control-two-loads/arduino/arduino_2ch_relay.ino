// Arduino sketch to control a 2-channel relay module: toggles two relays in sequence and includes helper functions plus ACTIVE_LOW support and safe startup.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-2-channel-relay-control-two-loads
// Parts used: https://shillehtek.com/products/2-channel-5v-relay-module
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#define RELAY1_PIN 7  // D7 -> IN1
#define RELAY2_PIN 6  // D6 -> IN2

// Many relay modules are ACTIVE LOW:
// LOW = ON, HIGH = OFF
const bool ACTIVE_LOW = true;

void relayOn(int pin) {
  digitalWrite(pin, ACTIVE_LOW ? LOW : HIGH);
}

void relayOff(int pin) {
  digitalWrite(pin, ACTIVE_LOW ? HIGH : LOW);
}

void setup() {
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);

  // Safe startup: both OFF
  relayOff(RELAY1_PIN);
  relayOff(RELAY2_PIN);
}

void loop() {
  // Relay 1 ON, Relay 2 OFF
  relayOn(RELAY1_PIN);
  relayOff(RELAY2_PIN);
  delay(1000);

  // Relay 1 OFF, Relay 2 ON
  relayOff(RELAY1_PIN);
  relayOn(RELAY2_PIN);
  delay(1000);

  // Both ON
  relayOn(RELAY1_PIN);
  relayOn(RELAY2_PIN);
  delay(1000);

  // Both OFF
  relayOff(RELAY1_PIN);
  relayOff(RELAY2_PIN);
  delay(1000);
}

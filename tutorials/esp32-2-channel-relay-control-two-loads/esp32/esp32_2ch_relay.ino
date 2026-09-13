// Controls two relays connected to GPIO25 and GPIO26 (active-low), providing a safe startup state and cycling through several relay on/off combinations.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-2-channel-relay-control-two-loads
// Parts used: https://shillehtek.com/products/2-channel-5v-relay-module
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#define RELAY1_PIN 25  // GPIO 25 -> IN1
#define RELAY2_PIN 26  // GPIO 26 -> IN2

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

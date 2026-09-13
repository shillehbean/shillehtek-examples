// Arduino sketch that monitors the RCWL-0516 output on D2 and drives an active-LOW relay on D7, keeping the relay on for 30 seconds after the last detected motion.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-rcwl-0516-through-wall-motion
// Parts used: https://shillehtek.com/products/rcwl-0516-microwave-doppler-radar-motion-sensor-module
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/1-channel-5v-relay-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int RADAR = 2;
const int RELAY = 7;
unsigned long lastTrigger = 0;
const unsigned long HOLD_MS = 30000;  // keep light on for 30s

void setup() {
  pinMode(RADAR, INPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);   // active LOW
}

void loop() {
  if (digitalRead(RADAR) == HIGH) {
    lastTrigger = millis();
    digitalWrite(RELAY, LOW);  // light on
  } else if (millis() - lastTrigger > HOLD_MS) {
    digitalWrite(RELAY, HIGH); // light off after timeout
  }
}

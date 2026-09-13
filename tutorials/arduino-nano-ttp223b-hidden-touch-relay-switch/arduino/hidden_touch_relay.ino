// Arduino sketch that reads the TTP223B touch sensor and toggles a 5V relay (active LOW) on each touch, with a simple debounce.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ttp223b-hidden-touch-relay-switch
// Parts used: https://shillehtek.com/products/digital-sensor-ttp223b-module-capacitive-touch-switch
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/1-channel-5v-relay-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int TOUCH = 2;
const int RELAY = 7;
bool state = false;
bool last = LOW;

void setup() {
  pinMode(TOUCH, INPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);   // active LOW: HIGH = off
}

void loop() {
  bool now = digitalRead(TOUCH);
  if (now == HIGH && last == LOW) {   // rising edge = new touch
    state = !state;
    digitalWrite(RELAY, state ? LOW : HIGH);
    delay(200);   // simple debounce
  }
  last = now;
}

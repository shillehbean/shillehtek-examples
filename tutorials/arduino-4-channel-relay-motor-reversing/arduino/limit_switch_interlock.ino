// Arduino snippet that configures two limit switches using INPUT_PULLUP and triggers brake() when either limit is reached as a safety interlock.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-4-channel-relay-motor-reversing
// Parts used: https://shillehtek.com/products/4-channel-12v-relay-module
//             https://shillehtek.com/products/4-channel-5v-relay-module
//             https://shillehtek.com/products/shillehtek-l298n-motor-driver-controller-board
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int LIMIT_FWD = 6;
const int LIMIT_REV = 7;

void setup() {
  pinMode(LIMIT_FWD, INPUT_PULLUP);
  pinMode(LIMIT_REV, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(LIMIT_FWD) == LOW) brake();
  if (digitalRead(LIMIT_REV) == LOW) brake();
  // ... rest of motion logic ...
}

// Arduino sketch that drives four active-LOW relay outputs to control motor direction (forward, reverse), implement a brake state, and demonstrate a timed forward/reverse cycle with dead-time between switching.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-4-channel-relay-motor-reversing
// Parts used: https://shillehtek.com/products/4-channel-12v-relay-module
//             https://shillehtek.com/products/4-channel-5v-relay-module
//             https://shillehtek.com/products/shillehtek-l298n-motor-driver-controller-board
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int RELAYS[4] = {2, 3, 4, 5};   // REL1..REL4

void allOff() {
  for (int r : RELAYS) digitalWrite(r, HIGH);   // active LOW
}
void forward() {
  allOff(); delay(50);                          // dead-time
  digitalWrite(RELAYS[0], LOW);                 // REL1
  digitalWrite(RELAYS[3], LOW);                 // REL4
}
void reverse() {
  allOff(); delay(50);
  digitalWrite(RELAYS[1], LOW);                 // REL2
  digitalWrite(RELAYS[2], LOW);                 // REL3
}
void brake() {
  allOff(); delay(50);
  digitalWrite(RELAYS[0], LOW);                 // REL1
  digitalWrite(RELAYS[2], LOW);                 // REL3 (high side together)
}

void setup() {
  for (int r : RELAYS) {
    pinMode(r, OUTPUT);
    digitalWrite(r, HIGH);
  }
}
void loop() {
  forward();  delay(5000);
  brake();    delay(500);
  reverse();  delay(5000);
  brake();    delay(500);
}

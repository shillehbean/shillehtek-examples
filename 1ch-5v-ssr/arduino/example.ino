// Arduino sketch that ensures the control pin is HIGH (SSR off) at startup, then toggles the active-low SSR on (LOW) and off (HIGH) every 3 seconds on digital pin 7.
//
// Buy this module: https://shillehtek.com/products/solid-state-relay-1ch-5v-active-low
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/solid-state-relay-1ch-5v-active-low-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int CH = 7;

void setup() {
  digitalWrite(CH, HIGH);   // define OFF state before...
  pinMode(CH, OUTPUT);      // ...the pin becomes an output
}

void loop() {
  digitalWrite(CH, LOW);    // load ON
  delay(3000);
  digitalWrite(CH, HIGH);   // load OFF
  delay(3000);
}

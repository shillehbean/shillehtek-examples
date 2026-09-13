// Arduino snippets showing wiring and control for an active‑LOW 5V relay and for an NPN transistor (including PWM) using digital pin 7.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-relay-mosfet-choose-right-switch
// Parts used: https://shillehtek.com/products/1-channel-5v-relay-module
//             https://shillehtek.com/products/2-channel-5v-relay-module
//             https://shillehtek.com/products/4-channel-5v-relay-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// RELAY (active-LOW module, 5V coil)
//   Arduino 5V -> Relay VCC
//   Arduino GND -> Relay GND
//   Arduino D7  -> Relay IN
//   Load wired to COM + NO terminals
pinMode(7, OUTPUT);
digitalWrite(7, LOW);   // relay engaged
digitalWrite(7, HIGH);  // relay released

// NPN TRANSISTOR (2N2222 / 2N3904)
//   Arduino D7 -> 1k ohm -> BASE
//   Load+ -> +supply
//   Load- -> COLLECTOR
//   EMITTER -> GND
pinMode(7, OUTPUT);
digitalWrite(7, HIGH);  // load on
analogWrite(7, 128);    // PWM, ~50% brightness

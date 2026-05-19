// Pulses four Arduino digital pins (D2–D5) in sequence to trigger the relay inputs with a 100 ms pulse per channel and a 2 second delay between channels.
//
// Buy this module: https://shillehtek.com/products/4-channel-relay-module-programmable-delay-6-24v
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4-channel-relay-module-programmable-delay-6-24v-manual
// More examples: https://github.com/shillehtek/examples
//

// 4-Channel programmable relay - fire each input in sequence
// Wire IN1-IN4 to D2-D5, share GND with the module

const int triggers[4] = {2, 3, 4, 5};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(triggers[i], OUTPUT);
    digitalWrite(triggers[i], LOW);
  }
}

void pulseTrigger(int pin) {
  digitalWrite(pin, HIGH);
  delay(100);                  // 100 ms pulse fires the channel
  digitalWrite(pin, LOW);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    pulseTrigger(triggers[i]);
    delay(2000);               // wait between channels
  }
}

// Sequentially turns each of the four SSR channels on for 1 second then off, using Arduino digital pins 4–7.
//
// Buy this module: https://shillehtek.com/products/4-channel-5v-ssr-module-arduino-esp32-raspberry
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4-channel-5v-ssr-module-arduino-esp32-raspberry-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int CH[4] = {4, 5, 6, 7};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(CH[i], OUTPUT);
    digitalWrite(CH[i], LOW);   // all off at boot
  }
}

void loop() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(CH[i], HIGH);  // ON
    delay(1000);
    digitalWrite(CH[i], LOW);   // OFF
  }
}

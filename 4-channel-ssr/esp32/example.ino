// Runs on an ESP32: toggles channel 1 and channel 2 in opposite phases on a 10-second cycle and prints their states over serial.
//
// Buy this module: https://shillehtek.com/products/4-channel-5v-ssr-module-arduino-esp32-raspberry
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4-channel-5v-ssr-module-arduino-esp32-raspberry-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int CH[4] = {25, 26, 27, 33};

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 4; i++) {
    pinMode(CH[i], OUTPUT);
    digitalWrite(CH[i], LOW);
  }
}

void loop() {
  // channel 1 on a 10 s cycle, channel 2 opposite phase
  bool phase = (millis() / 10000) % 2;
  digitalWrite(CH[0], phase);
  digitalWrite(CH[1], !phase);
  Serial.printf("CH1=%d CH2=%d\n", phase, !phase);
  delay(500);
}

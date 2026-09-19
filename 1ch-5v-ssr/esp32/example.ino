// ESP32 (Arduino core) sketch that reads serial input and turns the SSR on when it receives '1' (pulls GPIO26 LOW) and off when it receives '0' (sets GPIO26 HIGH).
//
// Buy this module: https://shillehtek.com/products/solid-state-relay-1ch-5v-active-low
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/solid-state-relay-1ch-5v-active-low-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int CH = 26;

void setup() {
  Serial.begin(115200);
  digitalWrite(CH, HIGH);
  pinMode(CH, OUTPUT);
  Serial.println("Send 1 = ON, 0 = OFF");
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == '1') { digitalWrite(CH, LOW);  Serial.println("ON");  }
    if (c == '0') { digitalWrite(CH, HIGH); Serial.println("OFF"); }
  }
}

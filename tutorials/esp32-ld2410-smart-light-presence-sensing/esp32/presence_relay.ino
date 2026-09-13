// ESP32 Arduino sketch that reads the LD2410 presence output and controls a relay, while printing presence state to Serial.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-ld2410-smart-light-presence-sensing
// Parts used: https://shillehtek.com/products/hlk-ld2450-24ghz-mmwave-radar-human-body-tracking-sensor-module
//             https://shillehtek.com/products/hlk-2410c-human-presence-radar-motion-detection-module-pre-soldered
//             https://shillehtek.com/products/hlk-2410b-human-presence-radar-motion-detection-module-pre-soldered
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int LD2410_OUT = 4;
const int RELAY = 5;
void setup() {
  pinMode(LD2410_OUT, INPUT);
  pinMode(RELAY, OUTPUT);
  Serial.begin(115200);
}
void loop() {
  bool present = digitalRead(LD2410_OUT);
  digitalWrite(RELAY, present ? HIGH : LOW);
  Serial.println(present ? "HUMAN" : "empty");
  delay(200);
}

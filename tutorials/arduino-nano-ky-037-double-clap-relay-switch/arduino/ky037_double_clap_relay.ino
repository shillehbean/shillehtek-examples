// Arduino sketch that reads a KY-037 sound sensor and toggles a relay on a detected double-clap using simple debounce and timing logic.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ky-037-double-clap-relay-switch
// Parts used: https://shillehtek.com/products/shillehtek-ky-037-sound-sensor-module
//             https://shillehtek.com/products/1-channel-5v-relay-module
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int MIC = 2;
const int RELAY = 3;
bool relayOn = false;
unsigned long lastClap = 0;
int clapCount = 0;

void setup() {
  pinMode(MIC, INPUT);
  pinMode(RELAY, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(MIC) == HIGH) {
    unsigned long now = millis();
    if (now - lastClap < 80) return;   // debounce
    if (now - lastClap < 1000) {
      clapCount++;
    } else {
      clapCount = 1;
    }
    lastClap = now;
    if (clapCount == 2) {
      relayOn = !relayOn;
      digitalWrite(RELAY, relayOn ? HIGH : LOW);
      Serial.println(relayOn ? "ON" : "OFF");
      clapCount = 0;
    }
  }
}

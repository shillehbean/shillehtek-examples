// Plays a short startup melody using Arduino tone() on digital pin D9 to drive the PAM8406 input (through the recommended series resistor/coupling).
//
// Buy this module: https://shillehtek.com/products/pam8406-stereo-class-d-amplifier-module-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pam8406-stereo-class-d-amplifier-module-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// PAM8406 Amplifier - Arduino Example (tone melody)
// D9 -> 1k -> INL, INL -> 100nF -> GND, speaker across +L/-L

const int audioPin = 9;

// Simple startup jingle: note frequency (Hz) and duration (ms)
const int melody[][2] = {
  {262, 200}, {330, 200}, {392, 200}, {523, 400},
  {392, 200}, {523, 600},
};

void setup() {
  Serial.begin(9600);
  Serial.println("Playing jingle on PAM8406...");
}

void loop() {
  for (unsigned int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    tone(audioPin, melody[i][0]);
    delay(melody[i][1]);
    noTone(audioPin);
    delay(30);
  }
  delay(2000);
}

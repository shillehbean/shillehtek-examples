// Arduino sketch that plays an 8-note C major scale on PWM pin D9 as a tone test; intended to feed an external amplifier (do not drive the speaker directly).
//
// Buy this module: https://shillehtek.com/products/mini-speaker-4ohm-3w-square-150mm-dupont-lead
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mini-speaker-4ohm-3w-square-150mm-dupont-lead-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Speaker tone test - Arduino Uno / Nano
// D9 -> 1k resistor -> amplifier INPUT (never straight to the speaker)
// Amplifier output + / - -> speaker red / black

const int AUDIO_PIN = 9;
const int NOTES[] = {262, 294, 330, 349, 392, 440, 494, 523};  // C4 to C5

void setup() {
  Serial.begin(9600);
  Serial.println("Playing test scale...");
}

void loop() {
  for (int i = 0; i < 8; i++) {
    tone(AUDIO_PIN, NOTES[i], 250);   // 250 ms per note
    delay(300);
  }
  noTone(AUDIO_PIN);
  delay(2000);                        // pause, then repeat
}

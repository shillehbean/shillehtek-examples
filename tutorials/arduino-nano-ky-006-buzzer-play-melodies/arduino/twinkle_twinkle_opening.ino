// Plays the opening phrase of "Twinkle Twinkle" by iterating arrays of note frequencies and durations, using tone(), delay(), and noTone() on pin 8.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ky-006-buzzer-play-melodies
// Parts used: https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int BUZZER = 8;

// Notes (Hz) and durations (ms) for the opening of "Twinkle Twinkle"
const int notes[]    = {262, 262, 392, 392, 440, 440, 392};
const int durations[] = {400, 400, 400, 400, 400, 400, 800};

void setup() {
  for (int i = 0; i < 7; i++) {
    tone(BUZZER, notes[i], durations[i]);
    delay(durations[i] + 50);   // gap between notes
    noTone(BUZZER);
  }
}

void loop() {}

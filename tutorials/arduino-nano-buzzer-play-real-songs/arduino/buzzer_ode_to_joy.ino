// Plays the first phrase of "Ode to Joy" on a passive piezo buzzer using tone(), note and duration arrays, and tempo-based timing.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-buzzer-play-real-songs
// Parts used: https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392

const int BUZZER = 9;
const int TEMPO  = 120;                      // beats per minute

// Ode to Joy, first phrase: {note, type} (4 = quarter, 8 = eighth)
int melody[]    = { NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4,
                    NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
                    NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4,
                    NOTE_E4, NOTE_D4, NOTE_D4 };
int durations[] = { 4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4,  4, 8, 2 };

void setup() {
  int wholenote = (60000 * 4) / TEMPO;

  for (unsigned i = 0; i < sizeof(melody) / sizeof(int); i++) {
    int noteMs = wholenote / durations[i];
    tone(BUZZER, melody[i], noteMs * 0.9);   // play 90% of the slot
    delay(noteMs);                           // 10% silence separates notes
    noTone(BUZZER);
  }
}

void loop() {}   // plays once on boot / reset

// Plays a short melody by sending specific note frequencies and durations to the buzzer using tone() in setup().
//
// Buy this module: https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects-manual
// More examples: https://github.com/shillehtek/examples
//

// KY-006 - Play a simple melody using note frequencies

const int buzzerPin = 8;

// Note frequencies in Hz
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_G5  784

int melody[]   = {NOTE_E5, NOTE_D5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_E5, NOTE_E5};
int durations[] = {300, 300, 300, 300, 300, 300, 600};

void setup() {
  pinMode(buzzerPin, OUTPUT);
  for (int i = 0; i < 7; i++) {
    tone(buzzerPin, melody[i], durations[i]);
    delay(durations[i] + 50);
  }
  noTone(buzzerPin);
}

void loop() {}

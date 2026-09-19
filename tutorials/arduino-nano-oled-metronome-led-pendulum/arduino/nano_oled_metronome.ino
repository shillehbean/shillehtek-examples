// Arduino sketch that implements an LED pendulum metronome: reads a potentiometer for BPM, updates eight LEDs as a pendulum, sounds a buzzer on the beat, and displays BPM and tempo markings on an SSD1306 I2C OLED.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-oled-metronome-led-pendulum
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

const int LED[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const int POT = A0, BUZZ = 11;
const int BEATS_PER_BAR = 4;

int pos = 0, dir = 1, beat = 0, bpm = 120;
unsigned long nextStep = 0;

const char* marking(int b) {
  if (b < 60)  return "Largo";
  if (b < 76)  return "Adagio";
  if (b < 108) return "Andante";
  if (b < 120) return "Moderato";
  if (b < 156) return "Allegro";
  if (b < 176) return "Vivace";
  return "Presto";
}

void showBpm() {
  oled.clearDisplay();
  oled.setTextSize(3); oled.setCursor(10, 8);  oled.print(bpm);
  oled.setTextSize(2); oled.setCursor(76, 14); oled.print("BPM");
  oled.setTextSize(1); oled.setCursor(10, 44); oled.print(marking(bpm));
  oled.setCursor(10, 54); oled.print("4/4   beat "); oled.print(beat + 1);
  oled.display();
}

int readBpm() {                                   // averaged, so the number doesn't jitter
  long s = 0; for (int i = 0; i < 8; i++) s += analogRead(POT);
  return map(s / 8, 0, 1023, 40, 208);
}

void setup() {
  for (int i = 0; i < 8; i++) pinMode(LED[i], OUTPUT);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(SSD1306_WHITE);
  digitalWrite(LED[0], HIGH);
  showBpm();
  nextStep = millis();
}

void loop() {
  int b = readBpm();
  if (abs(b - bpm) >= 2) { bpm = b; showBpm(); }  // small dead band = no flicker

  unsigned long stepMs = 60000UL / bpm / 7;       // one beat = 7 steps, end to end
  if ((long)(millis() - nextStep) >= 0) {
    nextStep += stepMs;                           // schedule from the last due time: no drift
    digitalWrite(LED[pos], LOW);
    pos += dir;
    digitalWrite(LED[pos], HIGH);
    if (pos == 0 || pos == 7) {                   // an end of the swing = a beat
      dir = -dir;
      tone(BUZZ, beat == 0 ? 1500 : 1000, 30);    // higher click on beat 1
      beat = (beat + 1) % BEATS_PER_BAR;
      showBpm();
    }
  }
}

// Arduino sketch for a 2-player reaction timer using an 8x8 WS2812 matrix, start and player buttons, and a buzzer; it handles idle/ready/GO cues, false-start detection, and increments player scores.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ws2812-matrix-reaction-timer
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/ws2812-8x8-led-matrix-arduino-esp32-raspberry-pi
//             https://shillehtek.com/products/200pcs-6mm-light-touch-button-switch-kit-plastic-box-4-3-5-6-7-8-9-10-12-14-16mm
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel matrix(64, 6, NEO_GRB + NEO_KHZ800);

const int START = 7, P1 = 8, P2 = 9, BUZZ = 10;
int score1 = 0, score2 = 0;

void fill(uint32_t c) { matrix.fill(c); matrix.show(); }

void setup() {
  matrix.begin();
  matrix.setBrightness(40);
  pinMode(START, INPUT_PULLUP);
  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  randomSeed(analogRead(A0));
  fill(matrix.Color(0, 0, 30));            // idle blue
}

void loop() {
  if (digitalRead(START) == HIGH) return;  // wait for start press

  fill(matrix.Color(30, 30, 0));           // yellow: get ready
  unsigned long wait = random(1000, 5000);
  unsigned long t0 = millis();

  while (millis() - t0 < wait) {           // false-start watch
    if (digitalRead(P1) == LOW || digitalRead(P2) == LOW) {
      tone(BUZZ, 110, 600);                // raspberry for jumping the gun
      fill(matrix.Color(30, 0, 30));
      delay(1200);
      return;
    }
  }

  fill(matrix.Color(0, 40, 0));            // GREEN: GO!
  tone(BUZZ, 1500, 120);
  unsigned long go = millis();

  while (true) {
    if (digitalRead(P1) == LOW) { score1++; break; }
    if (digitalRead(P2) == LOW) { score2++; break; }
  }
  unsigned long reaction = millis() - go;  // winner's time in ms

  // winner's color flash + show scores as lit rows
  fill(score1 > score2 ? matrix.Color(40, 0, 0) : matrix.Color(0, 0, 40));
  delay(1500);
  fill(matrix.Color(0, 0, 30));
}

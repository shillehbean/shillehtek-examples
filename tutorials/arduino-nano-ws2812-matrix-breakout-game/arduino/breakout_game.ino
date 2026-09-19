// Arduino sketch implementing a Breakout-style game using FastLED on an 8x8 WS2812 matrix with two-button input, buzzer sound, brick/paddle/ball logic, and drawing routines.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ws2812-matrix-breakout-game
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/ws2812-8x8-led-matrix-arduino-esp32-raspberry-pi
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <FastLED.h>
#define DATA_PIN 6
#define BTN_L 9
#define BTN_R 10
#define BUZZ  3
CRGB leds[64];

bool brick[3][8]; int bricksLeft;
int px, bx, by, dx, dy, lives;
unsigned long tickMs, lastTick = 0, lastMove = 0;

uint16_t XY(uint8_t x, uint8_t y) { return (y & 1) ? y * 8 + (7 - x) : y * 8 + x; }   // serpentine
void beep(int f, int ms) { tone(BUZZ, f, ms); }

void resetBall() { bx = px + 1; by = 6; dx = random(2) ? 1 : -1; dy = -1; }
void newGame() {
  for (int y = 0; y < 3; y++) for (int x = 0; x < 8; x++) brick[y][x] = true;
  bricksLeft = 24; px = 2; lives = 3; tickMs = 200; resetBall();
}

void draw() {
  FastLED.clear();
  const CRGB rowCol[3] = { CRGB::Red, CRGB::Orange, CRGB::Yellow };
  for (int y = 0; y < 3; y++) for (int x = 0; x < 8; x++) if (brick[y][x]) leds[XY(x, y)] = rowCol[y];
  for (int i = 0; i < 3; i++) leds[XY(px + i, 7)] = CRGB::Blue;
  leds[XY(bx, by)] = CRGB::White;
  FastLED.show();
}

void flash(CRGB c, int times) {
  for (int i = 0; i < times; i++) {
    fill_solid(leds, 64, c); FastLED.show(); delay(150);
    FastLED.clear(true); delay(150);
  }
}

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, 64);
  FastLED.setBrightness(40);
  pinMode(BTN_L, INPUT_PULLUP); pinMode(BTN_R, INPUT_PULLUP);
  randomSeed(analogRead(A0));
  newGame(); draw();
  while (digitalRead(BTN_L) && digitalRead(BTN_R)) {}      // press either button to start
}

void loop() {
  unsigned long now = millis();

  if (now - lastMove >= 70) {                              // paddle: one cell per 70 ms while held
    lastMove = now;
    if (!digitalRead(BTN_L) && px > 0) px--;
    if (!digitalRead(BTN_R) && px < 5) px++;
  }

  if (now - lastTick >= tickMs) {                          // ball: one cell per tick
    lastTick = now;
    int nx = bx + dx, ny = by + dy;
    if (nx < 0 || nx > 7) { dx = -dx; nx = bx + dx; beep(300, 20); }   // side walls
    if (ny < 0)           { dy = -dy; ny = by + dy; beep(300, 20); }   // ceiling
    if (ny <= 2 && brick[ny][nx]) {                                    // brick hit
      brick[ny][nx] = false; bricksLeft--; beep(900, 30);
      dy = -dy; ny = by + dy;
      if (tickMs > 90) tickMs -= 4;                                    // speed up
      if (bricksLeft == 0) { draw(); beep(1200, 400); flash(CRGB::Green, 4); newGame(); return; }
    }
    if (ny == 7) {                                                     // paddle row
      if (nx >= px && nx < px + 3) {
        dy = -1; ny = 6; beep(600, 20);
        if (nx == px) dx = -1; else if (nx == px + 2) dx = 1;          // paddle edges steer the ball
      } else {                                                         // missed
        lives--; beep(150, 300); flash(CRGB::Red, 1);
        if (lives == 0) { flash(CRGB::Red, 3); newGame(); }
        else resetBall();
        draw(); return;
      }
    }
    bx = nx; by = ny;
  }
  draw();
}

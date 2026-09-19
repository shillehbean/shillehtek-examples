// Arduino sketch that defines pins, LED matrix mapping, piece shapes and colors, and core variables for a Tetris game using FastLED on an 8x8 WS2812 matrix.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ws2812-matrix-tetris-game
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/ws2812-8x8-led-matrix-arduino-esp32-raspberry-pi
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <FastLED.h>
#define DATA_PIN 6
#define BTN_L   9
#define BTN_R   10
#define BTN_ROT 8
#define BUZZ    2
CRGB leds[64];
CRGB field[8][8];                              // locked blocks (black = empty)

// 7 pieces x 4 rotations x 4 cells; each cell is an index into a 4x4 box: row*4 + column
const uint8_t SHAPE[7][4][4] PROGMEM = {
  {{4,5,6,7},  {2,6,10,14}, {4,5,6,7},  {2,6,10,14}},   // I
  {{1,2,5,6},  {1,2,5,6},   {1,2,5,6},  {1,2,5,6}},     // O
  {{1,4,5,6},  {1,5,6,9},   {4,5,6,9},  {1,4,5,9}},     // T
  {{1,2,4,5},  {1,5,6,10},  {1,2,4,5},  {1,5,6,10}},    // S
  {{0,1,5,6},  {2,5,6,9},   {0,1,5,6},  {2,5,6,9}},     // Z
  {{0,4,5,6},  {1,2,5,9},   {4,5,6,10}, {1,5,8,9}},     // J
  {{2,4,5,6},  {1,5,9,10},  {4,5,6,8},  {0,1,5,9}}      // L
};
const CRGB COLOR[7] = {CRGB::Cyan, CRGB::Yellow, CRGB::Purple, CRGB::Green, CRGB::Red, CRGB::Blue, CRGB::OrangeRed};

int piece, rot, px, py;
unsigned int speedMs = 500;
unsigned long lastFall = 0, score = 0;

uint16_t XY(int x, int y) { return (y & 1) ? y * 8 + (7 - x) : y * 8 + x; }   // serpentine matrix
void beep(int f, int ms) { tone(BUZZ, f, ms); }
bool occupied(int x, int y) { return field[y][x].r | field[y][x].g | field[y][x].b; }

bool fits(int x, int y, int r) {                // can the piece sit at box position (x,y) in rotation r?
  for (int i = 0; i < 4; i++) {
    uint8_t c = pgm_read_byte(&SHAPE[piece][r][i]);
    int cx = x + (c & 3), cy = y + (c >> 2);
    if (cx < 0 || cx > 7 || cy > 7) return false;          // walls and floor
    if (cy >= 0 && occupied(cx, cy)) return false;          // locked blocks (cells above the top are fine)
  }
  return true;
}

void spawn() { piece = random(7); rot = 0; px = 2; py = -2; }

void gameOver() {
  for (int i = 0; i < 3; i++) {
    fill_solid(leds, 64, CRGB::Red); FastLED.show(); beep(200, 150); delay(200);
    FastLED.clear(true); delay(200);
  }
  memset(field, 0, sizeof field); score = 0; speedMs = 500;
  while (digitalRead(BTN_L) && digitalRead(BTN_R) && digitalRead(BTN_ROT)) {}   // any button restarts
  delay(300);
}

void clearLines() {
  int n = 0;
  for (int y = 7; y >= 0; y--) {
    bool full = true;
    for (int x = 0; x < 8; x++) if (!occupied(x, y)) { full = false; break; }
    if (!full) continue;
    n++;
    for (int x = 0; x < 8; x++) leds[XY(x, y)] = CRGB::White;      // flash the row
    FastLED.show(); delay(120);
    for (int yy = y; yy > 0; yy--) for (int x = 0; x < 8; x++) field[yy][x] = field[yy - 1][x];
    for (int x = 0; x < 8; x++) field[0][x] = CRGB::Black;
    y++;                                                            // re-check the row that dropped in
  }
  if (n) {
    score += (n == 1) ? 100 : 400 * (n - 1);                        // 100, 400, 800, 1200
    beep(1200, 80);
    if (speedMs > 150) speedMs -= 10 * n;                           // faster every line
    Serial.print("score "); Serial.println(score);
  }
}

void tick() {                                   // one gravity step
  if (fits(px, py + 1, rot)) { py++; return; }
  bool over = false;                            // can't fall: lock the piece
  for (int i = 0; i < 4; i++) {
    uint8_t c = pgm_read_byte(&SHAPE[piece][rot][i]);
    int cx = px + (c & 3), cy = py + (c >> 2);
    if (cy < 0) over = true; else field[cy][cx] = COLOR[piece];
  }
  beep(300, 20);
  if (over) gameOver(); else clearLines();
  spawn();
}

void handleButtons() {
  static unsigned long lastMove = 0; static bool rotWasDown = false;
  if (millis() - lastMove >= 120) {                                 // slide: one cell per 120 ms while held
    if (!digitalRead(BTN_L) && fits(px - 1, py, rot)) { px--; lastMove = millis(); }
    if (!digitalRead(BTN_R) && fits(px + 1, py, rot)) { px++; lastMove = millis(); }
  }
  bool rotDown = !digitalRead(BTN_ROT);
  if (rotDown && !rotWasDown) {                                    // rotate once per press
    int r = (rot + 1) % 4;
    if (fits(px, py, r))          { rot = r; beep(700, 15); }
    else if (fits(px - 1, py, r)) { px--; rot = r; beep(700, 15); }   // wall kick left
    else if (fits(px + 1, py, r)) { px++; rot = r; beep(700, 15); }   // wall kick right
  }
  rotWasDown = rotDown;
}

void draw() {
  for (int y = 0; y < 8; y++) for (int x = 0; x < 8; x++) leds[XY(x, y)] = field[y][x];
  for (int i = 0; i < 4; i++) {                                     // the falling piece on top
    uint8_t c = pgm_read_byte(&SHAPE[piece][rot][i]);
    int cx = px + (c & 3), cy = py + (c >> 2);
    if (cy >= 0) leds[XY(cx, cy)] = COLOR[piece];
  }
  FastLED.show();
}

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, 64);
  FastLED.setBrightness(40);
  pinMode(BTN_L, INPUT_PULLUP); pinMode(BTN_R, INPUT_PULLUP); pinMode(BTN_ROT, INPUT_PULLUP);
  randomSeed(analogRead(A0));
  spawn();
}

void loop() {
  handleButtons();
  if (millis() - lastFall >= speedMs) { lastFall = millis(); tick(); }
  draw();
}

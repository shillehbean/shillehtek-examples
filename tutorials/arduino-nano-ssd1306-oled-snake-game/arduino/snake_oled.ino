// Implements the Snake game: initializes the SSD1306 OLED, reads joystick input, manages snake movement, food placement, scoring, speed, and game over behavior with buzzer feedback.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ssd1306-oled-snake-game
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled(128, 64, &Wire, -1);
const int JOY_X = A0, JOY_Y = A1, BUZZ = 8;
const int COLS = 32, ROWS = 16, CELL = 4, MAX_LEN = 120;

int8_t sx[MAX_LEN], sy[MAX_LEN];    // snake cells, index 0 = head
int len, dirX, dirY, foodX, foodY, score;
unsigned long tick, speedMs;

void placeFood() {
  bool onSnake;
  do {
    foodX = random(COLS); foodY = random(ROWS); onSnake = false;
    for (int i = 0; i < len; i++) if (sx[i] == foodX && sy[i] == foodY) onSnake = true;
  } while (onSnake);
}

void newGame() {
  len = 3; dirX = 1; dirY = 0; score = 0; speedMs = 220;
  for (int i = 0; i < len; i++) { sx[i] = 10 - i; sy[i] = 8; }
  placeFood();
}

void gameOver() {
  tone(BUZZ, 200, 400);
  oled.clearDisplay(); oled.setTextSize(2); oled.setCursor(10, 14); oled.print("GAME OVER");
  oled.setTextSize(1); oled.setCursor(34, 44); oled.print("score "); oled.print(score);
  oled.display(); delay(2500); newGame();
}

void setup() {
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(SSD1306_WHITE);
  randomSeed(analogRead(A3));
  newGame();
}

void loop() {
  // read the stick constantly so quick flicks aren't missed; no reversing into yourself
  int x = analogRead(JOY_X), y = analogRead(JOY_Y);
  if (x < 300 && dirX == 0) { dirX = -1; dirY = 0; }
  if (x > 700 && dirX == 0) { dirX =  1; dirY = 0; }
  if (y < 300 && dirY == 0) { dirX = 0; dirY = -1; }
  if (y > 700 && dirY == 0) { dirX = 0; dirY =  1; }

  if (millis() - tick < speedMs) return;    // one game step per tick
  tick = millis();

  int nx = sx[0] + dirX, ny = sy[0] + dirY;
  if (nx < 0 || nx >= COLS || ny < 0 || ny >= ROWS) { gameOver(); return; }   // wall
  for (int i = 0; i < len; i++) if (sx[i] == nx && sy[i] == ny) { gameOver(); return; }   // tail

  bool ate = (nx == foodX && ny == foodY);
  if (ate && len < MAX_LEN) len++;          // keep the tail this tick = grow
  for (int i = len - 1; i > 0; i--) { sx[i] = sx[i - 1]; sy[i] = sy[i - 1]; }   // body follows
  sx[0] = nx; sy[0] = ny;                   // head moves
  if (ate) { score++; tone(BUZZ, 900, 40); placeFood(); if (speedMs > 80) speedMs -= 6; }

  oled.clearDisplay();
  for (int i = 0; i < len; i++) oled.fillRect(sx[i] * CELL, sy[i] * CELL, CELL - 1, CELL - 1, SSD1306_WHITE);
  oled.drawRect(foodX * CELL, foodY * CELL, CELL - 1, CELL - 1, SSD1306_WHITE);
  oled.display();
}

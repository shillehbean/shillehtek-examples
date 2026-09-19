// Arduino sketch for an Arduino Nano that reads a tactile button as a Morse key, provides a buzzer sidetone, decodes Morse into letters and digits, and displays the current symbol and decoded text on an SSD1306 I2C OLED.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ssd1306-oled-decode-morse-code
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

const int KEY = A0, BUZZ = 8;
const unsigned long DOT = 150;          // one unit in ms (dash = 3 units)

String symbol = "", text = "";
unsigned long pressStart = 0, releaseAt = 0;
bool keyDown = false, letterDone = false, wordDone = false;

const char* LETTERS[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
                         "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-",
                         "..-","...-",".--","-..-","-.--","--.."};
const char* DIGITS[]  = {"-----",".----","..---","...--","....-",
                         ".....","-....","--...","---..","----."};

char decode(const String& s) {
  for (int i = 0; i < 26; i++) if (s == LETTERS[i]) return 'A' + i;
  for (int i = 0; i < 10; i++) if (s == DIGITS[i])  return '0' + i;
  return '?';
}

void show() {
  oled.clearDisplay();
  oled.setTextSize(1); oled.setCursor(0, 0);  oled.print(symbol);   // dots/dashes so far
  oled.setTextSize(2); oled.setCursor(0, 24); oled.print(text);     // decoded text
  oled.display();
}

void setup() {
  pinMode(KEY, INPUT_PULLUP);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(SSD1306_WHITE);
  show();
}

void loop() {
  bool down = (digitalRead(KEY) == LOW);

  if (down && !keyDown) {                       // key just pressed
    keyDown = true; pressStart = millis();
    letterDone = wordDone = false;
    tone(BUZZ, 700);                              // sidetone
  }
  if (!down && keyDown) {                       // key just released
    keyDown = false; noTone(BUZZ);
    unsigned long held = millis() - pressStart;
    symbol += (held < DOT * 2) ? '.' : '-';
    releaseAt = millis();
    show();
  }
  // letter gap: 3 units of silence closes the symbol
  if (!keyDown && symbol.length() && !letterDone && millis() - releaseAt > DOT * 3) {
    text += decode(symbol); symbol = ""; letterDone = true;
    if (text.length() > 10) text = text.substring(1);   // scroll off the left
    show();
  }
  // word gap: 7 units of silence adds a space
  if (!keyDown && letterDone && !wordDone && millis() - releaseAt > DOT * 7) {
    text += ' '; wordDone = true; show();
  }
}

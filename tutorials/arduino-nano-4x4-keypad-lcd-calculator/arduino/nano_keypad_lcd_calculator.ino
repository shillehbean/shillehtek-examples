// Arduino sketch implementing a simple calculator: reads a 4x4 matrix keypad, manages the current number and expression, performs operations, and displays input/results on a 16x2 I2C LCD.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-4x4-keypad-lcd-calculator
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/4x4-membrane-matrix-keypad-16-key-switch-module-for-arduino-diy
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4, COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};
Keypad pad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String expr = "";        // what's shown on the top line, e.g. "12+7"
String num  = "";        // digits of the number currently being typed
double a = 0;            // first operand
char   op = 0;           // pending operator (A B C D) or 0
bool   done = false;     // a result is on screen

void reset() { expr = ""; num = ""; a = 0; op = 0; done = false; lcd.clear(); }

void redraw() {
  lcd.setCursor(0, 0); lcd.print("                ");
  lcd.setCursor(0, 0); lcd.print(expr);
}

void setup() { lcd.init(); lcd.backlight(); reset(); }

void loop() {
  char k = pad.getKey();
  if (!k) return;

  if (k == '*') { reset(); return; }                    // clear
  if (done) reset();                                    // start fresh after a result

  if (k >= '0' && k <= '9') {                           // digit
    if (num.length() < 8) { num += k; expr += k; }
  }
  else if (k == 'A' || k == 'B' || k == 'C' || k == 'D') {   // operator
    if (num.length() == 0 || op != 0) return;           // need a number, one op at a time
    a = num.toDouble(); num = ""; op = k;
    expr += (k == 'A') ? '+' : (k == 'B') ? '-' : (k == 'C') ? 'x' : '/';
  }
  else if (k == '#') {                                  // equals
    if (op == 0 || num.length() == 0) return;
    double b = num.toDouble(), r = 0;
    switch (op) {
      case 'A': r = a + b; break;
      case 'B': r = a - b; break;
      case 'C': r = a * b; break;
      case 'D': r = (b == 0) ? NAN : a / b; break;
    }
    lcd.setCursor(0, 1); lcd.print("= ");
    if (isnan(r))            lcd.print("Div by zero");
    else if (r == (long)r)   lcd.print((long)r);        // whole number: no decimals
    else                     lcd.print(r, 3);
    done = true;
    return;
  }
  redraw();
}

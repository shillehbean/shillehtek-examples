// Arduino sketch that measures capacitance by RC timing on two ranges (1k and 1M charge paths) and displays the autoranged result on an I2C LCD1602.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-lcd1602-capacitance-meter-autorange
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
//             https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int SENSE = A0, CHG_1K = 7, CHG_1M = 8, DISCH = 9;

void discharge() {
  pinMode(CHG_1K, INPUT); pinMode(CHG_1M, INPUT);
  pinMode(DISCH, OUTPUT); digitalWrite(DISCH, LOW);
  while (analogRead(SENSE) > 0);
  pinMode(DISCH, INPUT);
}

// returns microseconds to reach 63.2% through the given pin
unsigned long timeConstant(int pin, unsigned long timeoutUs) {
  pinMode(pin, OUTPUT); digitalWrite(pin, HIGH);
  unsigned long t0 = micros();
  while (analogRead(SENSE) < 647) {
    if (micros() - t0 > timeoutUs) { pinMode(pin, INPUT); return 0; }
  }
  unsigned long t = micros() - t0;
  pinMode(pin, INPUT);
  return t;
}

void setup() { lcd.init(); lcd.backlight(); }

void loop() {
  discharge();
  unsigned long t = timeConstant(CHG_1K, 1000000UL);   // try fast range first
  float value; const char* unit;

  if (t > 0) {                     // big capacitor: C = t / 1k  (uF)
    value = t / 1000.0; unit = "uF";
  } else {                         // tiny capacitor: use 1M  (nF)
    discharge();
    t = timeConstant(CHG_1M, 3000000UL);
    value = t / 1000.0; unit = "nF";
  }

  lcd.setCursor(0, 0); lcd.print("Capacitance:    ");
  lcd.setCursor(0, 1);
  if (t == 0) lcd.print("-- no cap --    ");
  else { lcd.print(value, 2); lcd.print(" "); lcd.print(unit); lcd.print("       "); }
  delay(800);
}

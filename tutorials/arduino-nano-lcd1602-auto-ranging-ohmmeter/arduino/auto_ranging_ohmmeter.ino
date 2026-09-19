// Arduino sketch that drives an I2C LCD and five reference resistor pins, reads the analog sense pin to perform auto-ranging resistance measurements, and formats results for display.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-lcd1602-auto-ranging-ohmmeter
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
//             https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int PIN[5] = {8, 9, 10, 11, 12};
// Measured reference values. Add ~30 ohms to the lowest one for the pin's own output resistance.
float REF[5] = {130.0, 1000.0, 10000.0, 100000.0, 1000000.0};
const char* NAME[5] = {"100", "1k", "10k", "100k", "1M"};
const int SENSE = A0;

int readRange(int r) {
  pinMode(PIN[r], OUTPUT); digitalWrite(PIN[r], HIGH);   // only this reference is "connected"
  delay(5);                                              // let the high ranges settle
  long s = 0; for (int i = 0; i < 16; i++) s += analogRead(SENSE);
  digitalWrite(PIN[r], LOW); pinMode(PIN[r], INPUT);     // back to high-impedance
  return s / 16;
}

void printOhms(float r) {
  if (r < 1000)     { lcd.print(r, 1);         lcd.print(" ");  }
  else if (r < 1e6) { lcd.print(r / 1000, 2);  lcd.print(" k"); }
  else              { lcd.print(r / 1e6, 2);   lcd.print(" M"); }
  lcd.write(0xF4);                                       // the omega symbol in the LCD's character ROM
  lcd.print("      ");
}

void setup() {
  lcd.init(); lcd.backlight();
  for (int i = 0; i < 5; i++) pinMode(PIN[i], INPUT);
}

void loop() {
  int adc[5], lo = 1023, hi = 0, best = 0;
  for (int r = 0; r < 5; r++) {
    adc[r] = readRange(r);
    lo = min(lo, adc[r]); hi = max(hi, adc[r]);
    if (abs(adc[r] - 512) < abs(adc[best] - 512)) best = r;   // closest to mid-scale wins
  }
  lcd.setCursor(0, 0);
  if (lo >= 1015)      lcd.print("Open  (> 5 M)   ");         // every range reads ~5 V
  else if (hi <= 4)    lcd.print("Short / < 2 ohm ");         // every range reads ~0 V
  else printOhms(REF[best] * adc[best] / (1023.0 - adc[best]));
  lcd.setCursor(0, 1);
  lcd.print("Range "); lcd.print(NAME[best]); lcd.print("  adc "); lcd.print(adc[best]); lcd.print("   ");
  delay(300);
}

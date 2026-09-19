// Reads an analog water level sensor, averages samples, maps the reading to a percentage, displays it on an I2C LCD, controls RGB LEDs to indicate level, and sounds a buzzer when the tank is full.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-water-level-sensor-percentage-alarm
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
//             https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int SENSOR = A0;
const int BUZZER = 2;
const int R = 10, B = 9, G = 8;
const int DRY = 0, FULL = 650;    // your Step 2 calibration

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(BUZZER, OUTPUT);
  pinMode(R, OUTPUT); pinMode(G, OUTPUT); pinMode(B, OUTPUT);
}

void loop() {
  long sum = 0;                    // average 20 readings
  for (int i = 0; i < 20; i++) { sum += analogRead(SENSOR); delay(10); }
  int pct = constrain(map(sum / 20, DRY, FULL, 0, 100), 0, 100);

  lcd.setCursor(0, 0);
  lcd.print("Water: ");
  lcd.print(pct);
  lcd.print("%   ");

  digitalWrite(G, pct < 60);                 // green: safe
  digitalWrite(B, pct >= 60 && pct < 99);    // blue: filling
  digitalWrite(R, pct >= 99);                // red: FULL

  if (pct >= 99) tone(BUZZER, 2000, 300);    // alarm at the brim

  delay(300);
}

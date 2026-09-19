// Reads an LM35 temperature sensor, averages samples for stability, displays the temperature on an I2C 16x2 LCD, and toggles between Celsius and Fahrenheit using a pushbutton.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-lm35-lcd-thermometer-c-f-toggle
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
//             https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int LM35 = A3;
const int BTN  = 2;
bool fahrenheit = false;

void setup() {
  lcd.init(); lcd.backlight();
  pinMode(BTN, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(BTN) == LOW) {          // toggle units
    fahrenheit = !fahrenheit;
    delay(300);
  }

  long sum = 0;                            // average 10 samples for a steady reading
  for (int i = 0; i < 10; i++) { sum += analogRead(LM35); delay(5); }
  float voltage = (sum / 10.0) * (5.0 / 1023.0);
  float tempC = voltage * 100.0;           // 10 mV per degree C

  lcd.setCursor(0, 0);
  lcd.print("Temperature:    ");
  lcd.setCursor(0, 1);
  if (fahrenheit) { lcd.print(tempC * 9.0 / 5.0 + 32.0, 1); lcd.print(" F      "); }
  else            { lcd.print(tempC, 1);                     lcd.print(" C      "); }

  delay(500);
}

// Reads an analog voltage through a resistor divider, averages samples, converts to the actual input voltage, and displays the result or warnings on an I2C LCD1602.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-lcd1602-50v-dc-voltmeter
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
//             https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int   SENSE = A3;
const float R1 = 100000.0, R2 = 10000.0;   // probe -> R1 -> A3 -> R2 -> GND
const float VREF = 5.00;                   // measure your 5V pin and type the real value here
const float MAX_V = 50.0;                  // over-range warning
const int   SAMPLES = 32;

float readVolts() {
  long sum = 0;
  for (int i = 0; i < SAMPLES; i++) sum += analogRead(SENSE);   // average out noise
  float vPin = (sum / (float)SAMPLES) * VREF / 1023.0;
  return vPin * (R1 + R2) / R2;                                  // undo the divider
}

void setup() {
  lcd.init(); lcd.backlight();
  lcd.print("DC Voltmeter");
}

void loop() {
  float v = readVolts();
  lcd.setCursor(0, 1);
  if (v > MAX_V)      lcd.print("  OVER RANGE!   ");
  else if (v < 0.05)  lcd.print("  0.00 V        ");        // ignore floating-input noise
  else { lcd.print("  "); lcd.print(v, 2); lcd.print(" V        "); }
  delay(250);
}

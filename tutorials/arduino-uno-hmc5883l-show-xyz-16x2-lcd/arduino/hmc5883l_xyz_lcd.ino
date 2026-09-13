// Arduino sketch that initializes the HMC5883L for continuous measurement, reads X/Y/Z magnetic field registers over I2C, and displays the values on Serial and a 16x2 LCD.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-hmc5883l-show-xyz-16x2-lcd
// Parts used: https://shillehtek.com/products/hmc5883l-gy-273-magnetometer-compass-module
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <LiquidCrystal.h>

#define HMC_ADDR 0x1E  // I2C 7-bit address of HMC5883L

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(16, 2);

  Wire.beginTransmission(HMC_ADDR);
  Wire.write(0x02);      // mode register
  Wire.write(0x00);      // continuous measurement mode
  Wire.endTransmission();
}

void loop() {
  int x, y, z;

  Wire.beginTransmission(HMC_ADDR);
  Wire.write(0x03);      // start of data registers
  Wire.endTransmission();

  Wire.requestFrom(HMC_ADDR, 6);
  if (6 <= Wire.available()) {
    x = Wire.read() << 8 | Wire.read();  // X MSB, LSB
    z = Wire.read() << 8 | Wire.read();  // Z MSB, LSB (register order!)
    y = Wire.read() << 8 | Wire.read();  // Y MSB, LSB
  }

  Serial.print("X: "); Serial.print(x);
  Serial.print("  Y: "); Serial.print(y);
  Serial.print("  Z: "); Serial.println(z);

  lcd.setCursor(0, 0);
  lcd.print("X:"); lcd.print(x);
  lcd.print(" Y:"); lcd.print(y);
  lcd.setCursor(0, 1);
  lcd.print("Z:"); lcd.print(z);

  delay(250);
}

// Reads distance from an HC-SR04/JSN-SR04T ultrasonic sensor, displays the value on a 16x2 I2C LCD, and drives a passive buzzer with proximity beeps and a solid stop tone.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-hc-sr04-lcd-parking-sensor-beeps
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
//             https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int TRIG = 9, ECHO = 10, BUZZ = 6;
const int STOP_CM = 15;                  // where the solid tone begins

long readCm() {
  digitalWrite(TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long us = pulseIn(ECHO, HIGH, 30000);  // timeout: nothing within ~5 m
  return us * 0.034 / 2;
}

void setup() {
  pinMode(TRIG, OUTPUT); pinMode(ECHO, INPUT); pinMode(BUZZ, OUTPUT);
  lcd.init(); lcd.backlight();
}

void loop() {
  long cm = readCm();
  if (cm < 2 || cm > 300) return;         // reject junk readings

  lcd.setCursor(0, 0); lcd.print("Distance: ");
  lcd.print(cm); lcd.print(" cm   ");

  if (cm <= STOP_CM) {
    tone(BUZZ, 2000);                      // STOP: solid tone
    lcd.setCursor(0, 1); lcd.print("   *** STOP ***  ");
  } else {
    noTone(BUZZ);
    int gap = map(constrain(cm, STOP_CM, 150), STOP_CM, 150, 60, 800);
    tone(BUZZ, 1500, 40);                  // beep faster as you get closer
    lcd.setCursor(0, 1); lcd.print(cm < 60 ? "  slow down...   " : "  keep coming    ");
    delay(gap);
  }
}

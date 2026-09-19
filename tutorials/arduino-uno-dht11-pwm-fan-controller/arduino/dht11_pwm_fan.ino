// Reads temperature/humidity from a DHT11, reads a potentiometer for the temperature setpoint, displays values on an I2C LCD, and controls a DC fan via PWM with hysteresis and proportional control.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-dht11-pwm-fan-controller
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/shillehtek-dht11-with-cables
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <DHT.h>
#include <LiquidCrystal_I2C.h>
DHT dht(2, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);     // try 0x3F if the screen stays blank

const int POT = A0, ENA = 9, IN1 = 7, IN2 = 8;
const float BAND = 4.0;                 // degrees above set point for 100 % fan
const float HYST = 0.5;                 // fan turns off only 0.5 C below set point
bool fanOn = false;

void setup() {
  dht.begin(); lcd.init(); lcd.backlight();
  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);   // fixed direction
}

void loop() {
  float setPt = 15.0 + analogRead(POT) * 25.0 / 1023.0;   // knob: 15 ... 40 C
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(t)) { lcd.setCursor(0, 0); lcd.print("DHT error       "); delay(2000); return; }

  // hysteresis: switch on above set point, off only below set point - HYST
  if (t >= setPt) fanOn = true;
  else if (t < setPt - HYST) fanOn = false;

  // proportional speed: 0 % at the set point, 100 % at set point + BAND
  int pct = 0;
  if (fanOn) pct = constrain((t - setPt) / BAND * 100.0, 25, 100);   // never below 25 % (fans stall)
  analogWrite(ENA, map(pct, 0, 100, 0, 255));

  lcd.setCursor(0, 0);
  lcd.print("T:"); lcd.print(t, 1); lcd.print("C H:"); lcd.print((int)h); lcd.print("% ");
  lcd.setCursor(0, 1);
  lcd.print("Set:"); lcd.print(setPt, 1); lcd.print(" Fan:"); lcd.print(pct); lcd.print("%  ");
  delay(2000);                          // DHT11 minimum interval
}

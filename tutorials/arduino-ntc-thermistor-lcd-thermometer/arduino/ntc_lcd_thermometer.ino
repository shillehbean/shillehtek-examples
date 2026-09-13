// Arduino sketch that reads a 10K NTC thermistor on A0, computes temperature via the Steinhart–Hart equation, displays Celsius and Fahrenheit on a 16x2 LCD, and controls LEDs and a buzzer for alarms.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-ntc-thermistor-lcd-thermometer
// Parts used: https://shillehtek.com/products/10k-ntc-thermistor-temperature-sensor-mf52-103
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Arduino pins to LCD

#define ThermistorPin A0
long ADC_Value;
float R1 = 10000; // fixed divider resistor
float logR2, R2, T;

// Steinhart-Hart coefficients for a 10K NTC
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741;
float temp_c, temp_f;

#define G_led 8
#define R_led 9
#define buzzer 13

void setup() {
  pinMode(ThermistorPin, INPUT);
  pinMode(R_led, OUTPUT);
  pinMode(G_led, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Welcome To   ");
  lcd.setCursor(0, 1);
  lcd.print("Temperature NTC");
  delay(2000);
  lcd.clear();
}

void loop() {
  ADC_Value = 0;
  for (int i = 0; i < 50; i++) {   // average 50 samples
    ADC_Value = ADC_Value + analogRead(ThermistorPin);
    delay(1);
  }
  ADC_Value = ADC_Value / 50;

  R2 = R1 * (1023.0 / (float)ADC_Value - 1.0); // thermistor resistance
  logR2 = log(R2);
  temp_c = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // Kelvin
  temp_c = temp_c - 273.15;                    // to Celsius
  temp_f = (temp_c * 9.0) / 5.0 + 32.0;        // to Fahrenheit

  lcd.setCursor(0, 0);
  lcd.print("  Temperature   ");
  lcd.setCursor(0, 1);
  lcd.print(temp_c, 1);
  lcd.write(0xdf); // degree symbol
  lcd.print("C  ");
  lcd.setCursor(9, 1);
  lcd.print(temp_f, 1);
  lcd.write(0xdf);
  lcd.print("F  ");

  if (temp_f > 100) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(G_led, LOW);
    digitalWrite(R_led, HIGH);
    delay(300);
  } else {
    digitalWrite(G_led, HIGH);
    digitalWrite(R_led, LOW);
  }

  digitalWrite(buzzer, LOW);
  delay(500);
}

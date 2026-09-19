// Arduino sketch for an Arduino Nano that measures an 18650 battery voltage, controls a 1-channel relay to apply a load, accumulates mAh and mWh during discharge, and displays status on an I2C LCD with button control and cutoff protection.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-relay-measure-18650-mah
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
//             https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int RELAY = 10, BTN = 9, VBAT = A0;
const bool  RELAY_ON = LOW;      // most 1-channel modules are active-LOW; flip if yours clicks the wrong way
const float VREF     = 5.00;     // measured 5V pin voltage
const float R_LOAD   = 4.0;      // measured load resistance in ohms
const float V_CUTOFF = 3.0;      // stop here (never below 2.8 V)

enum { IDLE, RUNNING, DONE } state = IDLE;
float mAh = 0, mWh = 0;
unsigned long t0, lastStep;

float readV() {                                  // average 32 samples for a steady reading
  long s = 0; for (int i = 0; i < 32; i++) s += analogRead(VBAT);
  return s / 32.0 * VREF / 1023.0;
}

void setup() {
  pinMode(RELAY, OUTPUT); digitalWrite(RELAY, !RELAY_ON);   // load OFF
  pinMode(BTN, INPUT_PULLUP);
  lcd.init(); lcd.backlight();
}

void loop() {
  float v = readV();

  if (state == IDLE) {
    lcd.setCursor(0, 0); lcd.print("Batt "); lcd.print(v, 2); lcd.print("V      ");
    lcd.setCursor(0, 1); lcd.print(v > 3.3 ? "Press to start  " : "Charge battery  ");
    if (digitalRead(BTN) == LOW && v > 3.3) {
      mAh = 0; mWh = 0; t0 = lastStep = millis();
      digitalWrite(RELAY, RELAY_ON);             // load ON
      state = RUNNING; delay(300);
    }

  } else if (state == RUNNING) {
    unsigned long now = millis();
    if (now - lastStep >= 500) {
      float dtH = (now - lastStep) / 3600000.0;  // elapsed hours since last step
      lastStep = now;
      float i = v / R_LOAD;                      // amps through the load
      mAh += i * 1000.0 * dtH;                   // integrate current  -> mAh
      mWh += v * i * 1000.0 * dtH;               // integrate power    -> mWh
      lcd.setCursor(0, 0);
      lcd.print(v, 2); lcd.print("V "); lcd.print(i, 2); lcd.print("A ");
      lcd.print((now - t0) / 60000); lcd.print("m ");
      lcd.setCursor(0, 1);
      lcd.print((int)mAh); lcd.print("mAh "); lcd.print((int)mWh); lcd.print("mWh ");
      if (v <= V_CUTOFF) { digitalWrite(RELAY, !RELAY_ON); state = DONE; }   // load OFF
    }

  } else {                                       // DONE
    lcd.setCursor(0, 0); lcd.print("Done: "); lcd.print((int)mAh); lcd.print(" mAh   ");
    lcd.setCursor(0, 1); lcd.print((int)mWh); lcd.print(" mWh - reset ");
    if (digitalRead(BTN) == LOW) { state = IDLE; delay(300); }
  }
}

// Arduino base-station sketch that reads 4-byte telemetry packets from an HC-12, displays temperature and humidity on an I2C 16x2 LCD, and sends simple toggle commands when buttons are pressed.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-hc-12-dht11-long-range-telemetry
// Parts used: https://shillehtek.com/products/hc-12-433mhz-serial-transceiver-si4438-arduino-esp32
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define B0 2
#define B1 3

SoftwareSerial HC12(7, 8);        // RX (to HC-12 TXD), TX (to HC-12 RXD)
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte RX[4];

void setup() {
  pinMode(B0, INPUT_PULLUP);
  pinMode(B1, INPUT_PULLUP);
  HC12.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("Waiting data...");
}

void loop() {
  if (!digitalRead(B0)) { HC12.write((byte)1); delay(250); }  // toggle red
  if (!digitalRead(B1)) { HC12.write((byte)2); delay(250); }  // toggle blue

  if (HC12.available() >= 4) {
    for (byte i = 0; i < 4; i++) RX[i] = HC12.read();
    float temp = (RX[0] * 256 + RX[1]) / 100.0;
    float humi = (RX[2] * 256 + RX[3]) / 100.0;

    if (temp >= 0 && temp <= 100 && humi >= 0) {
      lcd.setCursor(0, 0);
      lcd.print("Temp: "); lcd.print(temp, 1); lcd.print((char)223); lcd.print("C  ");
      lcd.setCursor(0, 1);
      lcd.print("Hum:  "); lcd.print(humi, 1); lcd.print("%   ");
    }
  }
}

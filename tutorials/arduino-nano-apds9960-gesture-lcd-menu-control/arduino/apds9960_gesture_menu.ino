// Arduino sketch that initializes the APDS-9960 gesture sensor and I2C 16x2 LCD, shows a menu, and uses gestures to navigate and toggle two digital outputs.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-apds9960-gesture-lcd-menu-control
// Parts used: https://shillehtek.com/products/apds-9960-gesture-proximity-color-sensor-module
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include "SoftwareSerial.h"
#include <LiquidCrystal_I2C.h>
#include "Adafruit_APDS9960.h"

Adafruit_APDS9960 apds;
LiquidCrystal_I2C lcd(0x27,16,2);
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX

byte count = 2;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  lcd.init();
  lcd.backlight();

  for(byte i = 2; i <= 4; i++)
  {
    pinMode(i, OUTPUT);
  }

  if(!apds.begin())
  {
    Serial.println("Failed to initialize the sensor. Check your connections!");
  }
  else
    Serial.println("Device initialized!");

  apds.enableProximity(true);
  apds.enableGesture(true);

  show_menu(count);
}

void loop()
{
  uint8_t gesture = apds.readGesture();

  if(gesture == APDS9960_UP)
  {
    count++;
    if(count > 4) { count = 4; }
    show_menu(count);
  }

  if(gesture == APDS9960_LEFT)
  {
    if(count == 2) { digitalWrite(2, LOW); }
    if(count == 3) { digitalWrite(3, LOW); }
    if(count == 4) { digitalWrite(2, LOW); digitalWrite(3, LOW); }
  }

  if(gesture == APDS9960_RIGHT)
  {
    if(count == 2) { digitalWrite(2, HIGH); }
    if(count == 3) { digitalWrite(3, HIGH); }
    if(count == 4) { digitalWrite(2, HIGH); digitalWrite(3, HIGH); }
  }

  if(gesture == APDS9960_DOWN)
  {
    count--;
    if(count < 2) { count = 2; }
    show_menu(count);
  }
}

void show_menu(byte option)
{
  if(option == 2)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("-> LED1");
    lcd.setCursor(0,1);
    lcd.print("   LED2");
    return;
  }

  if(option == 3)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   LED1");
    lcd.setCursor(0,1);
    lcd.print("-> LED2");
    return;
  }

  if(option == 4)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("-> LED1 and LED2");
    return;
  }

  return;
}

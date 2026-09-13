// Reads temperature from a DS18B20 and current time from a DS3231, controls heater and light relays based on temperature and a daily schedule, and updates an SSD1306 OLED display with status.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ds18b20-aquarium-controller
// Parts used: https://shillehtek.com/products/ds18b20-waterproof-digital-temp-sensor-probe-1m-for-arduino-pi
//             https://shillehtek.com/products/ds3231-at24c32-iic-module-precision-rtc-module-with-cr2032-battery
//             https://shillehtek.com/products/2-channel-5v-relay-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

OneWire bus(2); DallasTemperature ds(&bus);
RTC_DS3231 rtc;
Adafruit_SSD1306 oled(128, 64, &Wire, -1);
const int HEATER = 3, LIGHT = 4;
const float TARGET_C = 25.0, BAND = 0.5;
const int LIGHT_ON_HOUR = 8, LIGHT_OFF_HOUR = 20;

void setup() {
  pinMode(HEATER, OUTPUT); pinMode(LIGHT, OUTPUT);
  ds.begin(); rtc.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  ds.requestTemperatures();
  float t = ds.getTempCByIndex(0);
  DateTime now = rtc.now();

  bool heaterOn = t < (TARGET_C - BAND);
  bool lightOn  = now.hour() >= LIGHT_ON_HOUR && now.hour() < LIGHT_OFF_HOUR;
  digitalWrite(HEATER, heaterOn ? HIGH : LOW);
  digitalWrite(LIGHT,  lightOn  ? HIGH : LOW);

  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setTextSize(2); oled.setCursor(0, 0);
  oled.print(t, 1); oled.print((char)247); oled.print("C");
  oled.setTextSize(1); oled.setCursor(0, 30);
  oled.print("Heater: "); oled.println(heaterOn ? "ON" : "off");
  oled.print("Light:  "); oled.println(lightOn ? "ON" : "off");
  oled.setCursor(0, 56);
  oled.print(now.hour()); oled.print(':');
  if (now.minute() < 10) oled.print('0'); oled.print(now.minute());
  oled.display();
  delay(2000);
}

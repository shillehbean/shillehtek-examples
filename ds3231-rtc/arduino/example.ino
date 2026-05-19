// Reads date/time and temperature from a DS3231 using Adafruit RTClib, prints them to Serial, and sets the clock if the module lost power (with an optional compile-time set).
//
// Buy this module: https://shillehtek.com/products/ds3231-at24c32-iic-module-precision-rtc-module-with-cr2032-battery
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ds3231-at24c32-iic-module-precision-rtc-module-with-cr2032-battery-manual
// More examples: https://github.com/shillehtek/examples
//

// DS3231 RTC - Arduino Example
// Library: RTClib by Adafruit

#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  if (!rtc.begin()) {
    Serial.println("DS3231 not found!");
    while (1);
  }

  // Run ONCE to set time, then comment out and re-upload:
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  if (rtc.lostPower()) {
    Serial.println("Setting time to compile time...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();

  Serial.print(now.year()); Serial.print('/');
  Serial.print(now.month()); Serial.print('/');
  Serial.print(now.day()); Serial.print(' ');
  Serial.print(now.hour()); Serial.print(':');
  Serial.print(now.minute()); Serial.print(':');
  Serial.println(now.second());

  Serial.print("Temp: ");
  Serial.print(rtc.getTemperature());
  Serial.println(" C");

  delay(1000);
}

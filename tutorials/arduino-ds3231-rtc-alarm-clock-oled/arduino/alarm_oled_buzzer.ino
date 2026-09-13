// Displays the current time on an SSD1306 OLED, shows alarm time/status, checks the DS3231 for the alarm time, and rings a buzzer when the alarm condition is met (includes button inputs for setting mode).
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-ds3231-rtc-alarm-clock-oled
// Parts used: https://shillehtek.com/products/ds3231-at24c32-iic-module-precision-rtc-module-with-cr2032-battery
//             https://shillehtek.com/products/0-96-i2c-blue-oled-display-module-4-pin-ssd1306
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

RTC_DS3231 rtc;
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

const int BUZZ = 8;
const int BTN_SET = 2, BTN_MODE = 3;

int alarmHour = 7, alarmMin = 0;
bool alarmEnabled = true, alarmRinging = false;

void setup() {
  pinMode(BUZZ, OUTPUT);
  pinMode(BTN_SET, INPUT_PULLUP);
  pinMode(BTN_MODE, INPUT_PULLUP);
  Wire.begin();
  rtc.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  DateTime now = rtc.now();

  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setTextSize(3);
  oled.setCursor(0, 4);
  if (now.hour() < 10) oled.print('0'); oled.print(now.hour()); oled.print(':');
  if (now.minute() < 10) oled.print('0'); oled.print(now.minute());

  oled.setTextSize(1);
  oled.setCursor(0, 48);
  oled.print("Alarm "); oled.print(alarmHour); oled.print(':');
  if (alarmMin < 10) oled.print('0'); oled.print(alarmMin);
  oled.print(alarmEnabled ? " ON" : " OFF");

  oled.display();

  if (alarmEnabled && now.hour() == alarmHour && now.minute() == alarmMin) {
    alarmRinging = true;
  }
  if (alarmRinging) {
    tone(BUZZ, 1000, 500);
    delay(600);
    if (digitalRead(BTN_SET) == LOW) { alarmRinging = false; noTone(BUZZ); }
  }

  if (digitalRead(BTN_MODE) == LOW) { alarmEnabled = !alarmEnabled; delay(300); }

  delay(200);
}

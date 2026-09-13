// Arduino sketch that reads time from a DS3231 RTC, displays it on an SSD1306 OLED, fades a relay/MOSFET output over a pre-alarm period to simulate sunrise, and activates a buzzer at the alarm time.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ds3231-sunrise-alarm-clock
// Parts used: https://shillehtek.com/products/ds3231-at24c32-iic-module-precision-rtc-module-with-cr2032-battery
//             https://shillehtek.com/products/1-channel-5v-relay-module
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
RTC_DS3231 rtc;
Adafruit_SSD1306 oled(128, 64, &Wire, -1);
const int RELAY = 3, BUZZ = 8;
const int ALARM_HOUR = 7, ALARM_MIN = 0;
const int FADE_MIN = 30;   // start fade-in 30 min before alarm
bool dawnRunning = false;
unsigned long dawnStart = 0;

void setup() {
  Wire.begin(); rtc.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(RELAY, OUTPUT); pinMode(BUZZ, OUTPUT);
}

void loop() {
  DateTime now = rtc.now();
  int totalNow = now.hour() * 60 + now.minute();
  int alarmNow = ALARM_HOUR * 60 + ALARM_MIN;
  int diff = alarmNow - totalNow;

  if (diff >= 0 && diff <= FADE_MIN) {
    // PWM the relay/MOSFET - fade from 0 to 255 over FADE_MIN minutes
    float progress = 1.0 - (float)diff / FADE_MIN;
    analogWrite(RELAY, (int)(progress * 255));
  } else if (diff < 0 && diff > -2) {
    // Buzzer kicks in at actual alarm time
    tone(BUZZ, 1000, 200); delay(400);
  } else {
    analogWrite(RELAY, 0); noTone(BUZZ);
  }

  oled.clearDisplay(); oled.setTextSize(2); oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 8);
  oled.printf("%02d:%02d", now.hour(), now.minute());
  oled.setTextSize(1); oled.setCursor(0, 50);
  oled.printf("Alarm: %02d:%02d", ALARM_HOUR, ALARM_MIN);
  oled.display();
  delay(1000);
}

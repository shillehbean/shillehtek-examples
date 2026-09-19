// An ESP32 Arduino sketch that connects to Wi‑Fi, syncs local time via NTP (with timezone/DST), reads temperature and humidity from a DHT11, and updates an SSD1306 OLED with time/date and sensor readings.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-oled-dht-internet-clock
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306
//             https://shillehtek.com/products/shillehtek-dht11-with-cables
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <time.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

const char* SSID = "YourNetwork";
const char* PASS = "YourPassword";
const char* TZ   = "EST5EDT,M3.2.0,M11.1.0";     // your POSIX time-zone string

Adafruit_SSD1306 oled(128, 64, &Wire, -1);
DHT dht(23, DHT11);                              // change to DHT22 if that's what you have

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(SSD1306_WHITE);
  oled.clearDisplay(); oled.setCursor(0, 0); oled.print("Connecting..."); oled.display();

  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(250);

  configTzTime(TZ, "pool.ntp.org", "time.nist.gov");   // sync clock, apply zone + DST
  dht.begin();
}

void loop() {
  struct tm t;
  if (!getLocalTime(&t)) { delay(500); return; }     // waits for the first NTP sync

  float tempC = dht.readTemperature();
  float hum   = dht.readHumidity();

  char hhmmss[9], date[24];
  strftime(hhmmss, sizeof hhmmss, "%H:%M:%S", &t);
  strftime(date,   sizeof date,   "%a %d %b %Y", &t);

  oled.clearDisplay();
  oled.setTextSize(2); oled.setCursor(16, 0);  oled.print(hhmmss);
  oled.setTextSize(1); oled.setCursor(22, 22); oled.print(date);
  oled.setCursor(0, 44);
  if (isnan(tempC)) oled.print("DHT read error");
  else {
    oled.print("Temp "); oled.print(tempC, 1); oled.print(" C  Hum ");
    oled.print(hum, 0);  oled.print("%");
  }
  oled.display();
  delay(1000);
}

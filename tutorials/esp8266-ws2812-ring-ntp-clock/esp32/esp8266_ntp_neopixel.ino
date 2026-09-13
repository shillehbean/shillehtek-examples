// ESP8266 Arduino-framework sketch that connects to Wi‑Fi, syncs time via NTP, and drives a 24-LED WS2812 NeoPixel ring to act as a clock.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp8266-ws2812-ring-ntp-clock
// Parts used: https://shillehtek.com/products/ws2812-led-ring-90mm-arduino-raspberry-pi-esp32
//             https://shillehtek.com/products/esp8266-d1-mini-v3-4mb-dev-board-presoldered
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include "TimeClient.h"

#define PIN D5
long lastUpdate = millis();
long lastSecond = millis();

String hours, minutes, seconds;
int currentSecond, currentMinute, currentHour;

char ssid[] = "xxxxxxx";  // your network SSID
char pass[] = "xxxxxxx";  // your network password

const float UTC_OFFSET = 0; // set your timezone offset
TimeClient timeClient(UTC_OFFSET);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN);

void setup()
{
  Serial.begin(115200);
  Serial.println();

  strip.begin();
  strip.setBrightness(128); // 50%
  strip.show();

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  timeClient.updateTime();
  updateTime();
  lastUpdate = millis();
  lastSecond = millis();
}

void loop()
{
  // re-sync with NTP every 30 minutes
  if ((millis() - lastUpdate) > 1800000) updateTime();

  if ((millis() - lastSecond) > 1000)
  {
    // erase old hand positions
    strip.setPixelColor(currentSecond / 2.5, 0, 0, 0);
    strip.setPixelColor(currentMinute / 2.5, 0, 0, 0);
    strip.setPixelColor(currentHour * 2, 0, 0, 0);

    strip.show();
    lastSecond = millis();
    currentSecond++;
    if (currentSecond > 59)
    {
      currentSecond = 0;
      currentMinute++;
      if (currentMinute > 59) {
        currentMinute = 0;
        currentHour++;
        if (currentHour > 12) currentHour = 0;
      }
    }
    String currentTime = String(currentHour) + ':' + String(currentMinute) + ':' + String(currentSecond);
    Serial.println(currentTime);

    // draw the hands: blue seconds, green minutes, red hours
    strip.setPixelColor(currentSecond / 2.5, 0, 0, 255);
    strip.setPixelColor(currentMinute / 2.5, 0, 255, 0);
    strip.setPixelColor(currentHour * 2, 255, 0, 0);
    strip.show();
  }
}

void updateTime()
{
  hours = timeClient.getHours();
  minutes = timeClient.getMinutes();
  seconds = timeClient.getSeconds();
  currentHour = hours.toInt();
  if (currentHour > 12) currentHour = currentHour - 12;
  currentMinute = minutes.toInt();
  currentSecond = seconds.toInt();
  lastUpdate = millis();
}

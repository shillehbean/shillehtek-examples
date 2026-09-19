// ESP32 Arduino sketch that connects to Wi‑Fi, fetches current weather and forecast JSON from OpenWeatherMap, parses it with ArduinoJson, and prepares data for display on an ST7789 TFT.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-st7789-weather-forecast
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/tft-lcd-1-3-240x240-st7789-esp32-arduino
//             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h>
TFT_eSPI tft;

const char* SSID = "YourNetwork";
const char* PASS = "YourPassword";
const char* KEY  = "your_openweathermap_api_key";
const char* CITY = "Boston,US";                     // "City,CountryCode"

struct Day { long day; float lo, hi; String cond; };
Day days[6]; int nDays = 0;
float nowT = 0, nowH = 0; String nowCond = "--"; long tzOff = 0;
const char* WD[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

bool getJson(const String& url, JsonDocument& doc, JsonDocument* filter = nullptr) {
  HTTPClient http; http.useHTTP10(true);            // plain HTTP/1.0 so we can parse the stream
  http.begin(url);
  if (http.GET() != 200) { http.end(); return false; }
  DeserializationError e = filter
      ? deserializeJson(doc, http.getStream(), DeserializationOption::Filter(*filter))
      : deserializeJson(doc, http.getStream());
  http.end();
  return !e;
}

void fetchWeather() {
  String base = "http://api.openweathermap.org/data/2.5/";
  String tail = String("?q=") + CITY + "&units=metric&appid=" + KEY;
  JsonDocument doc;

  if (getJson(base + "weather" + tail, doc)) {      // current conditions
    nowT = doc["main"]["temp"]; nowH = doc["main"]["humidity"];
    nowCond = doc["weather"][0]["main"].as<String>();
    tzOff = doc["timezone"];                        // seconds east of UTC
  }

  JsonDocument filter;                              // keep only what we need from ~16 KB of JSON
  filter["list"][0]["dt"] = true;
  filter["list"][0]["main"]["temp_min"] = true;
  filter["list"][0]["main"]["temp_max"] = true;
  filter["list"][0]["weather"][0]["main"] = true;
  doc.clear();
  if (getJson(base + "forecast" + tail, doc, &filter)) {   // 40 x 3-hour slots
    nDays = 0;
    for (JsonObject it : doc["list"].as<JsonArray>()) {
      long local = it["dt"].as<long>() + tzOff;
      long d = local / 86400, hour = (local % 86400) / 3600;
      float lo = it["main"]["temp_min"], hi = it["main"]["temp_max"];
      String c = it["weather"][0]["main"].as<String>();
      if (nDays == 0 || days[nDays - 1].day != d) {
        if (nDays == 6) break;
        days[nDays++] = { d, lo, hi, c };           // new calendar day
      }
      Day& D = days[nDays - 1];
      D.lo = min(D.lo, lo); D.hi = max(D.hi, hi);
      if (hour >= 12 && hour < 15) D.cond = c;         // midday slot describes the day
    }
  }
}

void draw() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK); tft.drawString(CITY, 6, 4, 2);
  tft.setTextColor(TFT_CYAN,  TFT_BLACK); tft.drawString(String(nowT, 1) + " C", 6, 22, 4);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString(nowCond + "  " + String((int)nowH) + "% RH", 6, 52, 2);
  tft.drawFastHLine(0, 74, 240, TFT_DARKGREY);
  int start = (nDays > 5) ? 1 : 0;                  // skip today's partial day if we have 6
  for (int i = 0; i < 5 && start + i < nDays; i++) {
    Day& D = days[start + i]; int y = 82 + i * 30;
    tft.setTextColor(TFT_YELLOW, TFT_BLACK); tft.drawString(WD[(D.day + 4) % 7], 6, y, 2);
    tft.setTextColor(TFT_WHITE,  TFT_BLACK);
    tft.drawString(String((int)round(D.lo)) + "/" + String((int)round(D.hi)) + " C", 56, y, 2);
    tft.setTextColor(TFT_GREENYELLOW, TFT_BLACK); tft.drawString(D.cond, 140, y, 2);
  }
}

void setup() {
  Serial.begin(115200);
  tft.init(); tft.setRotation(0); tft.fillScreen(TFT_BLACK);
  tft.drawString("Connecting...", 6, 4, 2);
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(250);
  fetchWeather(); draw();
}

void loop() {
  static unsigned long last = 0;
  if (millis() - last >= 600000UL) { last = millis(); fetchWeather(); draw(); }   // every 10 min
}

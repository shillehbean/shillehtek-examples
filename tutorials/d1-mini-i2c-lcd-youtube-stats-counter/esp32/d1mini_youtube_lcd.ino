// Arduino sketch for an ESP8266/ESP32-based D1 Mini that connects to Wi‑Fi, requests YouTube channel statistics via the YouTube Data API over HTTPS, parses the JSON response, and displays subscribers, views, and video counts on an I2C 16x2 LCD.
//
// Full tutorial: https://shillehtek.com/blogs/news/d1-mini-i2c-lcd-youtube-stats-counter
// Parts used: https://shillehtek.com/products/esp8266-d1-mini-v3-4mb-dev-board-presoldered
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
//             https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* SSID    = "YourNetwork";
const char* PASS    = "YourPassword";
const char* API_KEY = "your_youtube_data_api_key";
const char* CHANNEL = "UCxxxxxxxxxxxxxxxxxxxxxx";     // 24-char channel id

String subs, views, videos;

String commas(String s) {                             // "1234567" -> "1,234,567"
  for (int i = s.length() - 3; i > 0; i -= 3) s = s.substring(0, i) + "," + s.substring(i);
  return s;
}

bool fetchStats() {
  WiFiClientSecure client; client.setInsecure();      // HTTPS without a stored certificate
  HTTPClient http;
  String url = String("https://www.googleapis.com/youtube/v3/channels")
             + "?part=statistics&fields=items/statistics&id=" + CHANNEL + "&key=" + API_KEY;
  http.begin(client, url);
  int code = http.GET();
  if (code != 200) { Serial.println("HTTP " + String(code)); http.end(); return false; }
  JsonDocument doc;
  DeserializationError e = deserializeJson(doc, http.getString());
  http.end();
  if (e || doc["items"].size() == 0) return false;
  JsonObject s = doc["items"][0]["statistics"];
  subs   = s["subscriberCount"].as<String>();          // numbers arrive as strings
  views  = s["viewCount"].as<String>();
  videos = s["videoCount"].as<String>();
  return true;
}

void setup() {
  Serial.begin(115200);
  lcd.init(); lcd.backlight(); lcd.print("Connecting...");
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(250);
  lcd.clear();
}

void loop() {
  static unsigned long last = 0; static bool first = true;
  if (first || millis() - last >= 60000) {            // refresh every minute
    first = false; last = millis();
    if (fetchStats()) {
      lcd.setCursor(0, 0); lcd.print("Subs: "); lcd.print(commas(subs));  lcd.print("      ");
      lcd.setCursor(0, 1); lcd.print("Views:"); lcd.print(commas(views)); lcd.print("      ");
      Serial.println(subs + " subs, " + views + " views, " + videos + " videos");
    } else {
      lcd.setCursor(0, 0); lcd.print("API error       ");
    }
  }
}

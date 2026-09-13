// ESP32 Arduino sketch that reads BME280 sensor data, fetches outdoor temperature from OpenWeatherMap, and drives an ST7735 display to show weather information.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-bme280-st7735-wifi-weather-station
// Parts used: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
//             https://shillehtek.com/products/shillehtek-1-8-inch-tft-lcd-display-module-dual-side-soldering
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

Adafruit_BME280 bme;
#define TFT_CS 5
#define TFT_RST 4
#define TFT_DC 2
Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);

const char* SSID = "YOUR_WIFI";
const char* PASS = "YOUR_PASS";
const char* OWM_KEY = "YOUR_API_KEY";
const char* CITY_ID = "YOUR_CITY_ID";

float outdoorTemp = 0;

void fetchOutdoor() {
  HTTPClient http;
  String url = String("http://api.openweathermap.org/data/2.5/weather?id=") +
               CITY_ID + "&units=metric&appid=" + OWM_KEY;
  http.begin(url);
  if (http.GET() == 200) {
    StaticJsonDocument<1024> d;
    deserializeJson(d, http.getString());
    outdoorTemp = d["main"]["temp"].as<float>();
  }
  http.end();
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  bme.begin(0x76);
  tft.initR(INITR_BLACKTAB); tft.setRotation(1);
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
}

void loop() {
  fetchOutdoor();
  float t = bme.readTemperature();
  float h = bme.readHumidity();
  float p = bme.readPressure() / 100.0;
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0); tft.setTextColor(ST77XX_WHITE);
  tft.printf("Indoor\n %.1fC %.0f%%\n %.0f hPa\n", t, h, p);
  tft.printf("\nOutdoor\n %.1fC", outdoorTemp);
  delay(60000);
}

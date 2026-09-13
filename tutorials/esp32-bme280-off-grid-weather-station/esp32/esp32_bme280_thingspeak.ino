// ESP32 Arduino sketch that reads temperature, humidity, and pressure from a BME280, sends the values to ThingSpeak via HTTP, then puts the ESP32 into deep sleep for a defined interval.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-bme280-off-grid-weather-station
// Parts used: https://shillehtek.com/products/110-x-136mm-6v-2w-solar-panel
//             https://shillehtek.com/products/cn3791-6v-mppt-solar-charger-module
//             https://shillehtek.com/products/tp4056-1a-lipo-battery-charging-board-type-c-with-current-protection
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <Adafruit_BME280.h>
#include <HTTPClient.h>
#define SLEEP_S 600   // 10 minutes

Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  bme.begin(0x76);
  WiFi.begin("MY_SSID","MY_PASS");
  while (WiFi.status() != WL_CONNECTED) delay(200);

  float t = bme.readTemperature();
  float h = bme.readHumidity();
  float p = bme.readPressure() / 100.0;

  HTTPClient http;
  String url = "https://api.thingspeak.com/update?api_key=KEY&field1=" +
               String(t)+"&field2="+String(h)+"&field3="+String(p);
  http.begin(url); http.GET(); http.end();

  esp_sleep_enable_timer_wakeup(SLEEP_S * 1000000ULL);
  esp_deep_sleep_start();
}
void loop(){}

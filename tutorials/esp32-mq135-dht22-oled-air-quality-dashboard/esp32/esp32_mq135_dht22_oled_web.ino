// ESP32 sketch that reads MQ-135 analog air quality and DHT22 temperature/humidity sensors, displays the values on an SSD1306 OLED, and serves a simple web page with the current readings.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-mq135-dht22-oled-air-quality-dashboard
// Parts used: https://shillehtek.com/products/mq-135-air-quality-hazardous-gas-sensor-module-for-arduino
//             https://shillehtek.com/products/shillehtek-dht22-with-cables
//             https://shillehtek.com/products/0-96-i2c-blue-oled-display-module-4-pin-ssd1306
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
DHT dht(4, DHT22);
Adafruit_SSD1306 oled(128, 64, &Wire, -1);
WebServer server(80);
const int MQ_PIN = 36;
float t=0, h=0; int aq=0;
void handle() {
  server.send(200, "text/html",
    "<h1>Air Quality</h1><p>T: " + String(t) + " C</p><p>H: " + String(h) +
    "%</p><p>AQ: " + String(aq) + "</p>");
}
void setup() {
  Serial.begin(115200); dht.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  WiFi.begin("SSID","PASS");
  while (WiFi.status() != WL_CONNECTED) delay(500);
  server.on("/", handle); server.begin();
}
void loop() {
  t = dht.readTemperature(); h = dht.readHumidity();
  aq = analogRead(MQ_PIN);
  oled.clearDisplay();
  oled.setTextSize(1); oled.setTextColor(SSD1306_WHITE); oled.setCursor(0,0);
  oled.printf("T: %.1f C\nH: %.1f%%\nAQ: %d\n%s", t, h, aq, WiFi.localIP().toString().c_str());
  oled.display();
  server.handleClient();
  delay(2000);
}

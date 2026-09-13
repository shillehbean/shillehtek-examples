// ESP32 Arduino sketch that reads a DS18B20 probe, displays temperature on an SSD1306 OLED, connects to Wi‑Fi and sends Telegram alerts and a buzzer notification when the target temperature is reached.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-ds18b20-wifi-smoker-thermometer-alerts
// Parts used: https://shillehtek.com/products/ds18b20-waterproof-digital-temp-sensor-probe-1m-for-arduino-pi
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/0-96-i2c-blue-oled-display-module-4-pin-ssd1306
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const char* SSID="WIFI", *PASS="PWD", *TOKEN="BOT", *CHAT="CHAT";
const float TARGET = 95.0;   // target meat temp (e.g. brisket)
const int BUZZ = 13;

OneWire bus(4); DallasTemperature ds(&bus);
Adafruit_SSD1306 oled(128, 64, &Wire, -1);
WiFiClientSecure client;
UniversalTelegramBot bot(TOKEN, client);
bool alerted = false;

void setup() {
  Serial.begin(115200); ds.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(BUZZ, OUTPUT);
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
}

void loop() {
  ds.requestTemperatures();
  float t = ds.getTempCByIndex(0);

  oled.clearDisplay(); oled.setTextSize(3); oled.setCursor(0, 8);
  oled.setTextColor(SSD1306_WHITE); oled.print(t, 1);
  oled.setTextSize(1); oled.setCursor(70, 50);
  oled.print(t >= TARGET ? "READY" : "...");
  oled.display();

  if (t >= TARGET && !alerted) {
    bot.sendMessage(CHAT, "🥩 Meat is ready! " + String(t,1) + "C");
    tone(BUZZ, 1500, 500); delay(700);
    tone(BUZZ, 1500, 500);
    alerted = true;
  }
  delay(1000);
}

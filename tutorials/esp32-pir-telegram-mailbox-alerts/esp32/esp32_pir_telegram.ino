// Connects an ESP32 to Wi‑Fi, reads a PIR motion sensor input, and sends a Telegram message when motion is detected (with a one‑minute debounce).
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-pir-telegram-mailbox-alerts
// Parts used: https://shillehtek.com/products/shillehtek-hc-sr501-pir-motion-sensor-module
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/18650-tp4056-1a-3-7-4-2v-lipo-battery-charging-board-micro-usb-with-current-protection
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* SSID = "YOUR_WIFI";
const char* PASS = "YOUR_PASS";
const char* TOKEN = "YOUR_BOT_TOKEN";
const char* CHAT  = "YOUR_CHAT_ID";

WiFiClientSecure client;
UniversalTelegramBot bot(TOKEN, client);
const int PIR = 13;

void setup() {
  pinMode(PIR, INPUT);
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
}
void loop() {
  if (digitalRead(PIR) == HIGH) {
    bot.sendMessage(CHAT, "📬 Mail just arrived!");
    delay(60000);   // debounce - one alert per minute max
  }
  delay(200);
}

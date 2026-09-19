// ESP32 Arduino-framework sketch that connects to Wi‑Fi and the Telegram Bot API to receive commands and control a relay and a local button override (implements setPump and message handling).
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-telegram-bot-relay-pump-control
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/1-channel-5v-relay-module
//             https://shillehtek.com/products/200pcs-6mm-light-touch-button-switch-kit-plastic-box-4-3-5-6-7-8-9-10-12-14-16mm
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>      // "UniversalTelegramBot" by Brian Lough (+ ArduinoJson)
#include <ArduinoJson.h>

const char* SSID = "YourNetwork";
const char* PASS = "YourPassword";
#define BOT_TOKEN "123456789:AAF-your-token-from-BotFather"
#define CHAT_ID   "123456789"           // your numeric chat id: only this chat is obeyed

const int RELAY = 22, BTN = 23;
const int RELAY_ON = LOW;               // most 1-channel modules are active-LOW; use HIGH if yours isn't

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
bool pumpOn = false;
unsigned long offAt = 0;                // millis() when a timed run should stop (0 = no timer)

void setPump(bool on, unsigned long ms = 0) {
  pumpOn = on;
  digitalWrite(RELAY, on ? RELAY_ON : !RELAY_ON);
  offAt = (on && ms) ? millis() + ms : 0;
}

void handleMessages(int n) {
  for (int i = 0; i < n; i++) {
    String chat = bot.messages[i].chat_id, text = bot.messages[i].text;
    if (chat != CHAT_ID) { bot.sendMessage(chat, "Sorry, this bot is private.", ""); continue; }
    if      (text == "/on")     { setPump(true);        bot.sendMessage(chat, "Pump ON", ""); }
    else if (text == "/on10")   { setPump(true, 10000); bot.sendMessage(chat, "Pump ON for 10 s", ""); }
    else if (text == "/on60")   { setPump(true, 60000); bot.sendMessage(chat, "Pump ON for 60 s", ""); }
    else if (text == "/off")    { setPump(false);       bot.sendMessage(chat, "Pump OFF", ""); }
    else if (text == "/status") {
      bot.sendMessage(chat, String("Pump is ") + (pumpOn ? "ON" : "OFF") + (offAt ? " (timed)" : ""), "");
    } else {
      bot.sendMessage(chat, "Commands:\n/on - run\n/on10 - run 10 s\n/on60 - run 60 s\n/off - stop\n/status", "");
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY, OUTPUT); setPump(false);
  pinMode(BTN, INPUT_PULLUP);
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(250);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);    // ships with the library (or client.setInsecure())
  configTime(0, 0, "pool.ntp.org");                // TLS needs the real time
  bot.sendMessage(CHAT_ID, "Pump controller online at " + WiFi.localIP().toString(), "");
}

void loop() {
  static unsigned long lastPoll = 0; static bool btnWas = true;

  if (millis() - lastPoll >= 1000) {                                 // ask Telegram for new messages
    lastPoll = millis();
    int n = bot.getUpdates(bot.last_message_received + 1);
    while (n) { handleMessages(n); n = bot.getUpdates(bot.last_message_received + 1); }
  }

  if (offAt && millis() >= offAt) {                                  // timed run finished
    setPump(false);
    bot.sendMessage(CHAT_ID, "Timer done, pump OFF", "");
  }

  bool btn = digitalRead(BTN);                                       // local override button
  if (!btn && btnWas) {
    setPump(!pumpOn);
    bot.sendMessage(CHAT_ID, pumpOn ? "Button: pump ON" : "Button: pump OFF", "");
    delay(50);
  }
  btnWas = btn;
}

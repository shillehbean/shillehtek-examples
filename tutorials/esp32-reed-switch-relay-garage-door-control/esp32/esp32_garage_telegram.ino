// ESP32 sketch that monitors a reed switch, controls a relay to open/close the garage, and uses UniversalTelegramBot over Wi‑Fi to send state updates and accept /open and /close commands.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-reed-switch-relay-garage-door-control
// Parts used: https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/1-channel-5v-relay-module
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* SSID="WIFI", *PASS="PWD", *TOKEN="BOT", *CHAT="CHAT";
const int REED=13, RELAY=27;
WiFiClientSecure client;
UniversalTelegramBot bot(TOKEN, client);
bool lastDoor = HIGH;

void setup() {
  pinMode(REED, INPUT_PULLUP); pinMode(RELAY, OUTPUT);
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
}

void trigger() { digitalWrite(RELAY, HIGH); delay(500); digitalWrite(RELAY, LOW); }

void loop() {
  bool door = digitalRead(REED);
  if (door != lastDoor) {
    bot.sendMessage(CHAT, door == HIGH ? "🚪 Garage opened" : "🚪 Garage closed");
    lastDoor = door;
  }
  int n = bot.getUpdates(bot.last_message_received + 1);
  for (int i = 0; i < n; i++) {
    if (bot.messages[i].text == "/open" || bot.messages[i].text == "/close") trigger();
  }
  delay(1000);
}

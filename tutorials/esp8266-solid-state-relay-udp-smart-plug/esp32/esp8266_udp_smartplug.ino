// An Arduino-style ESP8266 sketch that connects to Wi-Fi, listens for UDP packets on port 4210, and toggles one of four SSR channels when it receives the characters '1'..'4'.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp8266-solid-state-relay-udp-smart-plug
// Parts used: https://shillehtek.com/products/4-channel-5v-ssr-module-arduino-esp32-raspberry
//             https://shillehtek.com/products/solid-state-relay-1ch-5v-active-low
//             https://shillehtek.com/products/nodemcu-esp8266-development-board-with-0-96-inch-oled-display-type-c-with-soldering-and-foam
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid     = "Your_WIFI";
const char* password = "Your_Password";

WiFiUDP udp;
const int port = 4210;
char packet[16];

const int relayPins[4] = {D1, D2, D5, D6};
bool state[4] = {false, false, false, false};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(250);
  udp.begin(port);
}

void loop() {
  int size = udp.parsePacket();
  if (size) {
    int len = udp.read(packet, 15);
    packet[len] = 0;
    int ch = packet[0] - '1';          // command "1".."4" toggles a channel
    if (ch >= 0 && ch < 4) {
      state[ch] = !state[ch];
      digitalWrite(relayPins[ch], state[ch] ? HIGH : LOW);
    }
  }
}

// Sender sketch; upload separately to the sender board.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-esp-now-dht11-oled
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/shillehtek-dht11-with-cables
//             https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// ================= SENDER (ESP32 + DHT11) =================
#include <WiFi.h>
#include <esp_now.h>
#include <DHT.h>

uint8_t RECEIVER_MAC[] = {0x24, 0x6F, 0x28, 0xAA, 0xBB, 0xCC};   // from Step 2
DHT dht(4, DHT11);

typedef struct { int id; float tempC; float hum; unsigned long count; } Packet;
Packet pkt;

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.mode(WIFI_STA);                              // ESP-NOW needs the radio in station mode
  if (esp_now_init() != ESP_OK) { Serial.println("ESP-NOW init failed"); while (true); }
  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, RECEIVER_MAC, 6);
  peer.channel = 0; peer.encrypt = false;
  esp_now_add_peer(&peer);
}

void loop() {
  pkt.id = 1;
  pkt.tempC = dht.readTemperature();
  pkt.hum   = dht.readHumidity();
  pkt.count++;
  esp_err_t r = esp_now_send(RECEIVER_MAC, (uint8_t*)&pkt, sizeof(pkt));
  Serial.printf("packet %lu: %.1f C  %.0f %%  -> %s\n", pkt.count, pkt.tempC, pkt.hum,
                r == ESP_OK ? "queued" : "send error");
  delay(2000);
}

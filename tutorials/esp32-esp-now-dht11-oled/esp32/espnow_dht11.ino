// ESP32 Arduino sketch that reads temperature and humidity from a DHT11 and sends the data via ESP-NOW to a receiver (the file also includes the start of the receiver OLED code).
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

// ================= RECEIVER (ESP32 + OLED) =================
#include <WiFi.h>
#include <esp_now.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled(128, 64, &Wire, -1);
typedef struct { int id; float tempC; float hum; unsigned long count; } Packet;   // identical struct
Packet pkt;
volatile bool fresh = false;

// ESP32 Arduino core 3.x signature (core 2.x: const uint8_t *mac, const uint8_t *data, int len)
void onRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  if (len == sizeof(pkt)) { memcpy(&pkt, data, sizeof(pkt)); fresh = true; }
}

void setup() {
  Serial.begin(115200);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(SSD1306_WHITE);
  WiFi.mode(WIFI_STA);
  Serial.print("Receiver MAC: "); Serial.println(WiFi.macAddress());   // paste into the sender
  esp_now_init();
  esp_now_register_recv_cb(onRecv);
}

void loop() {
  if (!fresh) return;                               // draw in loop(), not inside the callback
  fresh = false;
  oled.clearDisplay();
  oled.setTextSize(1); oled.setCursor(0, 0);  oled.printf("node %d   pkt %lu", pkt.id, pkt.count);
  oled.setTextSize(2); oled.setCursor(0, 20); oled.printf("%.1f C", pkt.tempC);
  oled.setCursor(0, 44);                      oled.printf("%.0f %%", pkt.hum);
  oled.display();
}

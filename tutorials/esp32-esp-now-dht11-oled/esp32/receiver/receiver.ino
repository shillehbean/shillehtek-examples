// Receiver sketch; upload separately to the receiver board.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-esp-now-dht11-oled
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/shillehtek-dht11-with-cables
//             https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306
// More examples: https://github.com/shillehbean/shillehtek-examples
//

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

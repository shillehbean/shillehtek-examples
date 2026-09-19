// ESP32 Arduino-framework sketch that scans nearby Wi‑Fi networks and draws the results on a 240×240 ST7789 TFT (bar chart or list view with SSID, RSSI, channel, and security).
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-st7789-tft-wifi-scanner
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/tft-lcd-1-3-240x240-st7789-esp32-arduino
//             https://shillehtek.com/products/18650-tp4056-1a-3-7-4-2v-lipo-battery-charging-board-micro-usb-with-current-protection
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

Adafruit_ST7789 tft(-1 /*no CS*/, 2 /*DC*/, 4 /*RST*/);   // hardware SPI: SCK 18, MOSI 23
bool listView = false;

uint16_t colorFor(int rssi) {
  if (rssi > -60) return ST77XX_GREEN;
  if (rssi > -75) return ST77XX_YELLOW;
  return ST77XX_RED;
}

void setup() {
  Serial.begin(115200);
  tft.init(240, 240);                 // blank screen? try tft.init(240, 240, SPI_MODE3)
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();                  // scan works best when not associated
}

void loop() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE); tft.setTextSize(2); tft.setCursor(0, 0);
  tft.print("Scanning...");
  int n = WiFi.scanNetworks();        // blocks for ~2-3 s
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0); tft.printf("%d networks", n);

  if (!listView) {                    // ---- bar chart: strongest 8 ----
    for (int i = 0; i < n && i < 8; i++) {
      int y = 28 + i * 26;
      int w = map(constrain(WiFi.RSSI(i), -95, -35), -95, -35, 4, 236);
      tft.fillRect(0, y, w, 12, colorFor(WiFi.RSSI(i)));
      tft.setTextSize(1); tft.setTextColor(ST77XX_WHITE); tft.setCursor(0, y + 14);
      tft.printf("%-18.18s %d", WiFi.SSID(i).c_str(), WiFi.RSSI(i));
    }
  } else {                            // ---- list: SSID, channel, security ----
    tft.setTextSize(1);
    for (int i = 0; i < n && i < 16; i++) {
      tft.setCursor(0, 24 + i * 13);
      tft.setTextColor(colorFor(WiFi.RSSI(i)));
      tft.printf("%-16.16s ch%2d %s", WiFi.SSID(i).c_str(), WiFi.channel(i),
                 WiFi.encryptionType(i) == WIFI_AUTH_OPEN ? "open" : "lock");
    }
  }
  WiFi.scanDelete();
  listView = !listView;               // alternate views each refresh
  delay(3500);
}

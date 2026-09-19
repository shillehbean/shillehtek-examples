// Connects the ESP32 to Wi-Fi, fetches cryptocurrency prices and 24h change data from the CoinGecko API over HTTPS, parses the JSON response, and prepares values for display on an SSD1306 OLED.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-oled-live-crypto-ticker
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/esp8266-d1-mini-v3-4mb-dev-board-presoldered
//             https://shillehtek.com/products/0-96-i2c-blue-oled-display-module-4-pin-ssd1306
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>                 // D1 Mini: <ESP8266WiFi.h> and <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

const char* SSID = "YourNetwork";
const char* PASS = "YourPassword";
const char* COINS[] = {"bitcoin", "ethereum", "solana", "dogecoin"};   // CoinGecko ids
const char* SYM[]   = {"BTC", "ETH", "SOL", "DOGE"};
const int N = 4;
float price[N], change[N];
bool ok = false;

bool fetchPrices() {
  WiFiClientSecure client; client.setInsecure();        // HTTPS without a stored certificate
  HTTPClient http;
  String url = "https://api.coingecko.com/api/v3/simple/price"
               "?vs_currencies=usd&include_24hr_change=true&ids=";
  for (int i = 0; i < N; i++) { url += COINS[i]; if (i < N - 1) url += ","; }
  http.begin(client, url);
  int code = http.GET();
  if (code != 200) { Serial.println("HTTP " + String(code)); http.end(); return false; }
  JsonDocument doc;
  DeserializationError e = deserializeJson(doc, http.getString());
  http.end();
  if (e) return false;
  for (int i = 0; i < N; i++) {
    price[i]  = doc[COINS[i]]["usd"];
    change[i] = doc[COINS[i]]["usd_24h_change"];
  }
  return true;
}

void show(int i) {
  oled.clearDisplay();
  oled.setTextSize(2); oled.setCursor(0, 0);  oled.print(SYM[i]); oled.print("/USD");
  oled.setCursor(0, 24); oled.print("$");
  if (price[i] >= 1000) oled.print(price[i], 0);        // 64213
  else if (price[i] >= 1) oled.print(price[i], 2);      // 148.20
  else oled.print(price[i], 4);                         // 0.1234
  oled.setTextSize(1); oled.setCursor(0, 52);
  oled.print("24h: "); if (change[i] >= 0) oled.print("+");
  oled.print(change[i], 2); oled.print(" %");
  oled.display();
}

void setup() {
  Serial.begin(115200);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0); oled.print("Connecting..."); oled.display();
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(250);
  ok = fetchPrices();
}

void loop() {
  static unsigned long lastFetch = 0, lastPage = 0; static int i = 0;
  if (millis() - lastFetch >= 60000) { lastFetch = millis(); ok = fetchPrices(); }   // refresh 1/min
  if (millis() - lastPage >= 4000) {                                                 // next coin every 4 s
    lastPage = millis();
    if (ok) { show(i); i = (i + 1) % N; }
    else { oled.clearDisplay(); oled.setTextSize(1); oled.setCursor(0, 0);
           oled.print("API error - retrying"); oled.display(); }
  }
}

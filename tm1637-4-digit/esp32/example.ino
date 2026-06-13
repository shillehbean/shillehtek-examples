// ESP32 example that connects to Wi‑Fi, syncs time via NTP, and displays the current HHMM time on the TM1637 with the colon enabled.
//
// Buy this module: https://shillehtek.com/products/4-bits-tm1637-red-led-display-module-clock
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4-bits-tm1637-red-led-display-module-clock-manual
// More examples: https://github.com/shillehtek/examples
//

// TM1637 4-Digit Display - ESP32 Example (Live Clock from NTP)
// Requires: TM1637 library by Avishay Orpaz + WiFi

#include <WiFi.h>
#include <TM1637Display.h>
#include <time.h>

const char* SSID = "your_ssid";
const char* PASS = "your_password";

const int CLK = 18;
const int DIO = 19;
TM1637Display display(CLK, DIO);

void setup() {
  Serial.begin(115200);
  display.setBrightness(4);
  display.clear();

  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  configTime(0, 0, "pool.ntp.org");
}

void loop() {
  time_t now = time(nullptr);
  struct tm* t = localtime(&now);
  int hhmm = t->tm_hour * 100 + t->tm_min;
  display.showNumberDecEx(hhmm, 0x40, true);  // 0x40 = colon on
  delay(1000);
}

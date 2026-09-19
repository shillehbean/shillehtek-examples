// Connects the WROVER to WiFi, allocates a 2 MB PSRAM buffer, performs an HTTP GET to example.com, copies the response into PSRAM and prints the first line.
//
// Buy this module: https://shillehtek.com/products/esp32-wrover-4mb-psram-wifi-bluetooth-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-wrover-4mb-psram-wifi-bluetooth-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// ESP32-WROVER - download into a PSRAM buffer
// Fill in your WiFi credentials before uploading.

#include <WiFi.h>
#include <HTTPClient.h>

const char *SSID = "YOUR_WIFI";
const char *PASS = "YOUR_PASSWORD";

void setup() {
  Serial.begin(115200);
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) { delay(300); Serial.print("."); }
  Serial.printf("\nConnected: %s\n", WiFi.localIP().toString().c_str());

  // 2MB buffer - impossible on a WROOM, trivial on a WROVER
  size_t cap = 2 * 1024 * 1024;
  uint8_t *buf = (uint8_t *)ps_malloc(cap);
  Serial.printf("PSRAM buffer: %s\n", buf ? "allocated" : "failed");

  HTTPClient http;
  http.begin("http://example.com/");
  int code = http.GET();
  if (code == 200) {
    String body = http.getString();
    size_t n = min((size_t)body.length(), cap);
    memcpy(buf, body.c_str(), n);
    Serial.printf("Fetched %u bytes into PSRAM. First line:\n", n);
    Serial.println(body.substring(0, body.indexOf('\n')));
  } else {
    Serial.printf("HTTP error: %d\n", code);
  }
  http.end();
  free(buf);
}

void loop() {}

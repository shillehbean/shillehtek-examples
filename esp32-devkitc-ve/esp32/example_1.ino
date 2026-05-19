// Checks PSRAM presence and sizes, prints heap/PSRAM stats to Serial, and attempts to allocate a 1 MB buffer in PSRAM to verify it's usable.
//
// Buy this module: https://shillehtek.com/products/esp32-devkitc-ve-8mb-flash-8mb-psram-presoldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-devkitc-ve-8mb-flash-8mb-psram-presoldered-manual
// More examples: https://github.com/shillehtek/examples
//

// ESP32-DevKitC-VE - Confirm PSRAM is detected and usable
// Board: "ESP32 Dev Module"; under Tools -> PSRAM, select "Enabled"

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.print("Free heap:  "); Serial.println(ESP.getFreeHeap());
  Serial.print("Has PSRAM:  "); Serial.println(psramFound() ? "yes" : "no");
  Serial.print("PSRAM size: "); Serial.println(ESP.getPsramSize());
  Serial.print("Free PSRAM: "); Serial.println(ESP.getFreePsram());

  // Allocate a 1 MB buffer in PSRAM
  uint8_t* buf = (uint8_t*) ps_malloc(1024 * 1024);
  if (buf) {
    Serial.println("Allocated 1 MB in PSRAM");
    free(buf);
  } else {
    Serial.println("PSRAM allocation FAILED");
  }
}

void loop() {}

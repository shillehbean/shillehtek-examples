// Uses UART2 on an ESP32 (RXD=16, TXD=17) to parse the HLK-2410B's ASCII status messages and log presence state transitions to Serial.
//
// Buy this module: https://shillehtek.com/products/Arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hlk-2410b-human-presence-radar-motion-detection-module-pre-soldered-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <HardwareSerial.h>

HardwareSerial radar(2);  // UART2

#define RXD2 16
#define TXD2 17

bool present = false;

void setup() {
  Serial.begin(115200);
  radar.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.println("HLK-2410B on ESP32 UART2");
}

void loop() {
  static String buf;
  while (radar.available()) {
    char c = radar.read();
    if (c == '\n' || c == '\r') {
      if (buf.length()) {
        buf.trim();
        bool nowPresent = (buf.indexOf("ON") >= 0);
        if (nowPresent != present) {
          present = nowPresent;
          Serial.printf("Presence -> %s\n", present ? "OCCUPIED" : "VACANT");
        }
        buf = "";
      }
    } else {
      buf += c;
    }
  }
}

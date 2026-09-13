// Reads ASCII lines from the HLK-2410B over SoftwareSerial (D2 RX, D3 TX) and prints occupancy state ('occupied' or 'vacant') to the USB serial console.
//
// Buy this module: https://shillehtek.com/products/Arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hlk-2410b-human-presence-radar-motion-detection-module-pre-soldered-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SoftwareSerial.h>

// HLK-2410B TX -> D2, RX -> D3
SoftwareSerial radar(2, 3);

String line;

void setup() {
  Serial.begin(115200);
  radar.begin(115200);
  Serial.println("HLK-2410B ready");
}

void loop() {
  while (radar.available()) {
    char c = radar.read();
    if (c == '\n' || c == '\r') {
      if (line.length() > 0) {
        line.trim();
        // Sensor emits ASCII status: "ON" when presence detected, "OFF" otherwise
        if (line.indexOf("ON") >= 0) {
          Serial.println("[PRESENCE] occupied");
        } else if (line.indexOf("OFF") >= 0) {
          Serial.println("[PRESENCE] vacant");
        } else {
          Serial.print("[RAW] ");
          Serial.println(line);
        }
        line = "";
      }
    } else {
      line += c;
    }
  }
}

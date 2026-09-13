// Use SoftwareSerial on an Arduino to read LD2410-style frames from the HLK-2410C, parse the footer-delimited frames, and print target state plus moving/static distances to the hardware Serial port.
//
// Buy this module: https://shillehtek.com/products/Arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hlk-2410c-human-presence-radar-motion-detection-module-pre-soldered-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SoftwareSerial.h>

// HLK-2410C TX -> D2, RX -> D3
SoftwareSerial radar(2, 3);

// Frame header / footer bytes from the LD2410 protocol
const uint8_t HEADER[4] = {0xF4, 0xF3, 0xF2, 0xF1};
const uint8_t FOOTER[4] = {0xF8, 0xF7, 0xF6, 0xF5};

uint8_t buf[64];
uint8_t idx = 0;

void setup() {
  Serial.begin(115200);
  radar.begin(256000);  // Default baud
  Serial.println("HLK-2410C ready");
}

void loop() {
  while (radar.available()) {
    uint8_t b = radar.read();
    if (idx < sizeof(buf)) buf[idx++] = b;

    // Look for footer
    if (idx >= 4 &&
        buf[idx-4] == FOOTER[0] && buf[idx-3] == FOOTER[1] &&
        buf[idx-2] == FOOTER[2] && buf[idx-1] == FOOTER[3]) {

      // Target state at byte 8: 0=none, 1=moving, 2=static, 3=both
      uint8_t state = buf[8];
      uint16_t moveDist  = buf[9]  | (buf[10] << 8);
      uint16_t staticDist = buf[12] | (buf[13] << 8);

      Serial.print("State: "); Serial.print(state);
      Serial.print("  Moving: "); Serial.print(moveDist);
      Serial.print("cm  Static: "); Serial.print(staticDist);
      Serial.println("cm");

      idx = 0;
    }
  }
}

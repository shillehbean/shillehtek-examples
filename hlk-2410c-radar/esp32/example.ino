// Use ESP32's UART2 to receive frames from the HLK-2410C, detect the frame footer, extract state and distance fields (moving, static, detect) and log them over USB Serial.
//
// Buy this module: https://shillehtek.com/products/Arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hlk-2410c-human-presence-radar-motion-detection-module-pre-soldered-manual
// More examples: https://github.com/shillehtek/examples
//

#include <HardwareSerial.h>

HardwareSerial radar(2);  // UART2

#define RXD2 16
#define TXD2 17

void setup() {
  Serial.begin(115200);
  radar.begin(256000, SERIAL_8N1, RXD2, TXD2);
  Serial.println("HLK-2410C on ESP32 UART2");
}

void loop() {
  static uint8_t buf[64];
  static uint8_t idx = 0;

  while (radar.available()) {
    uint8_t b = radar.read();
    if (idx < sizeof(buf)) buf[idx++] = b;

    if (idx >= 4 &&
        buf[idx-4] == 0xF8 && buf[idx-3] == 0xF7 &&
        buf[idx-2] == 0xF6 && buf[idx-1] == 0xF5) {

      uint8_t state = buf[8];
      uint16_t moveDist  = buf[9]  | (buf[10] << 8);
      uint16_t staticDist = buf[12] | (buf[13] << 8);
      uint16_t detectDist = buf[15] | (buf[16] << 8);

      Serial.printf("State=%u  Move=%ucm  Static=%ucm  Detect=%ucm\n",
                    state, moveDist, staticDist, detectDist);
      idx = 0;
    }
  }
}

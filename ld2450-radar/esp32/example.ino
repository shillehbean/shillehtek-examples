// ESP32 Arduino code using HardwareSerial(2) on pins 16/17 to read the radar at 256000 baud, parse valid frames, decode three tracked targets, and print formatted position/speed/distance lines.
//
// Buy this module: https://shillehtek.com/products/24GHz
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hlk-ld2450-24ghz-mmwave-radar-human-body-tracking-sensor-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// HLK-LD2450 on ESP32 - 3-target position reader
#include <HardwareSerial.h>
HardwareSerial Radar(2);

uint8_t buf[64];
int idx = 0;

int16_t decode(uint8_t lo, uint8_t hi) {
  int16_t v = (int16_t)(((uint16_t)hi << 8) | lo) & 0x7FFF;
  return (hi & 0x80) ? v : -v;
}

void setup() {
  Serial.begin(115200);
  Radar.begin(256000, SERIAL_8N1, 16, 17);
  Serial.println("LD2450 ESP32 reader ready");
}

void loop() {
  while (Radar.available()) {
    buf[idx++] = Radar.read();
    if (idx >= 30) {
      if (buf[0] == 0xAA && buf[1] == 0xFF &&
          buf[28] == 0x55 && buf[29] == 0xCC) {
        for (int t = 0; t < 3; t++) {
          int o = 4 + t * 8;
          int16_t x = decode(buf[o], buf[o + 1]);
          int16_t y = decode(buf[o + 2], buf[o + 3]);
          int16_t spd = decode(buf[o + 4], buf[o + 5]);
          uint16_t dist = buf[o + 6] | (buf[o + 7] << 8);
          if (x || y || dist) {
            Serial.printf("T%d  x=%d mm  y=%d mm  spd=%d cm/s  dist=%u\n",
                          t + 1, x, y, spd, dist);
          }
        }
        idx = 0;
      } else {
        memmove(buf, buf + 1, idx - 1);
        idx--;
      }
    }
    if (idx >= (int)sizeof(buf)) idx = 0;
  }
}

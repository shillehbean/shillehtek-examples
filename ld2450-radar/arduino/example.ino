// Arduino Mega sketch that reads the HLK-LD2450 on Serial1 (pins 18/19) at 256000 baud, parses 30-byte frames, decodes three targets, and prints x/y, speed, and distance values to Serial.
//
// Buy this module: https://shillehtek.com/products/24GHz
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hlk-ld2450-24ghz-mmwave-radar-human-body-tracking-sensor-module-manual
// More examples: https://github.com/shillehtek/examples
//

// HLK-LD2450 reader for Arduino Mega
// Connect radar TX -> Mega RX1 (pin 19), RX -> Mega TX1 (pin 18)
// Frame: AA FF 03 00 [T1 8B][T2 8B][T3 8B] 55 CC  (30 bytes total)

uint8_t buf[64];
int idx = 0;

int16_t decode(uint8_t lo, uint8_t hi) {
  // Sign bit is the high bit of the high byte; value is the rest
  int16_t v = (int16_t)(((uint16_t)hi << 8) | lo) & 0x7FFF;
  return (hi & 0x80) ? v : -v;
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(256000);
  Serial.println("LD2450 ready");
}

void loop() {
  while (Serial1.available()) {
    uint8_t b = Serial1.read();
    buf[idx++] = b;

    if (idx >= 30) {
      if (buf[0] == 0xAA && buf[1] == 0xFF &&
          buf[28] == 0x55 && buf[29] == 0xCC) {
        for (int t = 0; t < 3; t++) {
          int o = 4 + t * 8;
          int16_t x = decode(buf[o + 0], buf[o + 1]);
          int16_t y = decode(buf[o + 2], buf[o + 3]);
          int16_t spd = decode(buf[o + 4], buf[o + 5]);
          uint16_t dist = buf[o + 6] | (buf[o + 7] << 8);
          if (x || y || dist) {
            Serial.print("T"); Serial.print(t + 1);
            Serial.print(" x="); Serial.print(x);
            Serial.print("mm y="); Serial.print(y);
            Serial.print("mm spd="); Serial.print(spd);
            Serial.print("cm/s dist="); Serial.println(dist);
          }
        }
        Serial.println();
        idx = 0;
      } else {
        // Slide window by one byte to re-sync
        memmove(buf, buf + 1, idx - 1);
        idx--;
      }
    }
    if (idx >= (int)sizeof(buf)) idx = 0;
  }
}

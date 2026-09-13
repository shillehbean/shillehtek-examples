// Runs on an ESP32 to send configuration commands to the LD1125H over UART and read ASCII status frames, printing MOVING/STATIC with measured distance.
//
// Buy this module: https://shillehtek.com/products/24GHz
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ld1125h-24ghz-mmwave-human-presence-radar-sensor-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// LD1125H on ESP32 - ASCII reader + config helper
#include <HardwareSerial.h>
HardwareSerial RadarSerial(2);

String line;

void sendCmd(const String &cmd) {
  RadarSerial.print(cmd);
  RadarSerial.print("\r\n");
}

void setup() {
  Serial.begin(115200);
  RadarSerial.begin(115200, SERIAL_8N1, 16, 17);
  delay(500);
  // Example config: 6 m max, moderate sensitivity
  sendCmd("rmax=6");
  sendCmd("mth1=80");
  sendCmd("mth2=50");
  sendCmd("mth3=30");
  sendCmd("save");
  Serial.println("LD1125H ESP32 reader ready");
}

void loop() {
  while (RadarSerial.available()) {
    char c = RadarSerial.read();
    if (c == '\n') {
      line.trim();
      if (line.length()) {
        bool moving = line.startsWith("mov");
        bool stat   = line.startsWith("occ");
        int eq = line.indexOf('=');
        float d = (eq > 0) ? line.substring(eq + 1).toFloat() : -1;
        if (moving)      Serial.printf("MOVING  %.2f m\n", d);
        else if (stat)   Serial.printf("STATIC  %.2f m\n", d);
        else             Serial.println(line);
      }
      line = "";
    } else if (c != '\r') {
      line += c;
    }
  }
}

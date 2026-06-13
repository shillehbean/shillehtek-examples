// Reads ASCII frames from the LD1125H over SoftwareSerial on an Arduino Uno and prints motion (MOVING/STATIC) and distance in meters to the USB serial console.
//
// Buy this module: https://shillehtek.com/products/24GHz
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ld1125h-24ghz-mmwave-human-presence-radar-sensor-module-manual
// More examples: https://github.com/shillehtek/examples
//

// LD1125H ASCII reader for Arduino Uno
// Wiring: UTX->D2, URX->D3, VCC->5V, GND->GND
// Frames look like:   mov, dis=1.23   or   occ, dis=0.85

#include <SoftwareSerial.h>
SoftwareSerial RadarSerial(2, 3); // RX, TX

String line;

void setup() {
  Serial.begin(115200);
  RadarSerial.begin(115200);
  Serial.println("LD1125H reader ready");
}

void loop() {
  while (RadarSerial.available()) {
    char c = RadarSerial.read();
    if (c == '\n') {
      line.trim();
      if (line.length()) {
        if (line.startsWith("mov")) {
          Serial.print("MOVING  ");
        } else if (line.startsWith("occ")) {
          Serial.print("STATIC  ");
        } else {
          Serial.print(line);
          Serial.println();
          line = "";
          continue;
        }
        int eq = line.indexOf('=');
        if (eq > 0) Serial.print(line.substring(eq + 1));
        Serial.println(" m");
      }
      line = "";
    } else if (c != '\r') {
      line += c;
    }
  }
}

// Reads CAN frames from an MCP2515 via SPI and prints message ID, length, and data bytes to Serial (suitable for capturing raw OBD-II frames).
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-mcp2515-can-bus-read-obd2-frames
// Parts used: https://shillehtek.com/products/mcp2515-can-bus-module-tja1050-receiver-spi
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SPI.h>
#include <mcp_can.h>

const int CS  = 10;
const int INT_PIN = 2;
MCP_CAN can(CS);

void setup() {
  Serial.begin(115200);
  while (can.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) != CAN_OK) {
    Serial.println("MCP2515 init failed, retrying...");
    delay(500);
  }
  can.setMode(MCP_NORMAL);
  pinMode(INT_PIN, INPUT);
  Serial.println("CAN bus listening...");
}

void loop() {
  if (!digitalRead(INT_PIN)) {
    long unsigned id;
    byte len, buf[8];
    can.readMsgBuf(&id, &len, buf);
    Serial.print("ID="); Serial.print(id, HEX);
    Serial.print(" LEN="); Serial.print(len);
    Serial.print(" DATA=");
    for (byte i = 0; i < len; i++) {
      if (buf[i] < 0x10) Serial.print('0');
      Serial.print(buf[i], HEX);
      Serial.print(' ');
    }
    Serial.println();
  }
}

// Initializes the MCP2515 at 500 kbps over SPI and transmits an 8-byte CAN frame (ID 0x100) once per second, reporting success to Serial.
//
// Buy this module: https://shillehtek.com/products/mcp2515-can-bus-module-tja1050-receiver-spi
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mcp2515-can-bus-module-tja1050-receiver-spi-manual
// More examples: https://github.com/shillehtek/examples
//

#include <SPI.h>
#include <mcp_can.h>

MCP_CAN CAN(10);  // CS

void setup() {
  Serial.begin(115200);
  while (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) != CAN_OK) {
    Serial.println("CAN init fail; retrying");
    delay(100);
  }
  CAN.setMode(MCP_NORMAL);
  Serial.println("CAN init ok");
}

void loop() {
  unsigned char data[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0x00, 0x00};
  byte sndStat = CAN.sendMsgBuf(0x100, 0, 8, data);
  Serial.println(sndStat == CAN_OK ? "sent" : "fail");
  delay(1000);
}

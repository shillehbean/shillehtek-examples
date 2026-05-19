// Initializes the MCP2515 and polls for incoming CAN frames, printing the received message ID and payload bytes to Serial when a frame arrives.
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
    delay(100);
  }
  CAN.setMode(MCP_NORMAL);
}

void loop() {
  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    long unsigned int rxId;
    unsigned char len, buf[8];
    CAN.readMsgBuf(&rxId, &len, buf);
    Serial.print("ID: 0x"); Serial.print(rxId, HEX);
    Serial.print("  data:");
    for (int i = 0; i < len; i++) {
      Serial.print(' '); Serial.print(buf[i], HEX);
    }
    Serial.println();
  }
}

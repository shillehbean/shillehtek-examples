// Bridge serial data between the ESP32 and a 5V UART device using UART2 and the TXS0108E to translate TX/RX voltage levels in both directions.
//
// Buy this module: https://shillehtek.com/products/shillehtek-pre-soldered-txs0108e-high-speed-full-duplex-8-channel-logic-level-bi-directional-converter
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-pre-soldered-txs0108e-high-speed-full-duplex-8-channel-logic-level-bi-directional-converter-manual
// More examples: https://github.com/shillehtek/examples
//

// TXS0108E - Talk to a 5V serial device from a 3.3V ESP32
// ESP32 TX (GPIO 17) -> A1, A2 <- ESP32 RX (GPIO 16)
// B1 -> 5V device RX, B2 <- 5V device TX
// VA = 3.3V, VB = 5V, OE = 3.3V

#include 

HardwareSerial Serial5V(2);  // UART2 on ESP32

void setup() {
  Serial.begin(115200);
  Serial5V.begin(9600, SERIAL_8N1, 16, 17);
  Serial.println("TXS0108E serial bridge ready");
}

void loop() {
  if (Serial.available()) {
    Serial5V.write(Serial.read());
  }
  if (Serial5V.available()) {
    Serial.write(Serial5V.read());
  }
}

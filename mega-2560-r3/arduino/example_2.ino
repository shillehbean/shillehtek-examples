// Bridges data between the USB Serial Monitor (Serial) and the board's hardware UART Serial1 (pins RX1=19, TX1=18), allowing passthrough to devices like GPS or Bluetooth modules.
//
// Buy this module: https://shillehtek.com/products/mega-2560-r3-ch340-arduino-board
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mega-2560-r3-ch340-arduino-board-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// The Mega's signature feature: 4 hardware UARTs.
// This sketch bridges a device on Serial1 (RX1=19, TX1=18)
// to the USB Serial Monitor - ideal for GPS or Bluetooth modules.

void setup() {
  Serial.begin(9600);    // USB serial monitor
  Serial1.begin(9600);   // device on pins 19 (RX1) and 18 (TX1)
  Serial.println("Serial1 bridge ready");
}

void loop() {
  // Forward device -> monitor
  if (Serial1.available()) {
    Serial.write(Serial1.read());
  }
  // Forward monitor -> device
  if (Serial.available()) {
    Serial1.write(Serial.read());
  }
}

// Initializes the SX1262 LoRa radio using RadioLib on Heltec V3 pin mapping and demonstrates sending a transmit packet and waiting for a received packet with a 5s timeout.
//
// Buy this module: https://shillehtek.com/products/sx1262-esp32-s3-0-96-inch-blue-oled-display-bluetooth-wifi-kit-32-module-iot-development-board-for-arduino-w-antenna-868-915mhz-with-soldering-and-foam
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/sx1262-esp32-s3-0-96-inch-blue-oled-display-bluetooth-wifi-kit-32-module-iot-development-board-for-arduino-w-antenna-868-915mhz-with-soldering-and-foam-manual
// More examples: https://github.com/shillehtek/examples
//

// Heltec WiFi LoRa 32 V3 - send and receive
// Library: RadioLib by jgromes

#include <RadioLib.h>

// SX1262 mapping for V3: NSS=8, DIO1=14, RST=12, BUSY=13
SX1262 lora = new Module(8, 14, 12, 13);

void setup() {
  Serial.begin(115200);
  int state = lora.begin(915.0);   // 868.0 in EU
  if (state != RADIOLIB_ERR_NONE) {
    Serial.printf("LoRa init failed: %d\n", state);
    while (true) delay(10);
  }
  Serial.println("LoRa ready");
}

void loop() {
  // TX:
  int s = lora.transmit("Hello from V3!");
  Serial.println(s == RADIOLIB_ERR_NONE ? "Sent OK" : "Send failed");

  // RX (blocking, 5s timeout):
  String msg;
  s = lora.receive(msg, 5000);
  if (s == RADIOLIB_ERR_NONE) {
    Serial.print("Got: "); Serial.println(msg);
  }
  delay(2000);
}

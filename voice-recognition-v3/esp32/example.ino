// Talks to the module using ESP32 UART2 with a raw command frame to load trained records and parses incoming frames to detect when a voice command (record number) is recognized.
//
// Buy this module: https://shillehtek.com/products/arduino-voice-recognition-module-v3
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-voice-recognition-module-v3-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Voice Recognition Module V3 - ESP32 Example (raw protocol)
// Module TXD -> GPIO 16 via divider, Module RXD -> GPIO 17, VCC -> VIN
// Train the records first using an Arduino and the Elechouse library -
// the voiceprints stay stored on the module.

HardwareSerial vrSerial(2);  // UART2

void loadRecord(uint8_t rec) {
  // Frame: AA | LEN | 30 (load) | record | 0A
  uint8_t cmd[5] = {0xAA, 0x02, 0x30, rec, 0x0A};
  cmd[1] = 2;  // LEN = command + data bytes
  vrSerial.write(cmd, 5);
  delay(50);
}

void setup() {
  Serial.begin(115200);
  vrSerial.begin(9600, SERIAL_8N1, 16, 17);
  delay(500);

  // Load trained records 0-2 into the recognizer
  loadRecord(0);
  loadRecord(1);
  loadRecord(2);

  Serial.println("Speak one of your trained commands...");
}

void loop() {
  // Recognition frames arrive as: AA | LEN | 0D | data... | 0A
  static uint8_t frame[32];
  static int pos = -1;

  while (vrSerial.available()) {
    uint8_t b = vrSerial.read();

    if (pos < 0) {
      if (b == 0xAA) { pos = 0; frame[pos++] = b; }
    } else {
      frame[pos++] = b;
      if (b == 0x0A || pos >= 32) {
        // frame[2] = 0x0D means "voice recognized";
        // frame[4] holds the record number
        if (pos > 5 && frame[2] == 0x0D) {
          Serial.printf("Recognized record #%d\n", frame[4]);
        }
        pos = -1;
      }
    }
  }
}

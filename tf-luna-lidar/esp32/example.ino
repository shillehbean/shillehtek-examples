// Arduino/ESP32 sketch that reads TF-Luna 9-byte UART frames on Serial2 (or SoftwareSerial on AVR) and decodes distance/strength/temperature for periodic reporting.
//
// Buy this module: https://shillehtek.com/products/lidar-tf-luna-single-module-8m
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/lidar-tf-luna-single-module-8m-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// TF-Luna LiDAR - read distance frames over UART (115200 baud)
// Uno/Nano: TF-Luna TXD (pin 3) -> D2. Leave RXD (pin 2) unconnected for reading.
// ESP32:    TF-Luna TXD (pin 3) -> GPIO 16, RXD (pin 2) -> GPIO 17
#if defined(ESP32)
  #define LIDAR Serial2
#else
  #include <SoftwareSerial.h>
  SoftwareSerial lidarPort(2, 3);   // RX = D2, TX = D3 (TX is not wired)
  #define LIDAR lidarPort
#endif

uint8_t frame[9];
unsigned long lastPrint = 0;

void setup() {
  Serial.begin(115200);
#if defined(ESP32)
  Serial2.begin(115200, SERIAL_8N1, 16, 17);   // RX = GPIO 16, TX = GPIO 17
#else
  lidarPort.begin(115200);
#endif
}

// Returns true when frame[] holds a complete 9-byte frame with a valid checksum
bool readFrame() {
  while (LIDAR.available() >= 9) {
    if (LIDAR.read() != 0x59) continue;        // first header byte
    if (LIDAR.peek() != 0x59) continue;        // second header byte
    frame[0] = 0x59;
    for (uint8_t i = 1; i < 9; i++) frame[i] = LIDAR.read();
    uint8_t sum = 0;
    for (uint8_t i = 0; i < 8; i++) sum += frame[i];
    if (sum == frame[8]) return true;
  }
  return false;
}

void loop() {
  if (!readFrame()) return;
  if (millis() - lastPrint < 100) return;      // print 10 readings per second
  lastPrint = millis();

  uint16_t distance = frame[2] | (frame[3] << 8);   // centimeters
  uint16_t strength = frame[4] | (frame[5] << 8);
  float tempC = (frame[6] | (frame[7] << 8)) / 8.0 - 256.0;

  if (strength < 100 || strength == 65535) {
    Serial.println("Signal unreliable - target too far, too dark, or overexposed");
  } else {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm   Strength: ");
    Serial.print(strength);
    Serial.print("   Chip temp: ");
    Serial.print(tempC, 1);
    Serial.println(" C");
  }
}

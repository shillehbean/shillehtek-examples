// Read 19‑byte UART RVC frames from the BNO085 on an Arduino Uno/Nano, validate the checksum and parse the frame contents for periodic printing.
//
// Buy this module: https://shillehtek.com/products/bno085-imu-pre-soldered-orientation-sensor
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/bno085-imu-pre-soldered-orientation-sensor-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// BNO085 (GY-BNO08X) in UART-RVC mode on an Arduino Uno or Nano - no library needed
// Wiring: VCC -> 3.3V, GND -> GND, PS0 -> 3.3V, SDA pin (data out) -> RX0 (pin 0)
// Unplug the wire from pin 0 while uploading, then reconnect it.
// The sensor sends a 19-byte frame 100 times per second at 115200 baud.

uint8_t frame[17];            // everything after the two 0xAA header bytes
unsigned long lastPrint = 0;

int16_t toInt16(uint8_t low, uint8_t high) {
  return (int16_t)(((uint16_t)high << 8) | low);
}

void setup() {
  Serial.begin(115200);       // RX listens to the sensor, TX prints to the Serial Monitor
}

// Returns true when frame[] holds a complete frame with a valid checksum
bool readFrame() {
  while (Serial.available() >= 19) {
    if (Serial.read() != 0xAA) continue;       // first header byte
    if (Serial.peek() != 0xAA) continue;       // second header byte
    Serial.read();
    for (uint8_t i = 0; i < 17; i++) frame[i] = Serial.read();
    uint8_t sum = 0;
    for (uint8_t i = 0; i < 16; i++) sum += frame[i];
    if (sum == frame[16]) return true;
  }
  return false;
}

void loop() {
  if (!readFrame()) return;
  if (millis() - lastPrint < 100) return;      // print 10 times per second
  lastPrint = millis();

  float yaw   = toInt16(frame[1], frame[2]) * 0.01;   // degrees
  float pitch = toInt16(frame[3], frame[4]) * 0.01;
  float roll  = toInt16(frame[5], frame[6]) * 0.01;

  Serial.print("Yaw: ");
  Serial.print(yaw, 2);
  Serial.print("   Pitch: ");
  Serial.print(pitch, 2);
  Serial.print("   Roll: ");
  Serial.println(roll, 2);
}

// Uses ESP32 UART2 on GPIO16/17 to send the MH-Z19C read command, validate the response checksum, and print the measured CO2 ppm to Serial every 5 seconds.
//
// Buy this module: https://shillehtek.com/products/co2-sensor-mh-z19c-ndir-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/co2-sensor-mh-z19c-ndir-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MH-Z19C CO2 Sensor - ESP32 Example (raw UART protocol)
// Sensor Tx -> GPIO 16 (RX2), Sensor Rx -> GPIO 17 (TX2), Vin -> VIN (5V)

HardwareSerial co2Serial(2);  // UART2

const uint8_t readCmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};

void setup() {
  Serial.begin(115200);
  co2Serial.begin(9600, SERIAL_8N1, 16, 17);  // baud, config, RX, TX
  Serial.println("Warming up (about 60 s after power-on)...");
}

void loop() {
  uint8_t response[9];

  co2Serial.flush();
  while (co2Serial.available()) co2Serial.read();  // clear stale bytes

  co2Serial.write(readCmd, 9);
  co2Serial.setTimeout(500);

  if (co2Serial.readBytes(response, 9) == 9 &&
      response[0] == 0xFF && response[1] == 0x86) {

    uint8_t checksum = 0;
    for (int i = 1; i < 8; i++) checksum += response[i];
    checksum = 0xFF - checksum + 1;

    if (checksum == response[8]) {
      int ppm = response[2] * 256 + response[3];
      Serial.printf("CO2: %d ppm\n", ppm);
    }
  } else {
    Serial.println("No response - check wiring and 5V supply");
  }

  delay(5000);
}

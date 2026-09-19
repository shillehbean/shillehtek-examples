// ESP32 telemetry sender that transmits a periodic labeled reading over HC-12 using Serial2 (RX=GPIO16, TX=GPIO17) and prints any returned data.
//
// Buy this module: https://shillehtek.com/products/hc-12-433mhz-serial-transceiver-si4438-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hc-12-433mhz-serial-transceiver-si4438-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// HC-12 - ESP32 telemetry sender (UART2)
// TXD->GPIO16, RXD->GPIO17

unsigned long counter = 0;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);   // RX=16, TX=17
  Serial.println("HC-12 telemetry sender");
}

void loop() {
  // Send a labeled reading once a second (replace with real sensor data)
  float fakeTemp = 20.0 + (millis() % 10000) / 1000.0;
  Serial2.printf("NODE1,%lu,%.2f\n", counter++, fakeTemp);
  Serial.printf("sent NODE1,%lu,%.2f\n", counter - 1, fakeTemp);

  // print anything that comes back
  while (Serial2.available()) Serial.write(Serial2.read());
  delay(1000);
}

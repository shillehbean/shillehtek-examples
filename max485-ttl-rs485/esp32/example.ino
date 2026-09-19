// Uses ESP32 hardware UART2 (RX=16, TX=17) with a direction pin on GPIO4 to transmit a counter message over RS‑485, then switch to receive and print incoming lines to the USB Serial.
//
// Buy this module: https://shillehtek.com/products/max485-ttl-rs485-converter-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max485-ttl-rs485-converter-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MAX485 RS-485 - ESP32 Example (hardware UART2)
// RO->GPIO16, DI->GPIO17, RE+DE->GPIO4

const int DIR_PIN = 4;
unsigned long counter = 0;

void setTransmit(bool tx) {
  digitalWrite(DIR_PIN, tx ? HIGH : LOW);
  delayMicroseconds(50);
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);   // RX=16, TX=17
  pinMode(DIR_PIN, OUTPUT);
  setTransmit(false);
  Serial.println("RS-485 node ready");
}

void loop() {
  setTransmit(true);
  Serial2.printf("ESP32 MSG %lu\n", counter++);
  Serial2.flush();
  setTransmit(false);

  unsigned long t0 = millis();
  while (millis() - t0 < 1000) {
    if (Serial2.available()) {
      String line = Serial2.readStringUntil('\n');
      Serial.print("Received: ");
      Serial.println(line);
    }
  }
}

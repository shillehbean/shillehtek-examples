// Uses SoftwareSerial on pins D10/D11 and a direction pin on D3 to send an incrementing "MSG" line over RS‑485 then switch to receive mode and print any replies to the USB Serial.
//
// Buy this module: https://shillehtek.com/products/max485-ttl-rs485-converter-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max485-ttl-rs485-converter-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MAX485 RS-485 - Arduino Example (sender + listener)
// RO->D10, DI->D11, RE+DE->D3, VCC->5V

#include <SoftwareSerial.h>

const int DIR_PIN = 3;                  // HIGH = TX, LOW = RX
SoftwareSerial rs485(10, 11);           // RX, TX
unsigned long counter = 0;

void setTransmit(bool tx) {
  digitalWrite(DIR_PIN, tx ? HIGH : LOW);
  delayMicroseconds(50);                // let the driver settle
}

void setup() {
  Serial.begin(115200);
  rs485.begin(9600);
  pinMode(DIR_PIN, OUTPUT);
  setTransmit(false);
  Serial.println("RS-485 node ready");
}

void loop() {
  // --- send one message ---
  setTransmit(true);
  rs485.print("MSG ");
  rs485.println(counter++);
  rs485.flush();                        // wait until fully shifted out
  setTransmit(false);

  // --- listen for replies for 1 second ---
  unsigned long t0 = millis();
  while (millis() - t0 < 1000) {
    if (rs485.available()) {
      String line = rs485.readStringUntil('\n');
      Serial.print("Received: ");
      Serial.println(line);
    }
  }
}

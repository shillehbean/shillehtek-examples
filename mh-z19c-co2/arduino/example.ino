// Sends the MH-Z19C raw UART read command over SoftwareSerial (pins D2/D3), verifies the response checksum, and prints the CO2 concentration in ppm to the USB Serial console.
//
// Buy this module: https://shillehtek.com/products/co2-sensor-mh-z19c-ndir-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/co2-sensor-mh-z19c-ndir-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MH-Z19C CO2 Sensor - Arduino Example (raw UART protocol)
// Sensor Tx -> D2, Sensor Rx -> D3 (via divider), Vin -> 5V, GND -> GND

#include <SoftwareSerial.h>

SoftwareSerial co2Serial(2, 3);  // RX = D2 (from sensor Tx), TX = D3

// Command: read CO2 concentration
const byte readCmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};

void setup() {
  Serial.begin(9600);
  co2Serial.begin(9600);   // MH-Z19C fixed baud rate
  Serial.println("Warming up (about 60 s after power-on)...");
}

void loop() {
  byte response[9];

  co2Serial.write(readCmd, 9);
  co2Serial.setTimeout(500);

  if (co2Serial.readBytes(response, 9) == 9 &&
      response[0] == 0xFF && response[1] == 0x86) {

    // Verify the checksum before trusting the data
    byte checksum = 0;
    for (int i = 1; i < 8; i++) checksum += response[i];
    checksum = 0xFF - checksum + 1;

    if (checksum == response[8]) {
      int ppm = response[2] * 256 + response[3];
      Serial.print("CO2: ");
      Serial.print(ppm);
      Serial.println(" ppm");
    } else {
      Serial.println("Checksum error - reading discarded");
    }
  } else {
    Serial.println("No response - check wiring and 5V supply");
  }

  delay(5000);  // The sensor updates slowly; 5 s polling is plenty
}

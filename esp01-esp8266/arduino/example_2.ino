// Sends AT commands to set the ESP-01 to station mode and join a specified Wi‑Fi network, then queries and prints the module's IP address.
//
// Buy this module: https://shillehtek.com/products/esp8266-esp-01-serial-wifi-module-1mb-wireless-transceiver-iot
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp8266-esp-01-serial-wifi-module-1mb-wireless-transceiver-iot-manual
// More examples: https://github.com/shillehtek/examples
//

// Arduino - join a Wi-Fi network using ESP-01 AT commands

#include <SoftwareSerial.h>

SoftwareSerial esp(2, 3);

void send(const char* cmd, unsigned long ms = 2000) {
  Serial.print("> "); Serial.println(cmd);
  esp.println(cmd);
  unsigned long start = millis();
  while (millis() - start < ms) {
    while (esp.available()) Serial.write(esp.read());
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  esp.begin(9600);
  delay(500);
  send("AT");
  send("AT+CWMODE=1");                                   // station mode
  send("AT+CWJAP=\"YOUR_SSID\",\"YOUR_PASSWORD\"", 8000); // join network
  send("AT+CIFSR");                                      // print IP
}

void loop() {}

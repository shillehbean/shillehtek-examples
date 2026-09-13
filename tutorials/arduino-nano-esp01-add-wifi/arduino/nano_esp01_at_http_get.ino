// Uses SoftwareSerial to send AT commands to an ESP‑01 to join a Wi‑Fi network, start a TCP connection to example.com, perform an HTTP GET request, and print the module's responses to the hardware Serial port.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-esp01-add-wifi
// Parts used: https://shillehtek.com/products/esp8266-esp-01-serial-wifi-module-1mb-wireless-transceiver-iot
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SoftwareSerial.h>

SoftwareSerial esp(2, 3);   // RX, TX

void sendAT(const char* cmd, int waitMs = 1500) {
  esp.println(cmd);
  long t = millis();
  while (millis() - t < waitMs) {
    while (esp.available()) Serial.write(esp.read());
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  esp.begin(9600);

  sendAT("AT");                          // sanity
  sendAT("AT+CWMODE=1");                 // station mode
  sendAT("AT+CWJAP=\"your-ssid\",\"your-password\"", 8000);
  sendAT("AT+CIFSR");                    // print IP

  sendAT("AT+CIPSTART=\"TCP\",\"example.com\",80", 4000);
  esp.println("AT+CIPSEND=44");
  delay(500);
  esp.println("GET / HTTP/1.1\r\nHost: example.com\r\n\r\n");
  delay(3000);
  while (esp.available()) Serial.write(esp.read());
}

void loop() {}

// Uses AT commands to open a TCP connection to example.com and perform a simple HTTP GET request, printing the server response.
//
// Buy this module: https://shillehtek.com/products/esp8266-esp-01-serial-wifi-module-1mb-wireless-transceiver-iot
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp8266-esp-01-serial-wifi-module-1mb-wireless-transceiver-iot-manual
// More examples: https://github.com/shillehtek/examples
//

// Arduino - simple HTTP GET via ESP-01 AT commands
// Assumes the ESP-01 is already joined to Wi-Fi

#include <SoftwareSerial.h>
SoftwareSerial esp(2, 3);

void send(const String &cmd, unsigned long ms = 2000) {
  esp.println(cmd);
  unsigned long start = millis();
  while (millis() - start < ms) {
    while (esp.available()) Serial.write(esp.read());
  }
}

void setup() {
  Serial.begin(9600);
  esp.begin(9600);
  delay(500);

  send("AT+CIPSTART=\"TCP\",\"example.com\",80", 4000);

  String req = "GET / HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n";
  send("AT+CIPSEND=" + String(req.length()), 1000);
  send(req, 4000);
  send("AT+CIPCLOSE");
}

void loop() {}

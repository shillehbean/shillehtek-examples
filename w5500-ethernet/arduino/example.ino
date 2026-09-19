// Arduino example that obtains an IP via DHCP and performs a simple HTTP GET to example.com, printing the response over Serial.
//
// Buy this module: https://shillehtek.com/products/w5500-spi-ethernet-module-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/w5500-spi-ethernet-module-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// W5500 Ethernet - Arduino Web Client (DHCP)
// SCLK->13, MISO->12, MOSI->11, SCS->10, 5V, GND
// Library: "Ethernet" (built into the IDE)

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 };  // pick any unique MAC
EthernetClient client;

void setup() {
  Serial.begin(115200);
  Ethernet.init(10);                       // CS pin

  Serial.println("Requesting IP via DHCP...");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("DHCP failed - check cable/router");
    while (1);
  }
  Serial.print("IP address: ");
  Serial.println(Ethernet.localIP());

  if (client.connect("example.com", 80)) {
    client.println("GET / HTTP/1.1");
    client.println("Host: example.com");
    client.println("Connection: close");
    client.println();
  }
}

void loop() {
  while (client.available()) {
    Serial.write(client.read());           // stream the response
  }
  if (!client.connected()) {
    client.stop();
    Serial.println("\n-- done --");
    while (1);
  }
}

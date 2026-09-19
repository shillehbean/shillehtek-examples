// ESP32 example that uses the W5500 to run a basic HTTP server over DHCP, serving a page that shows page hits and uptime.
//
// Buy this module: https://shillehtek.com/products/w5500-spi-ethernet-module-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/w5500-spi-ethernet-module-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// W5500 Ethernet - ESP32 Web Server
// SCLK->18, MISO->19, MOSI->23, SCS->5, 3.3V, GND

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x02 };
EthernetServer server(80);
unsigned long hits = 0;

void setup() {
  Serial.begin(115200);
  Ethernet.init(5);

  if (Ethernet.begin(mac) == 0) {
    Serial.println("DHCP failed");
    while (1) delay(10);
  }
  server.begin();
  Serial.print("Open http://");
  Serial.println(Ethernet.localIP());
}

void loop() {
  EthernetClient client = server.available();
  if (!client) return;

  // skip request headers
  while (client.connected() && client.available()) client.read();

  hits++;
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println("<html><body style='font-family:sans-serif'>");
  client.println("<h1>ESP32 + W5500</h1>");
  client.print("<p>Wired and reliable. Page hits: ");
  client.print(hits);
  client.print(" | Uptime: ");
  client.print(millis() / 1000);
  client.println(" s</p></body></html>");
  delay(1);
  client.stop();
}

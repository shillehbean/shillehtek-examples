// Reads DHT11 temperature and humidity and sends the values as an MCP2515 CAN frame every second.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-mcp2515-can-bus-dht11-lcd
// Parts used: https://shillehtek.com/products/mcp2515-can-bus-module-tja1050-receiver-spi
//             https://shillehtek.com/products/shillehtek-dht11-with-cables
//             https://shillehtek.com/products/shillehtek-dht22-with-cables
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SPI.h>        // SPI for the MCP2515
#include <mcp2515.h>    // CAN library: https://github.com/autowp/arduino-mcp2515
#include <DHT.h>        // Temperature / humidity sensor

#define DHTPIN 8
#define DHTTYPE DHT11

struct can_frame canMsg;
MCP2515 mcp2515(10);     // CS on D10
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  while (!Serial);
  Serial.begin(9600);
  SPI.begin();
  dht.begin();

  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);  // 500 kbps with the 8 MHz crystal
  mcp2515.setNormalMode();
}

void loop() {
  int h = dht.readHumidity();
  int t = dht.readTemperature();

  canMsg.can_id  = 0x036;
  canMsg.can_dlc = 8;
  canMsg.data[0] = h;
  canMsg.data[1] = t;
  canMsg.data[2] = 0x00;
  canMsg.data[3] = 0x00;
  canMsg.data[4] = 0x00;
  canMsg.data[5] = 0x00;
  canMsg.data[6] = 0x00;
  canMsg.data[7] = 0x00;

  mcp2515.sendMessage(&canMsg);
  delay(1000);
}

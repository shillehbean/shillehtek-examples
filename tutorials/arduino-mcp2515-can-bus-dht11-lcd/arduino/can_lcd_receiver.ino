// Receives MCP2515 CAN frames and displays the transmitted temperature and humidity on a 16x2 I2C LCD.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-mcp2515-can-bus-dht11-lcd
// Parts used: https://shillehtek.com/products/mcp2515-can-bus-module-tja1050-receiver-spi
//             https://shillehtek.com/products/shillehtek-dht11-with-cables
//             https://shillehtek.com/products/shillehtek-dht22-with-cables
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SPI.h>
#include <mcp2515.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // try 0x3F if 0x27 is silent
struct can_frame canMsg;
MCP2515 mcp2515(10);                 // CS on D10

void setup() {
  Serial.begin(9600);
  SPI.begin();

  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("CANBUS TUTORIAL");
  delay(3000);
  lcd.clear();

  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    int humidity    = canMsg.data[0];
    int temperature = canMsg.data[1];

    lcd.setCursor(0, 0);
    lcd.print("Humi: ");
    lcd.print(humidity);

    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(temperature);

    delay(1000);
    lcd.clear();
  }
}

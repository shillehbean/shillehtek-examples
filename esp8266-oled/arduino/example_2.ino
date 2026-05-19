// Initializes I2C and the SSD1306 OLED, connects the board to a Wi‑Fi network, then displays connection status and the device IP address on the OLED.
//
// Buy this module: https://shillehtek.com/products/nodemcu-esp8266-development-board-with-0-96-inch-oled-display-type-c-with-soldering-and-foam
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/nodemcu-esp8266-development-board-with-0-96-inch-oled-display-type-c-with-soldering-and-foam-manual
// More examples: https://github.com/shillehtek/examples
//

#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);
const char* ssid = "your-ssid";
const char* pwd  = "your-pwd";

void setup() {
  Wire.begin(4, 5);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Connecting WiFi...");
  display.display();

  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) delay(200);

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Connected!");
  display.println(WiFi.localIP());
  display.display();
}

void loop() {}

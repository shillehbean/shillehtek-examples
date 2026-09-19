// Initializes the LAN8720 Ethernet interface on the ESP32 (T-Internet-POE), registers event handlers, and prints the assigned IP address to Serial when the link is up.
//
// Buy this module: https://shillehtek.com/products/esp32-poe-ethernet-dev-board-lan8720a
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-poe-ethernet-dev-board-lan8720a-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// T-Internet-POE - bring up Ethernet and fetch a web page
// Board: "ESP32 Dev Module". Uses the built-in ETH library.

#define ETH_CLK_MODE  ETH_CLOCK_GPIO17_OUT
#define ETH_POWER_PIN 5
#define ETH_TYPE      ETH_PHY_LAN8720
#define ETH_ADDR      0
#define ETH_MDC_PIN   23
#define ETH_MDIO_PIN  18

#include <ETH.h>

static bool ethConnected = false;

void onEvent(WiFiEvent_t event) {
  switch (event) {
    case ARDUINO_EVENT_ETH_GOT_IP:
      Serial.print("IP address: ");
      Serial.println(ETH.localIP());
      ethConnected = true;
      break;
    case ARDUINO_EVENT_ETH_DISCONNECTED:
      ethConnected = false;
      break;
    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.onEvent(onEvent);
  ETH.begin(ETH_ADDR, ETH_POWER_PIN, ETH_MDC_PIN,
            ETH_MDIO_PIN, ETH_TYPE, ETH_CLK_MODE);
}

void loop() {
  if (ethConnected) {
    Serial.println("Ethernet up - board is on the LAN");
    delay(5000);
  }
}

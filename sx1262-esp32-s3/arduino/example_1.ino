// Instructions to add the Heltec ESP32 boards URL to Arduino IDE, install the Heltec board package, select the WiFi LoRa 32(V3) board and install the Heltec_ESP32 library.
//
// Buy this module: https://shillehtek.com/products/sx1262-esp32-s3-0-96-inch-blue-oled-display-bluetooth-wifi-kit-32-module-iot-development-board-for-arduino-w-antenna-868-915mhz-with-soldering-and-foam
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/sx1262-esp32-s3-0-96-inch-blue-oled-display-bluetooth-wifi-kit-32-module-iot-development-board-for-arduino-w-antenna-868-915mhz-with-soldering-and-foam-manual
// More examples: https://github.com/shillehtek/examples
//

1. In Arduino IDE -> Preferences, add this Boards Manager URL:
   https://resource.heltec.cn/download/package_heltec_esp32_index.json

2. Tools -> Board -> Boards Manager -> install "Heltec ESP32 Series Dev-boards"

3. Tools -> Board -> Heltec ESP32 Arduino -> "WiFi LoRa 32(V3)"

4. Tools -> Port -> (your CP2102 USB-C port)

5. Install the Heltec_ESP32 library via Library Manager.

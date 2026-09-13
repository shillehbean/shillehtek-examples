-- Connect the ESP32-S3 to a Wi‑Fi network using the Lua esp32.netconnect API.
--
-- Full tutorial: https://shillehtek.com/blogs/news/esp32-s3-xedge32-program-lua-web-ide
-- Parts used: https://shillehtek.com/products/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable
-- More examples: https://github.com/shillehbean/shillehtek-examples
--

esp32.netconnect("wifi", {ssid="your-Wi-Fi-SSID", pwd="password"})

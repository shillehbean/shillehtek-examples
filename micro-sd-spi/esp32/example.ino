// Mounts the SD card on an ESP32 using CS pin 5, writes 'Hello from ESP32!' to /hello.txt, then reads and prints the file over Serial.
//
// Buy this module: https://shillehtek.com/products/micro-sd-tf-card-adapter-reader-module-spi-interface-for-arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/micro-sd-tf-card-adapter-reader-module-spi-interface-for-arduino-manual
// More examples: https://github.com/shillehtek/examples
//

#include <SPI.h>
#include <SD.h>

#define CS_PIN 5

void setup() {
  Serial.begin(115200);
  if (!SD.begin(CS_PIN)) {
    Serial.println("Card Mount Failed");
    return;
  }
  Serial.println("SD ready");

  File f = SD.open("/hello.txt", FILE_WRITE);
  f.println("Hello from ESP32!");
  f.close();

  f = SD.open("/hello.txt");
  while (f.available()) Serial.write(f.read());
  f.close();
}

void loop() {}

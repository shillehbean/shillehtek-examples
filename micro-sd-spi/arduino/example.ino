// Initializes the SD card using CS pin 10 and appends analog A0 sensor readings to datalog.txt every second while echoing values to Serial.
//
// Buy this module: https://shillehtek.com/products/micro-sd-tf-card-adapter-reader-module-spi-interface-for-arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/micro-sd-tf-card-adapter-reader-module-spi-interface-for-arduino-manual
// More examples: https://github.com/shillehtek/examples
//

#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");

  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println("--- New Session ---");
    dataFile.close();
  }
}

void loop() {
  int sensor = analogRead(A0);
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print("ms=");
    dataFile.print(millis());
    dataFile.print(",sensor=");
    dataFile.println(sensor);
    dataFile.close();
    Serial.print("logged: ");
    Serial.println(sensor);
  }
  delay(1000);
}

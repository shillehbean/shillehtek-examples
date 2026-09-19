// ESP32 example using the hardware UART (UART2) with the Adafruit Fingerprint library to initialize the R307S, capture fingerprints, and print matched template ID and confidence.
//
// Buy this module: https://shillehtek.com/products/fingerprint-sensor-r307s-optical-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/fingerprint-sensor-r307s-optical-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// R307S Fingerprint Sensor - ESP32 Example
// Sensor TXD -> GPIO 16 (RX2), Sensor RXD -> GPIO 17 (TX2), +5V -> VIN
// Library: "Adafruit Fingerprint Sensor Library" (Library Manager)

#include <Adafruit_Fingerprint.h>

// Use the ESP32's second hardware UART - no SoftwareSerial needed
HardwareSerial sensorSerial(2);  // UART2
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&sensorSerial);

void setup() {
  Serial.begin(115200);

  // begin(baud, config, RX pin, TX pin)
  sensorSerial.begin(57600, SERIAL_8N1, 16, 17);
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Fingerprint sensor found!");
  } else {
    Serial.println("Sensor not found - check wiring.");
    while (1) delay(1);
  }

  Serial.println("Place an enrolled finger on the window...");
}

void loop() {
  if (finger.getImage() != FINGERPRINT_OK) return;
  if (finger.image2Tz() != FINGERPRINT_OK) return;

  if (finger.fingerFastSearch() == FINGERPRINT_OK) {
    Serial.printf("Match! ID #%d (confidence %d)\n",
                  finger.fingerID, finger.confidence);
    delay(1000);
  } else {
    Serial.println("No match for this finger.");
    delay(500);
  }
}

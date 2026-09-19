// Arduino example using SoftwareSerial and the Adafruit Fingerprint library to initialize the R307S, display stored template count, capture a fingerprint image, convert it to a template, and run a fast search for a matching template.
//
// Buy this module: https://shillehtek.com/products/fingerprint-sensor-r307s-optical-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/fingerprint-sensor-r307s-optical-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// R307S Fingerprint Sensor - Arduino Example
// Sensor TXD -> D2, Sensor RXD -> D3 (via divider), +5V -> 5V, GND -> GND
// Library: "Adafruit Fingerprint Sensor Library" (Library Manager)

#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);  // RX = D2 (from TXD), TX = D3 (to RXD)
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  Serial.begin(9600);
  finger.begin(57600);  // R307S default baud rate

  if (finger.verifyPassword()) {
    Serial.println("Fingerprint sensor found!");
  } else {
    Serial.println("Sensor not found - check wiring and baud rate.");
    while (1) delay(1);
  }

  finger.getTemplateCount();
  Serial.print("Templates stored: ");
  Serial.println(finger.templateCount);
  Serial.println("Place an enrolled finger on the window...");
}

void loop() {
  // Step 1: capture an image of the finger
  if (finger.getImage() != FINGERPRINT_OK) return;

  // Step 2: convert the image to a search template
  if (finger.image2Tz() != FINGERPRINT_OK) return;

  // Step 3: search the stored library for a match
  if (finger.fingerFastSearch() == FINGERPRINT_OK) {
    Serial.print("Match! ID #");
    Serial.print(finger.fingerID);
    Serial.print(" (confidence ");
    Serial.print(finger.confidence);
    Serial.println(")");
    delay(1000);  // Debounce so one touch prints once
  } else {
    Serial.println("No match for this finger.");
    delay(500);
  }
}

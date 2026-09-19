// Uses the Elechouse VoiceRecognitionV3 library over SoftwareSerial to clear the module, load trained records 0–2 into the active recognizer, and print recognized command numbers to the Serial console.
//
// Buy this module: https://shillehtek.com/products/arduino-voice-recognition-module-v3
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-voice-recognition-module-v3-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Voice Recognition Module V3 - Arduino Example
// Module TXD -> D2, Module RXD -> D3, VCC -> 5V, GND -> GND
// Library: Elechouse VoiceRecognitionV3 (github.com/elechouse/VoiceRecognitionV3)
// Train records 0-2 first with the vr_sample_train example.

#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

VR myVR(2, 3);   // RX = D2 (from module TXD), TX = D3 (to module RXD)

uint8_t records[7];
uint8_t buf[64];

void setup() {
  Serial.begin(115200);
  myVR.begin(9600);

  if (myVR.clear() == 0) {
    Serial.println("Recognizer cleared.");
  } else {
    Serial.println("Module not found - check wiring.");
    while (1);
  }

  // Load trained records 0, 1, 2 into the active recognizer
  if (myVR.load((uint8_t)0) >= 0) Serial.println("Record 0 loaded");
  if (myVR.load((uint8_t)1) >= 0) Serial.println("Record 1 loaded");
  if (myVR.load((uint8_t)2) >= 0) Serial.println("Record 2 loaded");

  Serial.println("Speak one of your trained commands...");
}

void loop() {
  int ret = myVR.recognize(buf, 50);

  if (ret > 0) {
    // buf[1] holds the record number that was recognized
    switch (buf[1]) {
      case 0:
        Serial.println("Command 0 recognized!");
        // digitalWrite(LED_BUILTIN, HIGH);  // your action here
        break;
      case 1:
        Serial.println("Command 1 recognized!");
        break;
      case 2:
        Serial.println("Command 2 recognized!");
        break;
      default:
        Serial.println("Record not handled");
    }
  }
}

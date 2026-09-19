// ESP32 Arduino sketch that creates a Bluetooth Serial (SPP) interface to receive text commands from a paired phone to control an LED and send status feedback.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-bluetooth-serial-control-led-relay
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/1-channel-5v-relay-module
//             https://shillehtek.com/products/hc-05-6pin-bluetooth-module-no-button
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
const int LED = 2;
bool ledOn = false;

void setLed(bool on) {
  ledOn = on;
  digitalWrite(LED, on ? HIGH : LOW);
  SerialBT.println(on ? "LED is ON" : "LED is OFF");    // feedback to the phone
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  SerialBT.begin("ESP32test");                          // the name you'll pair with
  Serial.println("Pair with 'ESP32test', then open the terminal app");
}

void loop() {
  if (SerialBT.available()) {
    String cmd = SerialBT.readStringUntil('\n');
    cmd.trim(); cmd.toLowerCase();

    if      (cmd == "led on")  setLed(true);
    else if (cmd == "led off") setLed(false);
    else if (cmd == "toggle")  setLed(!ledOn);
    else if (cmd == "status")  SerialBT.println(ledOn ? "LED is ON" : "LED is OFF");
    else SerialBT.println("Commands: led on | led off | toggle | status");

    Serial.println("BT> " + cmd);                        // echo to USB for debugging
  }
}

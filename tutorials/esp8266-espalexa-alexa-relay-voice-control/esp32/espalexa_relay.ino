// Arduino-framework sketch that uses Espalexa to expose a dimmable lamp (PWM) and a relay-controlled fan to Alexa over local WiFi, handling discovery and commands.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp8266-espalexa-alexa-relay-voice-control
// Parts used: https://shillehtek.com/products/esp8266-d1-mini-v3-4mb-dev-board-presoldered
//             https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/1-channel-5v-relay-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <ESP8266WiFi.h>       // ESP32: #include <WiFi.h>
#include <Espalexa.h>

const char* SSID = "YourNetwork";
const char* PASS = "YourPassword";
const int LAMP = D1, FAN = D2;     // ESP32: 16 and 17

Espalexa alexa;

// Alexa sends a level 0-255: 0 = off, 255 = on, anything between = dimmed
void lampChanged(uint8_t level) {
  analogWrite(LAMP, level);        // PWM: "Alexa, set desk lamp to 30 percent" works
  Serial.printf("lamp -> %d\n", level);
}
void fanChanged(uint8_t level) {
  digitalWrite(FAN, level > 0);    // relay: on for anything above zero
  Serial.printf("fan -> %s\n", level ? "ON" : "OFF");
}

void setup() {
  Serial.begin(115200);
  pinMode(LAMP, OUTPUT); pinMode(FAN, OUTPUT);

  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(250);
  Serial.println("\nconnected: " + WiFi.localIP().toString());

  alexa.addDevice("Desk Lamp", lampChanged);   // the names you'll say out loud
  alexa.addDevice("Desk Fan",  fanChanged);
  alexa.begin();
}

void loop() {
  alexa.loop();                    // answers Alexa's discovery and commands
  delay(1);
}

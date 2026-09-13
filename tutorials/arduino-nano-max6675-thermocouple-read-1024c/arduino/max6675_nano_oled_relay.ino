// Arduino sketch that reads temperature from a MAX6675 K-type thermocouple, displays the reading on an SSD1306 OLED, prints to Serial, and switches a relay when the temperature exceeds a defined threshold.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-max6675-thermocouple-read-1024c
// Parts used: https://shillehtek.com/products/max6675-module-k-type-thermocouple-sensor-measures-up-to-1024-degrees
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/1-channel-5v-relay-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SPI.h>
#include <max6675.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int SCK_PIN = 13, CS_PIN = 10, SO_PIN = 12;
const int RELAY = 7;
const float OVERTEMP_C = 250.0;

MAX6675 tc(SCK_PIN, CS_PIN, SO_PIN);
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

void setup() {
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);
  Serial.begin(9600);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(500);
}
void loop() {
  float c = tc.readCelsius();
  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.setTextSize(2); oled.setTextColor(WHITE);
  oled.print(c, 1); oled.print(" C");
  oled.display();
  Serial.println(c);
  digitalWrite(RELAY, c > OVERTEMP_C ? LOW : HIGH);
  delay(500);
}

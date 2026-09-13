// LoRa receiver sketch that initializes an SSD1306 OLED, listens for incoming LoRa packets at 433 MHz, toggles an LED and displays received messages (and RSSI/metadata) on the OLED.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-sx1278-lora-point-to-point
// Parts used: https://shillehtek.com/products/sx1278-lora-433mhz-transceiver-module
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/0-96-i2c-blue-oled-display-module-4-pin-ssd1306
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <LoRa.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String inString = "";
String myMessage = "";
int led = 3;

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);
  display.clearDisplay();
  display.display();
  while (!Serial);
  Serial.println("LoRa Receiver");
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 30);
  display.println("LoRa Receiver");
  display.display();
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  pinMode(led, OUTPUT);
}

void loop() {
  String message = "";
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Received packet '");
    digitalWrite(led, HIGH);
    delay(1000);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println("Received packet - ");
    display.display();
    Serial.println(packetSize);
    while (LoRa.available()) {
      message += (char)LoRa.read();
    }
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(20, 30);
    display.println(message);
    display.display();
    Serial.print(message);
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    digitalWrite(led, LOW);
  }
}

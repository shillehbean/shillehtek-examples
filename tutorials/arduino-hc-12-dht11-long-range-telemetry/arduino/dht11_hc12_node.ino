// Arduino sensor-node sketch that reads temperature and humidity from a DHT11, packs the values into four bytes and sends them over HC-12 every 3 seconds, and responds to incoming command bytes to toggle LEDs.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-hc-12-dht11-long-range-telemetry
// Parts used: https://shillehtek.com/products/hc-12-433mhz-serial-transceiver-si4438-arduino-esp32
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SoftwareSerial.h>
#include <DHT.h>

#define RED_LED  4
#define BLUE_LED 3
#define DHTPIN   5          // match the data pin in your wiring
#define DHTTYPE  DHT11

SoftwareSerial HC12(7, 8);  // RX, TX
DHT dht(DHTPIN, DHTTYPE);

byte TX[4];
unsigned long lastSend = 0;

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  HC12.begin(9600);
  dht.begin();
}

void loop() {
  while (HC12.available() > 0) {
    byte command = HC12.read();
    switch (command) {
      case 1: digitalWrite(RED_LED,  !digitalRead(RED_LED));  break;
      case 2: digitalWrite(BLUE_LED, !digitalRead(BLUE_LED)); break;
    }
  }

  if (millis() - lastSend >= 3000) {
    lastSend = millis();
    float temp = dht.readTemperature();
    float humi = dht.readHumidity();

    if (!isnan(temp) && !isnan(humi)) {
      int t = temp * 100;
      int h = humi * 100;
      TX[0] = highByte(t);  TX[1] = lowByte(t);
      TX[2] = highByte(h);  TX[3] = lowByte(h);
      for (byte i = 0; i < 4; i++) HC12.write(TX[i]);
    }
  }
}

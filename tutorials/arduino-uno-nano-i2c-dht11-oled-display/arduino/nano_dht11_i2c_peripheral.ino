// Arduino Nano peripheral sketch: reads DHT11 temperature and humidity every 2 seconds, stores values as tenths, responds to I2C requests with four bytes (temp10 high/low, hum10 high/low), and accepts a one-byte LED on/off command from the bus master.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-nano-i2c-dht11-oled-display
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/shillehtek-dht11-with-cables
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <DHT.h>                 // "DHT sensor library" by Adafruit (+ Adafruit Unified Sensor)

#define MY_ADDR 0x08
#define DHTPIN  2
DHT dht(DHTPIN, DHT11);

volatile int16_t temp10 = 0, hum10 = 0;   // tenths of a degree / percent
volatile byte ledCmd = 0;

void onRequest() {                         // controller asked: send 4 bytes
  byte out[4] = { highByte(temp10), lowByte(temp10), highByte(hum10), lowByte(hum10) };
  Wire.write(out, 4);
}
void onReceive(int n) {                    // controller wrote: first byte is a command
  while (Wire.available()) ledCmd = Wire.read();
  digitalWrite(LED_BUILTIN, ledCmd ? HIGH : LOW);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  dht.begin();
  Wire.begin(MY_ADDR);                     // join the bus AS A PERIPHERAL at 0x08
  Wire.onRequest(onRequest);
  Wire.onReceive(onReceive);
}

void loop() {
  static unsigned long last = 0;
  if (millis() - last >= 2000) {           // DHT11 needs e5 2 s between reads
    last = millis();
    float t = dht.readTemperature(), h = dht.readHumidity();
    if (!isnan(t) && !isnan(h)) { temp10 = t * 10; hum10 = h * 10; }
  }
}

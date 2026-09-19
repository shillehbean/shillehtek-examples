// MQ-7 CO monitor sketch that reads the MQ-7 on A0 and a DS18B20 temperature sensor on a OneWire bus, prints readings to Serial, and sounds a buzzer when CO exceeds a defined limit.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-mq-7-co-buzzer-alarm
// Parts used: https://shillehtek.com/products/mq-7-co-gas-sensor-module-arduino-esp32
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/ds18b20-waterproof-digital-temp-sensor-probe-1m-for-arduino-pi
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <OneWire.h>
#include <DallasTemperature.h>

#define CO_PIN     A0
#define BUZZER_PIN 8
#define ONE_WIRE   2
#define CO_LIMIT   400   // pick from YOUR clean-air baseline + margin

OneWire oneWire(ONE_WIRE);
DallasTemperature tempSensor(&oneWire);

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  tempSensor.begin();
}

void loop() {
  int co = analogRead(CO_PIN);
  tempSensor.requestTemperatures();
  float tempC = tempSensor.getTempCByIndex(0);

  Serial.print("CO: ");   Serial.print(co);
  Serial.print("  T: ");  Serial.println(tempC);

  if (co > CO_LIMIT) {
    tone(BUZZER_PIN, 1000);   // alarm!
  } else {
    noTone(BUZZER_PIN);
  }
  delay(250);
}

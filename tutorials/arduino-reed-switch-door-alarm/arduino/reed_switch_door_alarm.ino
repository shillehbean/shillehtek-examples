// Arduino sketch that reads a normally-open reed switch on D2 and sounds a buzzer on D8 when the door opens.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-reed-switch-door-alarm
// Parts used: https://shillehtek.com/products/reed-switch-magnetic-sensor-normally-open-arduino-esp32
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int sensorPin = 2;  // reed switch
const int buzzerPin = 8;  // buzzer

void setup() {
  pinMode(sensorPin, INPUT_PULLUP); // internal pull-up: closed = LOW
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int doorOpen = digitalRead(sensorPin); // HIGH = magnet away = door open

  if (doorOpen == HIGH) {
    tone(buzzerPin, 2000);   // sound the alarm
    Serial.println("Door OPEN!");
  } else {
    noTone(buzzerPin);       // silence when closed
  }
  delay(50);
}

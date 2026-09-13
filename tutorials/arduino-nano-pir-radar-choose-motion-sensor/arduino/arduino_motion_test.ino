// Reads a digital motion sensor input, sets the onboard LED to the sensor state, and prints motion events to the serial console every 100 ms.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-pir-radar-choose-motion-sensor
// Parts used: https://shillehtek.com/products/shillehtek-hc-sr501-pir-motion-sensor-module
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/rcwl-0516-microwave-doppler-radar-motion-sensor-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Both sensors: 3 pins (VCC, OUT, GND)
const int SENSOR_PIN = 2;
const int LED_PIN = 13;

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int s = digitalRead(SENSOR_PIN);
  digitalWrite(LED_PIN, s);
  if (s) Serial.println("motion!");
  delay(100);
}

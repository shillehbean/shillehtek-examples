// Reads the MQ-2 analog output on A0, prints readings over serial, and sounds a buzzer when the analog value exceeds a threshold.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-mq-2-gas-leak-alarm
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int SENSOR = A0;
const int BUZZER = 8;
const int THRESHOLD = 400;   // calibrate to your clean-air baseline + margin

void setup() {
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
  Serial.println("Warming up sensor...");
  delay(20000);
  Serial.println("Ready.");
}

void loop() {
  int v = analogRead(SENSOR);
  Serial.println(v);
  if (v > THRESHOLD) {
    tone(BUZZER, 2000, 200);
    delay(100);
  } else {
    noTone(BUZZER);
  }
  delay(500);
}

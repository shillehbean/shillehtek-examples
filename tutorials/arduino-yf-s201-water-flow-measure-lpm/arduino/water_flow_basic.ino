// Basic sketch that counts pulses from the YF-S201 on D2 and prints the calculated flow in liters per minute to Serial every second.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-yf-s201-water-flow-measure-lpm
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int SENSOR = 2;
volatile unsigned long pulses = 0;

void onPulse() { pulses++; }

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SENSOR), onPulse, RISING);
}

void loop() {
  unsigned long p = pulses;
  pulses = 0;
  delay(1000);   // measure over 1 second
  float flow_lpm = (p * 60.0) / 450.0;
  Serial.print(flow_lpm, 2);
  Serial.println(" L/min");
}

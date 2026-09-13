// ESP32-adapted version that uses an IRAM_ATTR interrupt handler to count encoder rotations and reports the count and button presses via Serial.
//
// Buy this module: https://shillehtek.com/products/Arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ky-040-rotary-encoder-module-for-arduino-with-demo-code-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// KY-040 Rotary Encoder - ESP32 Example
// CLK = GPIO 18, DT = GPIO 19, SW = GPIO 21

const int CLK = 18;
const int DT  = 19;
const int SW  = 21;

volatile long counter = 0;
volatile int lastCLK = HIGH;

void IRAM_ATTR readEncoder() {
  int cur = digitalRead(CLK);
  if (cur != lastCLK && cur == LOW) {
    if (digitalRead(DT) != cur) counter++;
    else                         counter--;
  }
  lastCLK = cur;
}

void setup() {
  Serial.begin(115200);
  pinMode(CLK, INPUT);
  pinMode(DT,  INPUT);
  pinMode(SW,  INPUT_PULLUP);
  attachInterrupt(CLK, readEncoder, CHANGE);
}

void loop() {
  static long last = 0;
  if (counter != last) {
    Serial.printf("Count: %ld\n", counter);
    last = counter;
  }
  if (digitalRead(SW) == LOW) {
    Serial.println("Button pressed!");
    delay(200);
  }
}

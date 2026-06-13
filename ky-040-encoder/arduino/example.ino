// Reads a KY-040 on an Arduino using an interrupt on the CLK pin to count encoder steps and prints counts and button presses over Serial.
//
// Buy this module: https://shillehtek.com/products/Arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ky-040-rotary-encoder-module-for-arduino-with-demo-code-manual
// More examples: https://github.com/shillehtek/examples
//

// KY-040 Rotary Encoder - Arduino Example
// CLK = D2 (interrupt), DT = D3, SW = D4

const int CLK = 2;
const int DT  = 3;
const int SW  = 4;

volatile long counter = 0;
volatile int lastCLK = HIGH;

void readEncoder() {
  int cur = digitalRead(CLK);
  if (cur != lastCLK && cur == LOW) {
    if (digitalRead(DT) != cur) counter++;
    else                         counter--;
  }
  lastCLK = cur;
}

void setup() {
  Serial.begin(9600);
  pinMode(CLK, INPUT);
  pinMode(DT,  INPUT);
  pinMode(SW,  INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CLK), readEncoder, CHANGE);
}

void loop() {
  static long last = 0;
  if (counter != last) {
    Serial.print("Count: ");
    Serial.println(counter);
    last = counter;
  }
  if (digitalRead(SW) == LOW) {
    Serial.println("Button pressed!");
    delay(200);  // debounce
  }
}

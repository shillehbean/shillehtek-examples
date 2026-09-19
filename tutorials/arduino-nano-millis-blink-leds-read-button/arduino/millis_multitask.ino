// Non-blocking multitask example: blink LED_A at a fixed 1s rate, blink LED_B at a potentiometer-controlled rate (50–1000 ms), read a button that forces both LEDs on, and periodically report status over Serial.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-millis-blink-leds-read-button
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int LED_A = 5, LED_B = 6, POT = A0, BTN = 2;

// a tiny reusable timer: "has `interval` ms passed since I last fired?"
struct Every {
  unsigned long interval, last = 0;
  Every(unsigned long ms) : interval(ms) {}
  bool ready() {
    unsigned long now = millis();
    if (now - last >= interval) { last = now; return true; }   // rollover-safe
    return false;
  }
};

Every blinkA(1000);      // LED A: fixed 1 s
Every blinkB(250);       // LED B: set by the pot
Every report(500);       // Serial status twice a second

void setup() {
  Serial.begin(9600);
  pinMode(LED_A, OUTPUT); pinMode(LED_B, OUTPUT); pinMode(BTN, INPUT_PULLUP);
}

void loop() {
  // task 1: LED A blinks at 1 Hz, no matter what else happens
  if (blinkA.ready()) digitalWrite(LED_A, !digitalRead(LED_A));

  // task 2: LED B blinks at a rate set live by the knob (50 ms ... 1000 ms)
  blinkB.interval = map(analogRead(POT), 0, 1023, 50, 1000);
  if (blinkB.ready()) digitalWrite(LED_B, !digitalRead(LED_B));

  // task 3: the button is checked thousands of times a second: instant response
  if (digitalRead(BTN) == LOW) { digitalWrite(LED_A, HIGH); digitalWrite(LED_B, HIGH); }

  // task 4: periodic status without slowing anything down
  if (report.ready()) {
    Serial.print("LED B interval: "); Serial.print(blinkB.interval); Serial.println(" ms");
  }
  // notice: no delay() anywhere
}

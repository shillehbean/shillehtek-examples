// Interrupt-driven pushbutton handler that debounces presses, toggles an LED instantly, and counts presses while the main loop performs long blocking work.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-pushbutton-interrupts-instant-led-toggle
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/200pcs-6mm-light-touch-button-switch-kit-plastic-box-4-3-5-6-7-8-9-10-12-14-16mm
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int LED = 12, BUTTON = 2;

volatile bool ledState = false;           // 'volatile': shared between ISR and loop()
volatile unsigned long lastEdge = 0;
volatile unsigned long presses = 0;

void onButton() {                         // the ISR: keep it short, no Serial, no delay
  unsigned long now = millis();           // reading millis() inside an ISR is fine
  if (now - lastEdge < 200) return;       // debounce: ignore bounces within 200 ms
  lastEdge = now;
  ledState = !ledState;
  digitalWrite(LED, ledState);
  presses++;
}

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON), onButton, FALLING);   // fire on press
}

void loop() {
  // the "long job": loop() is blocked, but the button still works
  noInterrupts();                         // read the shared counter atomically
  unsigned long p = presses;
  interrupts();
  Serial.print("Busy for 3 s... presses so far: ");
  Serial.println(p);
  delay(3000);
}

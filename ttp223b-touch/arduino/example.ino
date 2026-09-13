// Reads the TTP223 digital output on pin 2 and toggles the built-in LED on the rising touch edge while printing state changes to Serial.
//
// Buy this module: https://shillehtek.com/products/Arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/digital-sensor-ttp223b-module-capacitive-touch-switch-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// TTP223B Capacitive Touch Switch - Arduino Example
// Touch the pad to toggle the onboard LED.
// SIG: Digital Pin 2

const int touchPin = 2;
const int ledPin = LED_BUILTIN;

bool ledState = false;
bool lastTouch = false;

void setup() {
  Serial.begin(9600);
  pinMode(touchPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.println("TTP223B ready. Touch the pad...");
}

void loop() {
  bool touched = digitalRead(touchPin) == HIGH;

  // Rising-edge detection: only toggle on the moment of touch
  if (touched && !lastTouch) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState ? HIGH : LOW);
    Serial.println(ledState ? "LED ON" : "LED OFF");
  }
  lastTouch = touched;

  delay(20); // small debounce-style delay
}

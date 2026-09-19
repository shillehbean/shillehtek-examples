// Controls three LEDs on pins 2, 4, and 6 to implement a traffic-light sequence (green, yellow, red) with specified durations.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-led-traffic-light-controller
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
//             https://shillehtek.com/products/200pcs-6mm-light-touch-button-switch-kit-plastic-box-4-3-5-6-7-8-9-10-12-14-16mm
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int RED = 2, YELLOW = 4, GREEN = 6;

void setLights(bool r, bool y, bool g) {
  digitalWrite(RED, r);
  digitalWrite(YELLOW, y);
  digitalWrite(GREEN, g);
}

void go(int ms)      { setLights(LOW,  LOW,  HIGH); delay(ms); }
void caution(int ms) { setLights(LOW,  HIGH, LOW);  delay(ms); }
void stop(int ms)    { setLights(HIGH, LOW,  LOW);  delay(ms); }

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop() {
  go(5000);        // green: 5 s
  caution(2000);   // yellow: 2 s
  stop(5000);      // red: 5 s
}

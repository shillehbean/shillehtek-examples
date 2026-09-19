// Reads three potentiometers and a pushbutton, outputs PWM to an RGB LED to mix colors, and prints the current RGB values to Serial; button toggles LED on/off.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-rgb-led-color-mixer
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
//             https://shillehtek.com/products/200pcs-6mm-light-touch-button-switch-kit-plastic-box-4-3-5-6-7-8-9-10-12-14-16mm
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int R_PIN = 9,  G_PIN = 10, B_PIN = 11;
const int R_POT = A0, G_POT = A1, B_POT = A2;
const int BTN = 7;

bool on = true;

void setup() {
  Serial.begin(9600);
  pinMode(BTN, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(BTN) == LOW) {        // toggle on/off
    on = !on;
    delay(250);                          // crude debounce
  }

  // analogRead gives 0-1023; PWM wants 0-255 -> divide by 4
  int r = on ? analogRead(R_POT) / 4 : 0;
  int g = on ? analogRead(G_POT) / 4 : 0;
  int b = on ? analogRead(B_POT) / 4 : 0;

  analogWrite(R_PIN, r);
  analogWrite(G_PIN, g);
  analogWrite(B_PIN, b);

  Serial.print("RGB(");                  // copy this into any design tool
  Serial.print(r); Serial.print(", ");
  Serial.print(g); Serial.print(", ");
  Serial.print(b); Serial.println(")");

  delay(100);
}

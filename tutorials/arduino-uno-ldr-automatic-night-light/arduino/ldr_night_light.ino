// Read the LDR on analog pin A0, print the light level over serial, and switch an LED (or relay) on digital pin 2 using a threshold with hysteresis to avoid flicker.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-ldr-automatic-night-light
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
//             https://shillehtek.com/products/1-channel-5v-relay-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int LDR = A0;
const int LED = 2;
const int THRESHOLD = 500;    // from your Step 2 calibration
const int HYSTERESIS = 40;    // no flicker at the boundary

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  int light = analogRead(LDR);   // 0 (dark) .. 1023 (bright)
  Serial.println(light);

  if (light < THRESHOLD - HYSTERESIS)      digitalWrite(LED, HIGH); // dark
  else if (light > THRESHOLD + HYSTERESIS) digitalWrite(LED, LOW);  // bright

  delay(200);
}

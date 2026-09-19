// Reads the KY-037 on an ESP32: measures the ADC level (0–4095) and digital trigger pin, then prints the level and trigger state over serial.
//
// Buy this module: https://shillehtek.com/products/shillehtek-ky-037-sound-sensor-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ky-037-sound-sensor-module-with-analog
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// KY-037 on ESP32 - analog + digital read

const int analogPin  = 34;
const int digitalPin = 4;

void setup() {
  Serial.begin(115200);
  pinMode(digitalPin, INPUT);
}

void loop() {
  int level = analogRead(analogPin);   // 0..4095
  int trig  = digitalRead(digitalPin);
  Serial.printf("Level: %4d  Trigger: %s\n",
                level, trig == LOW ? "SOUND!" : "quiet");
  delay(50);
}

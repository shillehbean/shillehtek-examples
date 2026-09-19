// Reads distance from a JSN-SR04T ultrasonic sensor and displays the measurement on an SSD1306 I2C OLED and the serial console.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-jsn-sr04t-oled-distance-readout
// Parts used: https://shillehtek.com/products/jsn-sr04t-waterproof-ultrasonic-distance-sensor-arduino-esp32
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/0-96-i2c-blue-oled-display-module-4-pin-ssd1306
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TRIG_PIN 9
#define ECHO_PIN 8

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  // fire a 10 s trigger pulse
  digitalWrite(TRIG_PIN, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // time the echo and convert to centimeters
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  float distance = duration * 0.034 / 2;

  Serial.println(distance);

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Distance:");
  display.setTextSize(3);
  display.setCursor(10, 25);
  display.print(distance, 0);
  display.print(" cm");
  display.display();

  delay(250);
}

// Arduino sketch that reads a KY-040 rotary encoder (CLK, DT, SW) and drives an SSD1306 OLED to display a scrollable menu and handle selections.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ky-040-oled-menu-ui
// Parts used: https://shillehtek.com/products/ky-040-rotary-encoder-module-for-arduino-with-demo-code
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int CLK = 2, DT = 3, SW = 4;
volatile int pos = 0;
int lastPos = 0, lastClk = HIGH;

const char* items[] = {"Brightness", "Volume", "Setpoint", "Exit"};
const int N = 4;
int selected = 0;

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

void onRot() {
  int clk = digitalRead(CLK);
  if (clk != lastClk) {
    if (digitalRead(DT) != clk) pos++; else pos--;
    lastClk = clk;
  }
}

void draw() {
  oled.clearDisplay();
  for (int i = 0; i < N; i++) {
    oled.setCursor(8, i * 16);
    oled.setTextColor(i == selected ? BLACK : WHITE,
                       i == selected ? WHITE : BLACK);
    oled.print(items[i]);
  }
  oled.display();
}

void setup() {
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CLK), onRot, CHANGE);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextSize(1);
  draw();
}

void loop() {
  if (pos != lastPos) {
    selected = (selected + (pos > lastPos ? 1 : -1) + N) % N;
    lastPos = pos;
    draw();
  }
  if (digitalRead(SW) == LOW) {
    delay(50);  // debounce
    oled.clearDisplay();
    oled.setCursor(0, 24);
    oled.print("Picked: "); oled.print(items[selected]);
    oled.display();
    delay(800);
    draw();
  }
}

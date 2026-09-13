// Arduino sketch that reads distance from a VL53L0X ToF sensor, prints the reading to Serial, and displays the distance on an SSD1306 OLED.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-vl53l0x-oled-distance-display
// Parts used: https://shillehtek.com/products/gy-vl53l0xv2-laser-ranging-tof-sensor-module
//             https://shillehtek.com/products/0-96-i2c-blue-oled-display-module-4-pin-ssd1306
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 failed"));
    for (;;);
  }
  display.clearDisplay();
  display.display();
  if (!lox.begin()) {
    Serial.println(F("VL53L0X failed"));
    while (1);
  }
  Serial.println(F("VL53L0X ready"));
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Distance:");
  if (measure.RangeStatus != 4) {
    display.setTextSize(3);
    display.setCursor(0, 30);
    display.print(measure.RangeMilliMeter);
    display.println(" mm");
    Serial.print("Distance: ");
    Serial.print(measure.RangeMilliMeter);
    Serial.println(" mm");
  } else {
    display.setTextSize(2);
    display.setCursor(0, 30);
    display.println("Out of");
    display.println("range");
  }
  display.display();
  delay(100);
}

// Reads the sensor on digital pin D2 and prints "Obstacle detected!" or "Path clear" to the Serial monitor at 9600 baud.
//
// Buy this module: https://shillehtek.com/products/ir-infrared-obstacle-avoidance-sensor-module-for-arduino-robot
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ir-infrared-obstacle-avoidance-sensor-module-for-arduino-robot-manual
// More examples: https://github.com/shillehtek/examples
//

// IR Obstacle Sensor - print obstacle status on Arduino
// Wire VCC=5V, GND=GND, OUT=D2

const int sensorPin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {
  int state = digitalRead(sensorPin);
  if (state == LOW) {
    Serial.println("Obstacle detected!");
  } else {
    Serial.println("Path clear");
  }
  delay(100);
}

// Initializes the APDS-9960 on an Arduino Uno, attaches an interrupt, and starts the gesture engine using an ISR flag to process detected swipe gestures in the main loop.
//
// Buy this module: https://shillehtek.com/products/apds-9960-gesture-proximity-color-sensor-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/apds-9960-gesture-proximity-color-sensor-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// APDS-9960 Gesture Sensor - Arduino Uno Example
// SDA: A4, SCL: A5, INT: D2 (all through a logic level converter)
// VCC: 3.3V (NOT 5V)
// Library: "SparkFun APDS9960 RGB and Gesture Sensor" (Library Manager)

#include <Wire.h>
#include <SparkFun_APDS9960.h>

#define APDS9960_INT 2  // INT pin, active low

SparkFun_APDS9960 apds = SparkFun_APDS9960();
volatile bool isr_flag = false;

void interruptRoutine() {
  isr_flag = true;  // Keep the ISR short - just set a flag
}

void setup() {
  Serial.begin(9600);
  pinMode(APDS9960_INT, INPUT);
  attachInterrupt(digitalPinToInterrupt(APDS9960_INT), interruptRoutine, FALLING);

  // Initialize I2C and the sensor's default settings
  if (apds.init()) {
    Serial.println(F("APDS-9960 initialized"));
  } else {
    Serial.println(F("Init failed! Check wiring and 3.3V power."));
  }

  // Start the gesture engine with interrupts enabled
  if (apds.enableGestureSensor(true)) {
    Serial.println(F("Gesture sensor running - swipe over the sensor!"));
  } else {
    Serial.println(F("Could not start the gesture engine."));
  }
}

void loop() {
  if (isr_flag) {
    detachInterrupt(digitalPinToInterrupt(APDS9960_INT));
    handleGesture();
    isr_flag = false;
    attachInterrupt(digitalPinToInterrupt(APDS9960_INT), interruptRoutine, FALLING);
  }
}

void handleGesture() {
  if (apds.isGestureAvailable()) {
    switch (apds.readGesture()) {
      case DIR_UP:    Serial.println("UP");    break;
      case DIR_DOWN:  Serial.println("DOWN");  break;
      case DIR_LEFT:  Serial.println("LEFT");  break;
      case DIR_RIGHT: Serial.println("RIGHT"); break;
      case DIR_NEAR:  Serial.println("NEAR");  break;
      case DIR_FAR:   Serial.println("FAR");   break;
      default:        Serial.println("NONE");
    }
  }
}

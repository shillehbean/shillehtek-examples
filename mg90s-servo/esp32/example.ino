// Shows controlling the MG90S on an ESP32 by generating 50 Hz PWM with LEDC, converting desired angles to pulse widths and duty cycles for smooth sweeping.
//
// Buy this module: https://shillehtek.com/products/mg90s-metal-gear-micro-servo-motor-180-degree-9g-for-rc-plane
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mg90s-metal-gear-micro-servo-motor-180-degree-9g-for-rc-plane-manual
// More examples: https://github.com/shillehtek/examples
//

// MG90S Servo - ESP32 Arduino Example using LEDC PWM
// Signal pin: GPIO 18
// Power the servo from a separate 5V supply, share ground with ESP32.

const int servoPin = 18;
const int pwmChannel = 0;
const int pwmFreq = 50;        // 50 Hz for hobby servos
const int pwmResolution = 16;  // 16-bit duty

// Pulse width in microseconds at 50 Hz: 20000 us period
// Duty = (pulseUs / 20000) * 65535
int pulseToDuty(int pulseUs) {
  return (int)(((long)pulseUs * 65535L) / 20000L);
}

void writeAngle(int angle) {
  if (angle < 0) angle = 0;
  if (angle > 180) angle = 180;
  int pulseUs = map(angle, 0, 180, 500, 2400);
  ledcWrite(pwmChannel, pulseToDuty(pulseUs));
}

void setup() {
  Serial.begin(115200);
  ledcSetup(pwmChannel, pwmFreq, pwmResolution);
  ledcAttachPin(servoPin, pwmChannel);
  writeAngle(90);
  delay(500);
}

void loop() {
  for (int a = 0; a <= 180; a++) {
    writeAngle(a);
    delay(15);
  }
  for (int a = 180; a >= 0; a--) {
    writeAngle(a);
    delay(15);
  }
}

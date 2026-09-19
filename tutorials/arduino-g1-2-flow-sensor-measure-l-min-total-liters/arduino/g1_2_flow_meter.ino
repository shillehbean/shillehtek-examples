// Counts pulses from a hall-effect water flow sensor using an interrupt, calculates flow rate in L/min and accumulates total liters, then outputs results to the serial monitor.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-g1-2-flow-sensor-measure-l-min-total-liters
// Parts used: https://shillehtek.com/products/water-flow-sensor-g1-2-1-30l-min
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

volatile unsigned int pulseCount = 0;

const byte FLOW_PIN = 2;      // must be an interrupt pin
const float CAL     = 7.5;    // pulses/sec per L/min (tune to your sensor)

float flowRate = 0.0;         // L/min
float totalLiters = 0.0;
unsigned long lastCalc = 0;

void pulseISR() {
  pulseCount++;
}

void setup() {
  Serial.begin(9600);
  pinMode(FLOW_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(FLOW_PIN), pulseISR, RISING);
  lastCalc = millis();
}

void loop() {
  if (millis() - lastCalc >= 1000) {
    noInterrupts();
    unsigned int pulses = pulseCount;
    pulseCount = 0;
    interrupts();

    flowRate = pulses / CAL;              // L/min
    totalLiters += flowRate / 60.0;       // liters added this second

    Serial.print("Rate: ");
    Serial.print(flowRate);
    Serial.print(" L/min   Total: ");
    Serial.print(totalLiters);
    Serial.println(" L");

    lastCalc = millis();
  }
}

// Arduino sketch that uses an interrupt on D2 to count pulses from the flow sensor and prints the instantaneous flow (L/min) and cumulative liters to Serial every second.
//
// Buy this module: https://shillehtek.com/products/water-flow-sensor-g1-2-1-30l-min
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/water-flow-sensor-g1-2-1-30l-min-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// ZJ-S201 Water Flow Sensor - Arduino Example
// Yellow->D2, Red->5V, Black->GND

const byte flowPin = 2;
const float PULSES_PER_LMIN = 7.5;    // F(Hz) = 7.5 x Q(L/min)

volatile unsigned long pulses = 0;
float totalLiters = 0;

void onPulse() { pulses++; }

void setup() {
  Serial.begin(115200);
  pinMode(flowPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(flowPin), onPulse, FALLING);
  Serial.println("Flow meter ready - open the tap!");
}

void loop() {
  noInterrupts();
  unsigned long count = pulses;
  pulses = 0;
  interrupts();

  float lmin = count / PULSES_PER_LMIN;      // pulses in 1 s = Hz
  totalLiters += lmin / 60.0;

  Serial.print("Flow: ");
  Serial.print(lmin, 2);
  Serial.print(" L/min | Total: ");
  Serial.print(totalLiters, 3);
  Serial.println(" L");
  delay(1000);
}

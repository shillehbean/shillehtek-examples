// Reads the 49E Hall sensor analog value and the module's digital output, then prints both values to the Serial console.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-49e-hall-sensor-analog-digital-read
// Parts used: https://shillehtek.com/products/linear-hall-effect-sensor-49e-arduino-esp32
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

/* Displays both Analog and Digital values from a hall sensor module */
#define Hall_Sensor A0    // analog output
#define Hall_Sensor_D 2   // digital output

int Val1 = 0, Val2 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(Hall_Sensor_D, INPUT);
}

void loop() {
  Val1 = analogRead(Hall_Sensor);
  Serial.print(Val1);
  Val2 = digitalRead(Hall_Sensor_D);
  Serial.print("\t");
  Serial.println(Val2);
}

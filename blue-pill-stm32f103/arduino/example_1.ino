// Toggle the onboard LED (PC13) every 500 ms while sending an incrementing counter over Serial1 (PA9 TX / PA10 RX).
//
// Buy this module: https://shillehtek.com/products/shillehtek-pre-soldered-authentic-stm32f103c8t6-arm-stm32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-pre-soldered-authentic-stm32f103c8t6-arm-stm32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Blue Pill blink + serial counter.
// Board in Arduino IDE: "Generic STM32F1 series" -> "BluePill F103C8"
// Upload method: STM32CubeProgrammer (Serial) or ST-Link.

#define LED_PIN PC13  // Onboard LED (active LOW)

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial1.begin(9600);   // PA9 TX / PA10 RX
  Serial1.println("Blue Pill awake");
}

uint32_t counter = 0;

void loop() {
  digitalWrite(LED_PIN, LOW);   // LED on
  delay(500);
  digitalWrite(LED_PIN, HIGH);  // LED off
  delay(500);

  Serial1.print("Blink #");
  Serial1.println(counter++);
}

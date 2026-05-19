// Blink the on-board LED on PC13 (active LOW) using the Arduino STM32 core.
//
// Buy this module: https://shillehtek.com/products/shillehtek-unsoldered-stm32f103c8t6-blue-pill-arm-development-board-kit-pro-usb-v
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-unsoldered-stm32f103c8t6-blue-pill-arm-development-board-kit-pro-usb-v-manual
// More examples: https://github.com/shillehtek/examples
//

// STM32 Blue Pill - Blink on-board LED (PC13, active LOW)
// Install: Boards Manager -> "STM32 MCU based boards" by STMicroelectronics
// Select Board: "Generic STM32F1 series" -> Board part number "BluePill F103C8"
// Upload Method: "STM32CubeProgrammer (SWD)" if using ST-LINK
//                "STM32CubeProgrammer (Serial)" if using USB-TTL

void setup() {
  pinMode(PC13, OUTPUT);
}

void loop() {
  digitalWrite(PC13, LOW);   // LED on (active LOW)
  delay(500);
  digitalWrite(PC13, HIGH);  // LED off
  delay(500);
}

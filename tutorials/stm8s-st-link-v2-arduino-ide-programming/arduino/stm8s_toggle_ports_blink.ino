// Toggles all GPIO ports on an STM8S board in a loop to create a blink/LED pattern using the Sduino core.
//
// Full tutorial: https://shillehtek.com/blogs/news/stm8s-st-link-v2-arduino-ide-programming
// Parts used: https://shillehtek.com/products/st-link-v2-stm8-stm32-programmer-downloader
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// STM8S blink Sduino ST-Link/V2
void setup() {
  GPIOA->DDR = 0XFF;
  GPIOB->DDR = 0XFF;
  GPIOC->DDR = 0XFF;
  GPIOD->DDR = 0XFF;
  GPIOE->DDR = 0XFF; // all ports output
}
void loop() {
  --GPIOA->ODR;
  GPIOB->ODR++;
  GPIOC->ODR--;
  GPIOD->ODR++;
  GPIOE->ODR--; // toggle all IO ports
  {int n = 20000; while(n-- >0);} // nop loop delay
}

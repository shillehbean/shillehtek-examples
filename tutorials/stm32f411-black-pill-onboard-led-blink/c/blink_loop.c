// Main loop that blinks the onboard LED by setting and resetting PC13 with 1 second delays.
//
// Full tutorial: https://shillehtek.com/blogs/news/stm32f411-black-pill-onboard-led-blink
// Parts used: https://shillehtek.com/products/shillehtek-pre-soldered-authentic-stm32f411ceu6
// More examples: https://github.com/shillehbean/shillehtek-examples
//

while (1)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
    HAL_Delay(1000);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_Delay(1000);
}

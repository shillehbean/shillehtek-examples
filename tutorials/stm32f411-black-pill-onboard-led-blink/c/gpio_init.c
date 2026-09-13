// Enable the GPIOC clock and configure pin PC13 as a push-pull output with no pull-up/pull-down and low speed.
//
// Full tutorial: https://shillehtek.com/blogs/news/stm32f411-black-pill-onboard-led-blink
// Parts used: https://shillehtek.com/products/shillehtek-pre-soldered-authentic-stm32f411ceu6
// More examples: https://github.com/shillehbean/shillehtek-examples
//

GPIO_InitTypeDef GPIO_InitStruct = {0};

__HAL_RCC_GPIOC_CLK_ENABLE();

GPIO_InitStruct.Pin = GPIO_PIN_13;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

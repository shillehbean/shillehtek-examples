// STM32CubeIDE HAL example that toggles the PC13 LED using HAL_GPIO_WritePin and HAL_Delay in a main loop.
//
// Buy this module: https://shillehtek.com/products/shillehtek-unsoldered-stm32f103c8t6-blue-pill-arm-development-board-kit-pro-usb-v
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-unsoldered-stm32f103c8t6-blue-pill-arm-development-board-kit-pro-usb-v-manual
// More examples: https://github.com/shillehtek/examples
//

/* STM32CubeIDE auto-generates main.c when you make a project for STM32F103C8.
 * Configure PC13 as GPIO_Output in the .ioc file, then drop this in the loop. */

#include "main.h"

int main(void) {
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  while (1) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); // LED on
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);   // LED off
    HAL_Delay(500);
  }
}

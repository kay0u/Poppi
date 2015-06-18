#include <stm32f4xx_hal.h>
#include "include/stm32f4_discovery.h"
#include "include/stm32f4_discovery_accelerometer.h"
#include "include/stm32f4_discovery_gyroscope.h"

#include "include/Useful.h"
#include "include/Imu.h"

void Toggle_Leds(void);

#ifdef __cplusplus
extern "C"
{
#endif
	void SysTick_Handler(void)
	{
		HAL_IncTick();
		HAL_SYSTICK_IRQHandler();
	}
#ifdef __cplusplus
}
#endif

/**
  * @brief  Toggle LEDs
  * @param  None
  * @retval None
  */
void Toggle_Leds(void)
{
	BSP_LED_Toggle(LED3);
	HAL_Delay(100);
	BSP_LED_Toggle(LED4);
	HAL_Delay(100);
	BSP_LED_Toggle(LED5);
	HAL_Delay(100);
	BSP_LED_Toggle(LED6);
	HAL_Delay(100);
}

int main(void)
{ 
 /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
     */
	HAL_Init();

	Imu imu;
  
	/* Configure LED3, LED4, LED5 and LED6 */
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4); 
	BSP_LED_Init(LED5);
	BSP_LED_Init(LED6);

	/* Configure USER Button */
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
  
	/* Toggle LEDs between each Test */
	while (!Useful::UserPressButton)
	{
		Toggle_Leds();
	}
    
	BSP_LED_Off(LED3);
	BSP_LED_Off(LED4);
	BSP_LED_Off(LED5);
	BSP_LED_Off(LED6);
  
	/* 1. Start Test: Wait For User inputs -------------------------------------*/
	while (1)
	{
		Useful::UserPressButton = 0;
		imu.ACCELERO_MEMS_Test();

		/* Toggle LEDs between each Test */
		Useful::UserPressButton = 0;
		while (!Useful::UserPressButton) Toggle_Leds();
		BSP_LED_Off(LED3);
		BSP_LED_Off(LED4);
		BSP_LED_Off(LED5);
		BSP_LED_Off(LED6);
	}
}
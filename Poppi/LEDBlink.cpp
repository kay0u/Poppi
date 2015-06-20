#include <stm32f4xx_hal.h>

#include "include/stm32f4_discovery.h"
#include "include/stm32f4_discovery_accelerometer.h"
#include "include/stm32f4_discovery_gyroscope.h"
#include "FreeRTOS/Source/include/FreeRTOS.h"

#include "include/Useful.h"
#include "include/Imu.h"

void Toggle_Leds(void);

/**
  * @brief  Toggle LEDs
  * @param  None
  * @retval None
  */
void Toggle_Leds(void)
{
	BSP_LED_Toggle(LED3);
	osDelay(100);
	BSP_LED_Toggle(LED4);
	osDelay(100);
	BSP_LED_Toggle(LED5);
	osDelay(100);
	BSP_LED_Toggle(LED6);
	osDelay(100);
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 100000000
  *            HCLK(Hz)                       = 100000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 16000000
  *            PLL_M                          = 16
  *            PLL_N                          = 400
  *            PLL_P                          = 4
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale2 mode
  *            Flash Latency(WS)              = 3
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	  /* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();
  
	/* The voltage scaling allows optimizing the power consumption when the device is 
	   clocked below the maximum system frequency, to update the voltage scaling value 
	   regarding system frequency refer to product datasheet.  */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
	/* Enable HSI Oscillator and activate PLL with HSI as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = 0x10;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 16;
	RCC_OscInitStruct.PLL.PLLN = 400;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
  
	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
	   clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
	{
		Error_Handler();
	}
}

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
osThreadId LEDThread1Handle, PrintThread2Handle;

/**
  * @brief  Toggle LED3 and LED4 thread
  * @param  thread not used
  * @retval None
  */
static void LED_Thread1(void const *argument)
{
	uint32_t count = 0;
	(void) argument;
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);

	for (;;)
	{
		count = osKernelSysTick() + 5000;
    
		/* Toggle LED3 every 200 ms for 5 s */
		while (count >= osKernelSysTick())
		{
			BSP_LED_Toggle(LED3);
      
			osDelay(200);
		}
    
		/* Turn off LED3 */
		BSP_LED_Off(LED3);
    
		/* Suspend Thread 1 */
		osThreadSuspend(NULL);
    
		count = osKernelSysTick() + 5000;
    
		/* Toggle LED3 every 400 ms for 5 s */
		while (count >= osKernelSysTick())
		{
			BSP_LED_Toggle(LED3);
      
			osDelay(400);
		}
    
		/* Resume Thread 2 */
		osThreadResume(PrintThread2Handle);
	}
}

/**
  * @brief  Toggle LED4 thread
  * @param  argument not used
  * @retval None
  */
static void Print_Thread2(void const *argument)
{
	uint32_t count;
	(void) argument;

	for (;;)
	{
		count = osKernelSysTick() + 10000;
    
		// Print every 500 ms for 10 s 
		while (count >= osKernelSysTick())
		{
			//imu.printAngles();

			osDelay(500);
		}
    
		// Resume Thread 1 
		osThreadResume(LEDThread1Handle);
    
		// Suspend Thread 2 
		osThreadSuspend(NULL);  
	}
}

int main(void)
{ 
 /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
     */
	//SystemClock_Config();
	//InitializeTimer();
	
	HAL_Init();
	Imu imu;
	imu.init();

	BSP_LED_Off(LED3);
	BSP_LED_Off(LED4);
	BSP_LED_Off(LED5);
	BSP_LED_Off(LED6);

	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
	while (!Useful::UserPressButton)
	{
		Toggle_Leds();
	}

	osThreadDef(ABWABWALED, LED_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  
	// /!\ Attention, avec l'utilisation du printf il faut augmenter la stack size pour le thread.
	osThreadDef(ABWAPrintIMU, Print_Thread2, osPriorityRealtime, 1, configMINIMAL_STACK_SIZE + 500);
  
	LEDThread1Handle = osThreadCreate(osThread(ABWABWALED), NULL);
	PrintThread2Handle = osThreadCreate(osThread(ABWAPrintIMU), NULL);
  
	osKernelStart();

	  // We should never get here as control is now taken by the scheduler
	for (;;) {
	};
}
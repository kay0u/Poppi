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

/* Private typedef -----------------------------------------------------------*/
#define  PERIOD_VALUE       (65535)      /* Period Value  */

#define  PULSE1_VALUE       40961       /* Capture Compare 1 Value  */
#define  PULSE2_VALUE       27309       /* Capture Compare 2 Value  */
#define  PULSE3_VALUE       13654       /* Capture Compare 3 Value  */
#define  PULSE4_VALUE       6826        /* Capture Compare 4 Value  */

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef    TimHandle;
TIM_OC_InitTypeDef   sConfig;

uint32_t uwPrescalerValue = 0;
uint32_t uwCapturedValue = 0;


#define TIMx                           TIM3
#define TIMx_CLK_ENABLE                __HAL_RCC_TIM3_CLK_ENABLE

/* Definition for TIMx's NVIC */
#define TIMx_IRQn                      TIM3_IRQn
#define TIMx_IRQHandler                TIM3_IRQHandler

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

static void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();

	/* The voltage scaling allows optimizing the power consumption when the device is
	clocked below the maximum system frequency, to update the voltage scaling value
	regarding system frequency refer to product datasheet.  */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}

void InitializeTimer()
{
	/* STM32F4xx HAL library initialization:
	- Configure the Flash prefetch, instruction and Data caches
	- Configure the Systick to generate an interrupt each 1 msec
	- Set NVIC Group Priority to 4
	- Global MSP (MCU Support Package) initialization
	*/
	if (HAL_Init() != HAL_OK)
	{
		/* Start Conversation Error */
		Error_Handler();
	}

	/* Configure the system clock to 84 MHz */
	SystemClock_Config();

	/* Configure LED3 and LED4 */
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);


	/*##-1- Configure the TIM peripheral #######################################*/
	/* -----------------------------------------------------------------------
	In this example TIM3 input clock (TIM3CLK) is set to 2 * APB1 clock (PCLK1),
	since APB1 prescaler is different from 1.
	TIM3CLK = 2 * PCLK1
	PCLK1 = HCLK / 2
	=> TIM3CLK = HCLK = SystemCoreClock
	To get TIM3 counter clock at 10 KHz, the Prescaler is computed as following:
	Prescaler = (TIM3CLK / TIM3 counter clock) - 1
	Prescaler = (SystemCoreClock /10 KHz) - 1

	Note:
	SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f4xx.c file.
	Each time the core clock (HCLK) changes, user had to update SystemCoreClock
	variable value. Otherwise, any configuration based on this variable will be incorrect.
	This variable is updated in three ways:
	1) by calling CMSIS function SystemCoreClockUpdate()
	2) by calling HAL API function HAL_RCC_GetSysClockFreq()
	3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
	----------------------------------------------------------------------- */

	/* Compute the prescaler value to have TIM3 counter clock equal to 10 KHz */
	uwPrescalerValue = (uint32_t)((SystemCoreClock / 10000) - 1);

	/* Set TIMx instance */
	TimHandle.Instance = TIMx;

	/* Initialize TIM3 peripheral as follow:
	+ Period = 10000 - 1
	+ Prescaler = ((SystemCoreClock/2)/10000) - 1
	+ ClockDivision = 0
	+ Counter direction = Up
	*/
	TimHandle.Init.Period = 10000 - 1;
	TimHandle.Init.Prescaler = uwPrescalerValue;
	TimHandle.Init.ClockDivision = 0;
	TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	/*##-2- Start the TIM Base generation in interrupt mode ####################*/
	/* Start Channel1 */
	if (HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)
	{
		/* Starting Error */
		Error_Handler();
	}

	/* Infinite loop */
	while (1)
	{
	}
}

/**
* @brief  Period elapsed callback in non blocking mode
* @param  htim : TIM handle
* @retval None
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	printf("POUET POUET \r\n");
	BSP_LED_Toggle(LED4);
}

int main(void)
{ 
 /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
     */
	//InitializeTimer();
	
	HAL_Init();

	Imu imu;
  
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4); 
	BSP_LED_Init(LED5);
	BSP_LED_Init(LED6);

	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
	while (!Useful::UserPressButton)
	{
		Toggle_Leds();
	}
    
	BSP_LED_Off(LED3);
	BSP_LED_Off(LED4);
	BSP_LED_Off(LED5);
	BSP_LED_Off(LED6);
  
	while (1)
	{
		imu.printAngles();
	}
}
#include <stm32f4xx_hal.h>

#include "include/stm32f4_discovery.h"
#include "include/stm32f4_discovery_accelerometer.h"
#include "include/stm32f4_discovery_gyroscope.h"

#include "include/Useful.h"
#include "include/Imu.h"

void Toggle_Leds(void);

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

	/* Configure the system clock to 100 MHz */
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

Imu imu;

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
    
		/* Print every 500 ms for 10 s */
		while (count >= osKernelSysTick())
		{
			imu.printAngles();

			osDelay(500);
		}
    
		/* Resume Thread 1 */
		osThreadResume(LEDThread1Handle);
    
		/* Suspend Thread 2 */
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
	SystemClock_Config();
	//InitializeTimer();
	
	HAL_Init();

	Imu imu;
	BSP_LED_Off(LED3);
	BSP_LED_Off(LED4);
	BSP_LED_Off(LED5);
	BSP_LED_Off(LED6);

	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
	while (!Useful::UserPressButton)
	{
		Toggle_Leds();
	}
	/* Thread 1 definition */
	osThreadDef(ABWABWALED, LED_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  
	/* Thread 2 definition */
	/* /!\ Attention, avec l'utilisation du printf il faut augmenter la stack size pour le thread.*/
	osThreadDef(ABWAPrintIMU, Print_Thread2, osPriorityRealtime, 1, configMINIMAL_STACK_SIZE + 500);
  
	/* Start thread 1 */
	LEDThread1Handle = osThreadCreate(osThread(ABWABWALED), NULL);
  
	/* Start thread 2 */
	PrintThread2Handle = osThreadCreate(osThread(ABWAPrintIMU), NULL);
  
	/* Start scheduler */
	osKernelStart();

	  /* We should never get here as control is now taken by the scheduler */
	for (;;);
}
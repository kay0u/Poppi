#include <stm32f4xx_hal.h>
#include "include/stm32f4_discovery.h"
#include "include/stm32f4_discovery_accelerometer.h"
#include "include/stm32f4_discovery_gyroscope.h"

#ifdef __cplusplus
extern "C"
{
#endif
	void SysTick_Handler(void)
	{
		HAL_IncTick();
		HAL_SYSTICK_IRQHandler();
	}

	/* Exported types ------------------------------------------------------------*/
	/* Exported constants --------------------------------------------------------*/
	/* Exported macro ------------------------------------------------------------*/
	#define ABS(x)         (x < 0) ? (-x) : x

	void Error_Handler(void);
	#ifdef __cplusplus
}
#endif

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void ACCELERO_MEMS_Test(void);
void GYRO_MEMS_Test(void);
void Audio_Test(void);

typedef struct
{
	void(*DemoFunc)(void);
	uint8_t DemoName[50]; 
	uint32_t DemoIndex;
}BSP_DemoTypedef;

/* Exported constants --------------------------------------------------------*/
#define COUNT_OF_EXAMPLE(x)    (sizeof(x)/sizeof(BSP_DemoTypedef))

/* Defines for the Audio playing process */
#define PAUSE_STATUS     ((uint32_t)0x00) /* Audio Player in Pause Status */
#define RESUME_STATUS    ((uint32_t)0x01) /* Audio Player in Resume Status */
#define IDLE_STATUS      ((uint32_t)0x02) /* Audio Player in Idle Status */

__IO uint8_t UserPressButton;

/* Init af threshold to detect acceleration on MEMS */
int16_t ThresholdHigh = 1000;
int16_t ThresholdLow = -1000;

/* Private function prototypes -----------------------------------------------*/
static void ACCELERO_ReadAcc(void);
static void GYRO_ReadAng(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Test ACCELERATOR MEMS Hardware.
  *         The main objective of this test is to check acceleration on 2 axes X and Y
  * @param  None
  * @retval None
  */
void ACCELERO_MEMS_Test(void)
{
  /* Init Accelerometer MEMS */
  if(BSP_ACCELERO_Init() != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  
  UserPressButton = 0;
  while(!UserPressButton)
  {
    ACCELERO_ReadAcc();
  }
}  

/**
  * @brief  Read Acceleration data.
  * @param  None
  * @retval None
  */
static void ACCELERO_ReadAcc(void)
{
  int16_t buffer[3] = {0};
  int16_t xval, yval = 0x00;
  
  /* Read Acceleration */
  BSP_ACCELERO_GetXYZ(buffer);

  xval = buffer[0];
  yval = buffer[1];

  if((ABS(xval))>(ABS(yval)))
  {
    if(xval > ThresholdHigh)
    { 
      /* LED5 On */
      BSP_LED_On(LED5);
      HAL_Delay(10);
    }
    else if(xval < ThresholdLow)
    { 
      /* LED4 On */
      BSP_LED_On(LED4);      
      HAL_Delay(10);
    }
    else
    { 
      HAL_Delay(10);
    }
  }
  else
  {
    if(yval < ThresholdLow)
    {
      /* LED6 On */
      BSP_LED_On(LED6);
      HAL_Delay(10);
    }
    else if(yval > ThresholdHigh)
    {
      /* LED3 On */
      BSP_LED_On(LED3);
      HAL_Delay(10);
    } 
    else
    { 
      HAL_Delay(10);
    }
  } 
  
  BSP_LED_Off(LED3);
  BSP_LED_Off(LED4);
  BSP_LED_Off(LED5);
  BSP_LED_Off(LED6);
}

/**
  * @brief  Test Gyroscope MEMS Hardware.
  *         The main objectif of this test is to check the hardware connection of the 
  *         MEMS peripheral.
  * @param  None
  * @retval None
  */
void GYRO_MEMS_Test(void)
{
  /* Init Gyroscope MEMS */
  if(BSP_ACCELERO_Init() != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  
  UserPressButton = 0;
  while(!UserPressButton)
  {
    GYRO_ReadAng();
  }
}  

/**
  * @brief  Read Gyroscope Angular data.
  * @param  None
  * @retval None
  */
static void GYRO_ReadAng(void)
{
  /* Gyroscope variables */
  float Buffer[3];
  float Xval, Yval = 0x00;
  
  /* Init Gyroscope Mems */
  if(BSP_GYRO_Init() != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  
  /* Read Gyroscope Angular data */
  BSP_GYRO_GetXYZ(Buffer);
  
  Xval = ABS((Buffer[0]));
  Yval = ABS((Buffer[1])); 
  
  if(Xval>Yval)
  {
    if(Buffer[0] > 5000.0f)
    { 
      /* LED5 On */
      BSP_LED_On(LED5);
      HAL_Delay(10);
    }
    else if(Buffer[0] < -5000.0f)
    { 
      /* LED4 On */
      BSP_LED_On(LED4);
      HAL_Delay(10);
    }
    else
    { 
      HAL_Delay(10);
    }
  }
  else
  {
    if(Buffer[1] < -5000.0f)
    {
      /* LED6 On */
      BSP_LED_On(LED6);
      
      HAL_Delay(10);
    }
    else if(Buffer[1] > 5000.0f)
    {
      /* LED3 On */
      BSP_LED_On(LED3);
      HAL_Delay(10);
    } 
    else
    { 
      HAL_Delay(10);
    }
  } 
  
  BSP_LED_Off(LED3);
  BSP_LED_Off(LED4);
  BSP_LED_Off(LED5);
  BSP_LED_Off(LED6);
}
/* Exported functions ------------------------------------------------------- */
void Toggle_Leds(void);

uint8_t DemoIndex = 0;
BSP_DemoTypedef  BSP_examples[] =  {
	{ ACCELERO_MEMS_Test, "LSM303DLHC", 0 }, 
	{ GYRO_MEMS_Test, "L3GD20", 1 }, 
};

/* Wave Player Pause/Resume Status. Defined as external in waveplayer.c file */
__IO uint32_t PauseResumeStatus = IDLE_STATUS;   

/* Counter for User button presses */
__IO uint32_t PressCount = 0;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  EXTI line detection callbacks.
  * @param  GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (KEY_BUTTON_PIN == GPIO_Pin)
	{
		while (BSP_PB_GetState(BUTTON_KEY) != RESET)
			;
		UserPressButton = 1;
	}
  
	if (ACCELERO_INT1_PIN == GPIO_Pin) 
	{
		if (PressCount == 1)
		{
		  /* Resume playing Wave status */
			PauseResumeStatus = RESUME_STATUS;
			PressCount = 0;
		}
		else
		{
		  /* Pause playing Wave status */
			PauseResumeStatus = PAUSE_STATUS;
			PressCount = 1;
		}
	}
}

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
  
	/* Configure LED3, LED4, LED5 and LED6 */
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4); 
	BSP_LED_Init(LED5);
	BSP_LED_Init(LED6);

	/* Configure USER Button */
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
  
	/* Toggle LEDs between each Test */
	while (!UserPressButton)
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
		UserPressButton = 0;
		BSP_examples[DemoIndex++].DemoFunc();
    
		/* If all Demo has been already executed, Reset DemoIndex to restart BSP example */
		if (DemoIndex >= COUNT_OF_EXAMPLE(BSP_examples))
		{
			DemoIndex = 0;
		}
		/* Toggle LEDs between each Test */
		UserPressButton = 0;
		while (!UserPressButton) Toggle_Leds();
		BSP_LED_Off(LED3);
		BSP_LED_Off(LED4);
		BSP_LED_Off(LED5);
		BSP_LED_Off(LED6);
	}
}

#ifdef __cplusplus
extern "C"
{
#endif
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
	void Error_Handler(void)
	{
	  /* Turn LED5 on */
		BSP_LED_On(LED5);
		while (1)
		{
		}
	}

	/**
	  * @brief  This function handles NMI exception.
	  * @param  None
	  * @retval None
	  */
	void NMI_Handler(void)
	{
	}

	/**
	  * @brief  This function handles Hard Fault exception.
	  * @param  None
	  * @retval None
	  */
	void HardFault_Handler(void)
	{
	  /* Go to infinite loop when Hard Fault exception occurs */
		while (1)
		{
		}
	}

	/**
	  * @brief  This function handles Memory Manage exception.
	  * @param  None
	  * @retval None
	  */
	void MemManage_Handler(void)
	{
	  /* Go to infinite loop when Memory Manage exception occurs */
		while (1)
		{
		}
	}

	/**
	  * @brief  This function handles Bus Fault exception.
	  * @param  None
	  * @retval None
	  */
	void BusFault_Handler(void)
	{
	  /* Go to infinite loop when Bus Fault exception occurs */
		while (1)
		{
		}
	}

	/**
	  * @brief  This function handles Usage Fault exception.
	  * @param  None
	  * @retval None
	  */
	void UsageFault_Handler(void)
	{
	  /* Go to infinite loop when Usage Fault exception occurs */
		while (1)
		{
		}
	}

	/**
	  * @brief  This function handles SVCall exception.
	  * @param  None
	  * @retval None
	  */
	void SVC_Handler(void)
	{
	}

	/**
	  * @brief  This function handles Debug Monitor exception.
	  * @param  None
	  * @retval None
	  */
	void DebugMon_Handler(void)
	{
	}

	/**
	  * @brief  This function handles PendSVC exception.
	  * @param  None
	  * @retval None
	  */
	void PendSV_Handler(void)
	{
	}

	/******************************************************************************/
	/*                 STM32F4xx Peripherals Interrupt Handlers                   */
	/*  Add here the Interrupt Handler for the used peripheral(s) (BSP), for the  */
	/*  available peripheral interrupt handler's name please refer to the startup */
	/*  file (startup_stm32f4xx.s).                                               */
	/******************************************************************************/

	/**
	  * @brief  This function handles External line 0 interrupt request.
	  * @param  None
	  * @retval None
	  */
	void EXTI0_IRQHandler(void)
	{
		HAL_GPIO_EXTI_IRQHandler(KEY_BUTTON_PIN);
	}

	/**
	  * @brief  This function handles External line 1 interrupt request.
	  * @param  None
	  * @retval None
	  */
	void EXTI1_IRQHandler(void)
	{
		HAL_GPIO_EXTI_IRQHandler(ACCELERO_INT2_PIN);
	}

	/**
	  * @brief  This function handles main I2S interrupt. 
	  * @param  None
	  * @retval 0 if correct communication, else wrong communication
	  */
	void I2S3_IRQHandler(void)
	{ 
		//HAL_DMA_IRQHandler(hAudioOutI2s.hdmatx);
	}

	/**
	  * @brief  This function handles I2S IT Stream interrupt request.
	  * @param  None
	  * @retval None
	  */
	void I2S2_IRQHandler(void)
	{
		//HAL_DMA_IRQHandler(hAudioInI2s.hdmarx);
	}
#ifdef __cplusplus
}
#endif
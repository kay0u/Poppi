#include "../include/Useful.h"

/* Defines for the Audio playing process */
#define PAUSE_STATUS     ((uint32_t)0x00) /* Audio Player in Pause Status */
#define RESUME_STATUS    ((uint32_t)0x01) /* Audio Player in Resume Status */
#define IDLE_STATUS      ((uint32_t)0x02) /* Audio Player in Idle Status */

/* Wave Player Pause/Resume Status. Defined as external in waveplayer.c file */
__IO uint32_t PauseResumeStatus = IDLE_STATUS;
/* Counter for User button presses */
__IO uint32_t PressCount = 0;



int printDebug(const char *fmt, ...)
{
    char buffer[4096];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
#ifdef DEBUG
	printf(buffer);
#endif
}


uint8_t Useful::UserPressButton = 0;
Useful::Useful()
{
}


Useful::~Useful()
{
}

int16_t Useful::distance(int16_t d1, int16_t d2)
{
	return ABS(d1 - d2);
}

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
		Useful::UserPressButton = 1;
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
#ifdef DEBUG
		printf("Error handler called\r\n");
#endif
		while (1)
		{
		}
	}

	void SysTick_Handler(void)
	{
		HAL_IncTick();
		osSystickHandler();
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
	* @brief  This function handles Debug Monitor exception.
	* @param  None
	* @retval None
	*/
	void DebugMon_Handler(void)
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

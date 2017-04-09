#include <BSP/stm32f411e_discovery.h>
#include <BSP/stm32f411e_discovery_accelerometer.h>
#include <BSP/stm32f411e_discovery_gyroscope.h>
#include <stm32f4xx_hal.h>

#include "FreeRTOS.h"
#include "../include/Useful.h"
#include "Hexapode/Hexapode.h"
#include "LedController.h"
#include "../include/Imu.h"

#include "Uart.hpp"
#include "AX12.h"

static void gyro(void const *argument)
{
	Imu imu;
	imu.init();

	/* Gyroscope variables */
	float* Buffer;
	float Xval, Yval = 0x00;

	for (;;)
	{
		/* Read Gyroscope Angular data */
		Buffer = imu.getGyroscope();

		Xval = ABS((Buffer[0]));
		Yval = ABS((Buffer[1]));

		if(Xval>Yval)
		{
			if(Buffer[0] > 5000.0f)
			{
				/* LED5 On */
				LedController::Instance().ledOn(LED5);
			}
			else if(Buffer[0] < -5000.0f)
			{
				/* LED4 On */
				LedController::Instance().ledOn(LED4);
			}
		}
		else
		{
			if(Buffer[1] < -5000.0f)
			{
				/* LED6 On */
				LedController::Instance().ledOn(LED6);
			}
			else if(Buffer[1] > 5000.0f)
			{
				/* LED3 On */
				LedController::Instance().ledOn(LED3);
			}
		}
		osDelay(100);

		LedController::Instance().ledOff(LED3);
		LedController::Instance().ledOff(LED4);
		LedController::Instance().ledOff(LED5);
		LedController::Instance().ledOff(LED6);
	}
}

static void hexapodeThread(void const *argument)
{
	Hexapode hexapode;
	hexapode.setDirection(Vector3::forward);
	Servo servo(1, 30, 220);
	int angle = 180;

	for (;;)
	{
		/*if (angle > servo.getMaxAngle())
			angle = servo.getMinAngle();
		servo.goTo(angle);
		//serial_pc::printfln("delta: %d", (xTaskGetTickCount() - time) * portTICK_RATE_MS);
		osDelay(500);

		angle += 10;*/
		hexapode.update();
		osDelay(10);
	}
}

static void SystemClock_Config(void);

int main(void)
{
	HAL_Init();
	SystemClock_Config();

	serial_pc::init(1000000);

	// /!\ Attention, avec l'utilisation du printf il faut augmenter la stack size pour le thread.
	osThreadDef(HexapodeThread, hexapodeThread, osPriorityRealtime, 1, configMINIMAL_STACK_SIZE + 1000);
	osThreadCreate(osThread(HexapodeThread), NULL);

	osThreadDef(GYROThread, gyro, osPriorityNormal, 1, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(GYROThread), NULL);
	
	/* Start scheduler */
	osKernelStart();
	
	// We should never get here as control is now taken by the scheduler
	for (;;) {
	};
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

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
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
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
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

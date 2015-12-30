#include <stm32f4xx_hal.h>

#include "../include/stm32f4_discovery.h"
#include "../include/stm32f4_discovery_accelerometer.h"
#include "../include/stm32f4_discovery_gyroscope.h"
#include "FreeRTOS.h"

#include "../include/Useful.h"
#include "../include/Imu.h"

#include "Uart.hpp"
#include "AX12.hpp"

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

Uart<1> serial_pc;
#define RXBUFFERSIZE 64
char aRxBuffer[RXBUFFERSIZE];

static void Print_Thread2(void const *argument)
{
	for (;;)
	{
		//HAL_StatusTypeDef status;
		//status = HAL_UART_Receive_IT(&serial_pc.UART, (uint8_t *) aRxBuffer, 10);

		serial_pc.read(aRxBuffer);
		//if (status == HAL_OK)
		serial_pc.printfln("%s", aRxBuffer);
		osDelay(500);
	}
}

/**
 * @brief  Print IMU infos
 * @param  argument not used
 * @retval None
 */
static void Print_Thread1(void const *argument)
{
	uint32_t count;
	(void)argument;
	Imu imu;
	imu.init();

	for (;;)
	{
		count = osKernelSysTick() + 10000;

		// Print every 500 ms for 10 s 
		while (count >= osKernelSysTick())
		{
			serial_pc.printfln("%f, %f", imu.getOrientation()[0], imu.getOrientation()[1]);

			osDelay(500);
		}

		// Resume Thread 1 
		osThreadResume(LEDThread1Handle);

		// Suspend Thread 2 
		osThreadSuspend(NULL);  
	}
}

static void BP_Thread(void const *argument)
{
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);

	for (;;)
	{

		while (!Useful::UserPressButton)
		{
			osDelay(100);
		}
		Useful::UserPressButton = 0;
		Toggle_Leds();
	}
}

int main(void)
{ 
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);
	BSP_LED_Init(LED6);

	serial_pc.init(115200);

	osThreadDef(ABWABWALED, LED_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	// /!\ Attention, avec l'utilisation du printf il faut augmenter la stack size pour le thread.
	osThreadDef(ABWAPrintIMU, Print_Thread1, osPriorityNormal, 1, configMINIMAL_STACK_SIZE + 200);
	osThreadDef(READThread, Print_Thread2, osPriorityNormal, 1, configMINIMAL_STACK_SIZE + 200);
	osThreadDef(BPThread, BP_Thread, osPriorityNormal, 1, configMINIMAL_STACK_SIZE);

	LEDThread1Handle = osThreadCreate(osThread(ABWABWALED), NULL);
	PrintThread2Handle = osThreadCreate(osThread(ABWAPrintIMU), NULL);
	osThreadCreate(osThread(BPThread), NULL);
	osThreadCreate(osThread(READThread), NULL);


	/* Start scheduler */
	osKernelStart();

	// We should never get here as control is now taken by the scheduler
	for (;;) {
	};
}

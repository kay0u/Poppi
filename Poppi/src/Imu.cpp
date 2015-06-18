#include "../include/Imu.h"


Imu::Imu()
{
	ThresholdHigh = 1000;
	ThresholdLow = -1000;
}


Imu::~Imu()
{
}


/**
* @brief  Read Acceleration data.
* @param  None
* @retval None
*/

#include "inttypes.h"

void Imu::ACCELERO_ReadAcc(void)
{
	int16_t buffer[3] = { 0 };
	int16_t xval, yval = 0x00;

	/* Read Acceleration */
	BSP_ACCELERO_GetXYZ(buffer);

	xval = buffer[0];
	yval = buffer[1];

	printf("x : %" PRId16 " | y : %" PRId16 " \r\n", xval, yval);

	if ((ABS(xval))>(ABS(yval)))
	{
		if (xval > ThresholdHigh)
		{
			/* LED5 On */
			BSP_LED_On(LED5);
			HAL_Delay(10);
		}
		else if (xval < ThresholdLow)
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
		if (yval < ThresholdLow)
		{
			/* LED6 On */
			BSP_LED_On(LED6);
			HAL_Delay(10);
		}
		else if (yval > ThresholdHigh)
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
* @brief  Test ACCELERATOR MEMS Hardware.
*         The main objective of this test is to check acceleration on 2 axes X and Y
* @param  None
* @retval None
*/
void Imu::ACCELERO_MEMS_Test(void)
{
	/* Init Accelerometer MEMS */
	if (BSP_ACCELERO_Init() != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	Useful::UserPressButton = 0;

	while (!Useful::UserPressButton)
	{
		ACCELERO_ReadAcc();
	}
}

/**
* @brief  Test Gyroscope MEMS Hardware.
*         The main objectif of this test is to check the hardware connection of the
*         MEMS peripheral.
* @param  None
* @retval None
*/
void Imu::GYRO_MEMS_Test(void)
{
	/* Init Gyroscope MEMS */
	if (BSP_ACCELERO_Init() != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	Useful::UserPressButton = 0;
	while (!Useful::UserPressButton)
	{
		GYRO_ReadAng();
	}
}

/**
* @brief  Read Gyroscope Angular data.
* @param  None
* @retval None
*/
void Imu::GYRO_ReadAng(void)
{
	/* Gyroscope variables */
	float Buffer[3];
	float Xval, Yval = 0x00;

	/* Init Gyroscope Mems */
	if (BSP_GYRO_Init() != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	/* Read Gyroscope Angular data */
	BSP_GYRO_GetXYZ(Buffer);

	Xval = ABS((Buffer[0]));
	Yval = ABS((Buffer[1]));

	if (Xval>Yval)
	{
		if (Buffer[0] > 5000.0f)
		{
			/* LED5 On */
			BSP_LED_On(LED5);
			HAL_Delay(10);
		}
		else if (Buffer[0] < -5000.0f)
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
		if (Buffer[1] < -5000.0f)
		{
			/* LED6 On */
			BSP_LED_On(LED6);

			HAL_Delay(10);
		}
		else if (Buffer[1] > 5000.0f)
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
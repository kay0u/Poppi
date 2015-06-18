#include "../include/Imu.h"
#include "inttypes.h"

Imu::Imu()
{
	ThresholdHigh = 1000;
	ThresholdLow = -1000;

	if (BSP_ACCELERO_Init() != HAL_OK || BSP_ACCELERO_Init() != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}
}


Imu::~Imu()
{
}


/**
* @brief  Read Acceleration data.
* @param  None
* @retval None
*/
void Imu::ACCELERO_ReadAcc(void)
{
	int16_t buffer[3] = { 0 };
	int16_t xval, yval = 0x00;

	/* Read Acceleration */
	BSP_ACCELERO_GetXYZ(buffer);

	xAccel = buffer[0];
	yAccel = buffer[1];

	/*
	xval = buffer[0];
	yval = buffer[1];
	
	if ((ABS(xval))>(ABS(yval)))
	{
		if (xval > ThresholdHigh)
		{
			// LED5 On 
			BSP_LED_On(LED5);
			HAL_Delay(10);
		}
		else if (xval < ThresholdLow)
		{
			// LED4 On
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
			// LED6 On 
			BSP_LED_On(LED6);
			HAL_Delay(10);
		}
		else if (yval > ThresholdHigh)
		{
			// LED3 On 
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
	BSP_LED_Off(LED6);*/
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

	xGyro = ABS(Buffer[0]);
	yGyro = ABS(Buffer[1]);

	/*
	Xval = ABS(Buffer[0]);
	Yval = ABS(Buffer[1]);
	
	if (Xval>Yval)
	{
		if (Buffer[0] > 5000.0f)
		{
			//LED5 On
			BSP_LED_On(LED5);
			HAL_Delay(10);
		}
		else if (Buffer[0] < -5000.0f)
		{
			//LED4 On
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
			//LED6 On
			BSP_LED_On(LED6);

			HAL_Delay(10);
		}
		else if (Buffer[1] > 5000.0f)
		{
			// LED3 On 
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
	BSP_LED_Off(LED6);*/
}

void Imu::comp_filter(float newAngle, float newRate) {

	float filterTerm0;
	float filterTerm1;
	float filterTerm2;
	float timeConstant;

	timeConstant = 0.5; // default 1.0

	filterTerm0 = (newAngle - xAngleFiltered) * timeConstant * timeConstant;
	filterTerm2 += filterTerm0 * dt;
	filterTerm1 = filterTerm2 + ((newAngle - xAngleFiltered) * 2 * timeConstant) + newRate;
	xAngleFiltered = (filterTerm1 * dt) + xAngleFiltered;
}

void Imu::printAngles()
{
	ACCELERO_ReadAcc();
	GYRO_ReadAng();
	comp_filter(xAccel, xGyro);
}